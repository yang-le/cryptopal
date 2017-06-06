#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "common.h"

char* convHexRaw(char *hex, size_t *outSize);

void singleXorSimple(char *in, char key, char *out, size_t size)
{
	int i = 0;
	for (i = 0; i < size; ++i) {
		out[i] = in[i] ^ key;
	}
}

char* singleXor(char *in, char key)
{
	char *_in = NULL, *_out = NULL;
	size_t size = 0;

	_in = convHexRaw(in, &size);
	_out = (char *)calloc(size, 1);

	singleXorSimple(_in, key, _out, size);
	
	free(_in);

	return _out;
}

// the freq of 'a' - 'z' (/10000)
static int freqs[26] = {
	817,
	149,
	278,
	425,
	1270,
	223,
	202,
	609,
	697,
	15,
	77,
	403,
	240,
	675,
	750,
	193,
	10,
	599,
	633,
	906,
	276,
	98,
	236,
	15,
	197,
	7,
};

int strScore(char *in)
{
	int i = 0;
	int count[26] = {0};
	int score = 0;
	int len = 0;
	char cur = '\0';

	while((cur = *in++)) {
		if (!isspace(cur) && !isgraph(cur)) {
			return INT_MAX;
		}		
		if (('a' <= cur) && (cur <= 'z')) {
			++count[cur - 'a'];
			++len;
		}
		if (('A' <= cur) && (cur <= 'Z')) {
			++count[cur - 'A'];
			++len;
		}
	}
	
	if (0 == len)
		return INT_MAX;

	for (i = 0; i < 26; ++i) {
		count[i] *= 10000;
		count[i] /= len;
		score += (count[i] - freqs[i]) * (count[i] - freqs[i]);
	}

	return score;
}

static struct entry {
	char key;
	int score;
	char *result;
} table[CHAR_MAX];

static int tableCompare(const void *a, const void *b) {
	return ((struct entry *)a)->score - ((struct entry *)b)->score;
}

char* singleXorDetect(char *in, char *key, int *score)
{
	int k = 0;
	for (k = 0; k < CHAR_MAX; ++k) {
		table[k].key = k;
		table[k].result = singleXor(in, k);
		table[k].score = strScore(table[k].result);
	}

	// TODO: we don't need sort, just to find the max
	qsort(table, CHAR_MAX, sizeof(table[0]), tableCompare);

	for (k = 1; k < CHAR_MAX; ++k) {
		free(table[k].result);
	}

	if (key) {
		*key = table[0].key;
	}

	if (score) {
		*score = table[0].score;
	}

	return table[0].result;
}
