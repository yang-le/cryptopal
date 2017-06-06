#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include "common.h"

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
	char *out = (char *)calloc(_size, 1);

	assert((0 == strlen(in) % 4) && "The length of base64 string must be divided by 4.");

	convBase64RawSimple(in, out);

	if (size) {
		*size = _size;
	}

	return out;
}

#if 0
int main(int argc, char** argv)
{
    FILE *fp = fopen("6.txt", "r");
	char in[512] = {0};
	char out[512] = {0};
	char blocks[512] = {0};
	char blocksOut[512] = {0};
	char result[512] = {0};
	int outLen = 0;
	int keyLen = 0;
	int blockLen = 0;
	int maxKeyLen = 0;
	int minKeyLen = 0;
	int minDistance = INT_MAX;
	int minScore = INT_MAX;
	char minKey[64] = {0};
	int i = 0, j = 0;

	fgets(in, 512, fp);
	deBase64(in, out);
	
	outLen = strlen(in) / 4 * 3;
	maxKeyLen = outLen / 2;

	for (keyLen = 2; keyLen < maxKeyLen; ++keyLen) {
		int distance = hammingDistance(out, out + keyLen, keyLen) / keyLen;
		
		if (distance < minDistance) {
			minDistance = distance;
			minKeyLen = keyLen;
		}
	}

	blockLen = outLen / minKeyLen + 1;
	for (i = 0; i < outLen; ++i) {
		blocks[(i % minKeyLen) * blockLen + i / minKeyLen] = out[i];
	}

	for (i = 0; i < minKeyLen; ++i) {
		minScore = INT_MAX;
		memset(blocksOut, 0, 512);
		for (j = 0; j < 128; ++j) {
			singleXorImp(blocks + i * blockLen, j, blocksOut, blockLen);
			int score = strScore(blocksOut);
			if (score < minScore) {
				minScore = score;
				minKey[i] = j;
			}
		}
	}

	repeatXorImp(out, minKey, result, outLen);
	
	fclose(fp);
    return 0;
}
#endif