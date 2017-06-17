#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include "common.h"

char* convRawHex(char *in, size_t size);

void repeatXorSimple(char *in, char *key, char *out, size_t size)
{
    size_t keyLen = strlen(key);
	for (int i = 0; i < size; ++i) {
		out[i] = in[i] ^ key[i % keyLen];
	}
}

char* repeatXorHex(char *in, char *key)
{
	size_t size = strlen(in);
	char *_out = (char *)calloc(size, 1);
    char *out = NULL;

	repeatXorSimple(in, key, _out, size);
    out = convRawHex(_out, size);

    free(_out);

    return out;
}
