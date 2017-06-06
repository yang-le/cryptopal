#include <stdlib.h>
#include <string.h>
#include <assert.h>

static void convRawBase64Imp(char in[3], char out[4])
{
	static const char base64Tbl[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";	
	
	out[0] = base64Tbl[in[0] >> 2];
	out[1] = base64Tbl[(in[0] << 4 | in[1] >> 4) & 0x3F];
	out[2] = base64Tbl[(in[1] << 2 | in[2] >> 6) & 0x3F];
	out[3] = base64Tbl[in[2] & 0x3F];
}

void convRawBase64Simple(char *in, size_t inSize, char *out)
{
	int i = 0;
	int remain = 0;
	int count = inSize / 3;

	for (i = 0; i < count; ++i)
	{
		convRawBase64Imp(in + 3 * i, out + 4 * i);
	}

	remain = inSize - 3 * i;
	if (remain == 2) {
		char _in[3] = {in[3 * i], in[3 * i + 1], '\0'};
		convRawBase64Imp(_in, out + 4 * i);
		out[4 * i + 3] = '=';
	}
	if (remain == 1) {
		char _in[3] = {in[3 * i], '\0', '\0'};
		convRawBase64Imp(_in, out + 4 * i);
		out[4 * i + 3] = '=';
		out[4 * i + 2] = '=';
	}
}

char* convRawBase64(char *bytes, size_t inSize)
{
	size_t base64Len = (inSize + 2) / 3 * 4;
	char *base64 = (char*)calloc(base64Len, 1);
	
	convRawBase64Simple(bytes, inSize, base64);
	
	return base64;
}

void convHexRawSimple(char *in, char *out)
{
	static const char hexTbl[256] = {
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,	 
		0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  0,  0,  0,  0,  0,  0,
		0, 10, 11, 12, 13, 14, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0, 10, 11, 12, 13, 14, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	};

	while(*in) {
		assert(('0' == *in) || hexTbl[(unsigned)*in] && "Invalid hex string.");		
		*out = hexTbl[(unsigned)*in++] << 4;

		assert(('0' == *in) || hexTbl[(unsigned)*in] && "Invalid hex string.");		
		*out++ |= hexTbl[(unsigned)*in++];
	}
}

char* convHexRaw(char *hex, size_t *outSize)
{
	size_t hexSize = strlen(hex);	
	char *bytes = (char *)calloc(hexSize / 2, 1);
	
	assert((0 == hexSize % 2) && "The length of hex string must be even.");

	convHexRawSimple(hex, bytes);

	if (outSize) {
		*outSize = hexSize / 2;
	}

	return bytes;
}

char* convHexBase64(char *hexStr)
{
	size_t nBytes = 0;
	char *bytes = convHexRaw(hexStr, &nBytes);
	
	char *base64 = convRawBase64(bytes, nBytes);

	free(bytes);
	return base64;
}
