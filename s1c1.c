#include <stdlib.h>
#include <string.h>
#include "common.h"

static char base64Tbl[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static void convBase64Imp(char in[3], char out[4])
{
	out[0] = base64Tbl[in[0] >> 2];
	out[1] = base64Tbl[(in[0] << 4 | in[1] >> 4) & 0x3F];
	out[2] = base64Tbl[(in[1] << 2 | in[2] >> 6) & 0x3F];
	out[3] = base64Tbl[in[2] & 0x3F];
}

void convBase64(char *in, size_t size, char *out)
{
	int i = 0;
	int remain = 0;
	int _size = size / 3;

	for (i = 0; i < _size; ++i)
	{
		convBase64Imp(in + 3 * i, out + 4 * i);
	}

	remain = size - 3 * i;
	if (remain == 2) {
		char _in[3] = {in[3 * i], in[3 * i + 1], '\0'};
		convBase64Imp(_in, out + 4 * i);
		out[4 * i + 3] = '=';
	}
	if (remain == 1) {
		char _in[3] = {in[3 * i], '\0', '\0'};
		convBase64Imp(_in, out + 4 * i);
		out[4 * i + 3] = '=';
		out[4 * i + 2] = '=';
	}
}

void hex2Base64(char *in, char *out)
{
	size_t size = (strlen(in) + 1) / 2;
	char *hex = (char*)malloc(size);
	
	str2Hex(in, hex);
	convBase64(hex, size, out);
	
	free(hex);
}

#if 0
int main(int argc, char** argv)
{
	char out[1024] = {'\0'};

	hex2Base64("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d", out);

	return 0;
}
#endif
