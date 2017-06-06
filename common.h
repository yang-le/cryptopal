#ifndef _CRYPTO_PAL_COMMON
#define _CRYPTO_PAL_COMMON

#ifdef __cplusplus
extern "C" {
#endif

void str2Hex(char *in, char *out);
void hex2Str(char *in, char *out);
int strScore(char *in);
int strDistance(char *a, char *b);
int hammingDistance(char *a, char *b, int len);
char* hex2bytes(char *hex, size_t inSize, size_t *outSize);

#ifdef __cplusplus
}
#endif

#endif
