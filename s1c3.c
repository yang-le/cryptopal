#include "common.h"
#include <string.h>

#include <stdlib.h>
#include <string.h>
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

#if 1
int main(int argc, char** argv)
{
	int byte = 0;
	char out[1024] = {'\0'};

	int score[128] = {0};
	int minScore = ((unsigned int)-1) >> 1;
	int minByte = 0;

	for (byte = 0; byte < 128; ++byte) {
		singleXor("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736", byte, out);
		score[byte] = strScore(out);
		if (score[byte] <= minScore) {
			minScore = score[byte];
			minByte = byte;
		}
	}

	singleXor("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736", minByte, out);

	return 0;
}
#endif