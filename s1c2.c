#include <stdlib.h>
#include <string.h>
#include "common.h"

void fixedXorImp(char *in1, char *in2, char *out, size_t size)
{
	int i = 0;
	for (i = 0; i < size; ++i) {
		out[i] = in1[i] ^ in2[i];
	}
}

void fixedXor(char *in1, char *in2, char *out)
{
	size_t size = (strlen(in1) + 1) / 2;
	char *hex1 = (char*)malloc(size);
	char *hex2 = (char*)malloc(size);

	str2Hex(in1, hex1);
	str2Hex(in2, hex2);

	fixedXorImp(hex1, hex2, out, size);

	free(hex1);
	free(hex2);
}

#if 0
int main(int argc, char** argv)
{
	char out[1024] = {'\0'};

	fixedXor("1c0111001f010100061a024b53535009181c", "686974207468652062756c6c277320657965", out);

	return 0;
}
#endif