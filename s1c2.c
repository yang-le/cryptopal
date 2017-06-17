#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

char* convHexRaw(char *hex, size_t *outSize);

void convRawHexSimple(char *in, size_t size, char *out)
{
	static const char hexTbl[] = "0123456789abcdef";	
	
	for (int i = 0; i < size; ++i) {
		*out++ = hexTbl[(unsigned)*in >> 4];
		*out++ = hexTbl[(unsigned)*in++ & 0xF];
	}
}

char* convRawHex(char *in, size_t size)
{
	char *out = (char *)calloc(size * 2, 1);

	convRawHexSimple(in, size, out);

	return out;
}

void fixedXorSimple(char *in1, char *in2, char *out, size_t size)
{
	for (int i = 0; i < size; ++i) {
		out[i] = in1[i] ^ in2[i];
	}
}

char* fixedXorHex(char *in1, char *in2)
{
	assert((strlen(in1) == strlen(in2)) && "Input of xor must be equal sized.");

	size_t size = 0;	
	char *out = NULL;
	char *_in1 = convHexRaw(in1, &size);
	char *_in2 = convHexRaw(in2, &size);
	char *_out = (char *)calloc(size, 1);

	fixedXorSimple(_in1, _in2, _out, size);
	out = convRawHex(_out, size);
	
	free(_in1);
	free(_in2);
	free(_out);

	return out;
}
