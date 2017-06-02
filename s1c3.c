#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "common.h"

void singleXorImp(char *in, char byte, char *out, size_t size)
{
	int i = 0;
	for (i = 0; i < size; ++i) {
		out[i] = in[i] ^ byte;
	}
}

void singleXor(char *in, char byte, char *out)
{
	size_t size = (strlen(in) + 1) / 2;
	char *hex = (char*)malloc(size);

	str2Hex(in, hex);

	singleXorImp(hex, byte, out, size);

	free(hex);
}

#if 0
struct entry {
	int key;
	int score;
	char *result;
} table[128];

static char result[128][512] = {0};

int main(int argc, char** argv)
{
	int i = 0, j = 0;

	for (i = 0; i < 128; ++i) {
		singleXor("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736", i, result[i]);
		table[i].key = i;
		table[i].score = strScore(result[i]);
		table[i].result = result[i];
	}

	for (i = 0; i < 128; ++i) {
		for (j = i + 1; j < 128; ++j) {
			if (table[i].score > table[j].score) {
				struct entry temp = table[i];
				table[i] = table[j];
				table[j] = temp;
			}
		}
	}

	return 0;
}
#endif