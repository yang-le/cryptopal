#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

static void convBase64RawImp(char in[4], char out[3])
{
	static const char base64Tbl[256] = {
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 62,  0,  0,  0, 63,	 
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61,  0,  0,  0,  0,  0,  0,
		0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,  0,  0,  0,  0,  0,
		0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,  0,  0,  0,  0,  0
	};

	char input[4] = {
		base64Tbl[(unsigned)in[0]], base64Tbl[(unsigned)in[1]],
		base64Tbl[(unsigned)in[2]], base64Tbl[(unsigned)in[3]]
	};
	
	assert(('A' == in[0]) || ('=' == in[0]) || input[0] && "char in not in base64 table");
	assert(('A' == in[1]) || ('=' == in[1]) || input[1] && "char in not in base64 table");
	assert(('A' == in[2]) || ('=' == in[2]) || input[2] && "char in not in base64 table");
	assert(('A' == in[3]) || ('=' == in[3]) || input[3] && "char in not in base64 table");

	out[0] = (input[0] << 2) | (input[1] >> 4);
    out[1] = (input[1] << 4) | (input[2] >> 2);
    out[2] = (input[2] << 6) | (input[3] >> 0);
}

void convBase64RawSimple(char *in, char *out)
{
	int i = 0;
	size_t len = strlen(in) / 4;

	for (i = 0; i < len; ++i)
	{
		convBase64RawImp(in + 4 * i, out + 3 * i);
	}

	if (in[4 * i + 3] == '=') out[3 * i + 2] = 0;
	if (in[4 * i + 2] == '=') out[3 * i + 1] = 0;
}

char* convBase64Raw(char *in, size_t *size)
{
	size_t _size = strlen(in) / 4 * 3;
	assert((0 == strlen(in) % 4) && "The length of base64 string must be divided by 4.");

	char *out = (char *)calloc(_size, 1);
	convBase64RawSimple(in, out);

	if (size) {
		*size = _size;
	}

	return out;
}

int hammingDistance(char *a, char *b, int len)
{
	int distance = 0;

	while (len--) {
		int sum = 0;
		unsigned char t = *a++ ^ *b++;
		while (t) {
			sum += t & 1;
			t >>= 1;
		}
		distance += sum;
	}

	return distance;
}

#define MAX_KEY_LEN 40

struct entry {
	int keyLen;
	float distance;
} table[MAX_KEY_LEN] = {{0, 0}};

static int tableCompare(const void *a, const void *b) {
	return ((struct entry *)a)->distance - ((struct entry *)b)->distance;
}

int strScore(char *in);
char* singleXorDetect(char *in, size_t size, char *key, int *score);
void repeatXorSimple(char *in, char *key, char *out, size_t size);

char* s1c6Result(void)
{
    FILE *fp = fopen("6.txt", "r");

	size_t size = 0;
	char *file = NULL;
	char *raw = NULL;
	size_t rawLen = 0;
	
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);

	file = (char *)calloc(size + 1, 1);
	fgets(file, size, fp);

	while(fgets(file + strlen(file) - 1, size - strlen(file), fp));
	fclose(fp);

	file[strlen(file) - 1] = 0;

	raw = convBase64Raw(file, &rawLen);

// seems no means{
	assert(37 == hammingDistance("this is a test", "wokka wokka!!!", sizeof("this is a test")));

	for (int tryKeyLen = 2; tryKeyLen < MAX_KEY_LEN; ++tryKeyLen) {
		table[tryKeyLen].keyLen = tryKeyLen;
		table[tryKeyLen].distance = 1.0f * hammingDistance(raw, raw + tryKeyLen, tryKeyLen) / tryKeyLen;
	}

	qsort(table, MAX_KEY_LEN, sizeof(table[0]), tableCompare);
// }seems no means

	char key1[MAX_KEY_LEN] = {0};
	char key2[MAX_KEY_LEN] = {0};
	int score = 0, minScore = INT_MAX;

	char *key = key1;
	char *out = (char *)calloc(rawLen + 1, 1);	
	char *blocks = (char *)calloc(rawLen + MAX_KEY_LEN, 1);	
	
	for (int keySize = 2; keySize < MAX_KEY_LEN; ++keySize) {
		int blockSize = rawLen / keySize + 1;

		for (int j = 0; j < keySize; ++j) {
			for (int k = 0, curPos = j; (k < blockSize) && (curPos < rawLen); ++k, curPos += keySize) {
				blocks[j * blockSize + k] = raw[curPos];
			}
			singleXorDetect(&blocks[j * blockSize], blockSize, &key[j], &score);
		}

		memset(blocks, 0, rawLen + MAX_KEY_LEN);
		
		repeatXorSimple(raw, key, out, rawLen);
		score = strScore(out);
		if (score < minScore) {
			minScore = score;
			key = (key == key1) ? key2 : key1;
		}
	}

	free(out);
	free(blocks);

	key = (key == key1) ? key2 : key1;
	char *result = (char *)calloc(strlen(key) + 1, 1);
	strcpy(result, key);

	return result;
}
