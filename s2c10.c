#include <stdio.h>
#include <malloc.h>
#include <string.h>

void aesEcbSimple(char *key, size_t keyBits, char *in, char *out, size_t size, int enc);

void aesCbcXorSimple(char *in1, char *in2, char *out, size_t size)
{
	for (int i = 0; i < size; ++i) {
		out[i] = in1[i] ^ in2[i];
	}
}

void aesCbcSimpleEnc(char *key, size_t keyBits, char *iv, char *in, char *out, size_t size)
{
    size_t keyBytes = keyBits / 8;
    char *nextIn = (char *)calloc(keyBytes, 1);
    aesCbcXorSimple(iv, in, nextIn, keyBytes);

    for (int i = 0; i < size; i += keyBytes) {
        aesEcbSimple(key, keyBits, nextIn, out + i, keyBytes, 1);
        aesCbcXorSimple(out + i, in + i + keyBytes, nextIn, keyBytes);
    }
    
    free(nextIn);
}

void aesCbcSimpleDec(char *key, size_t keyBits, char *iv, char *in, char *out, size_t size)
{
    size_t keyBytes = keyBits / 8;

    aesEcbSimple(key, keyBits, in, out, keyBytes, 0); 
    aesCbcXorSimple(iv, out, out, keyBytes);

    for (int i = keyBytes; i < size; i += keyBytes) {
        aesEcbSimple(key, keyBits, in + i, out + i, keyBytes, 0);
        aesCbcXorSimple(in + i - keyBytes, out + i, out + i, keyBytes);
    }
}

char* aesCbc(char *key, size_t keyBits, char *iv, char *in, size_t size, int enc)
{
    char *out = (char *)calloc(size, 1);
    
    if (enc)
        aesCbcSimpleEnc(key, keyBits, iv, in, out, size);
    else
        aesCbcSimpleDec(key, keyBits, iv, in, out, size);

    return out;
}

char* convBase64Raw(char *in, size_t *size);

char* s2c10Result(void)
{
    FILE *fp = fopen("10.txt", "r");

    size_t size = 0;
    char *file = NULL;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    file = (char *)calloc(size + 1, 1);
	fgets(file, size, fp);

	while(fgets(file + strlen(file) - 1, size - strlen(file), fp));
	fclose(fp);

    file[strlen(file) - 1] = 0;

    char IV[16] = {0};
    size_t rawLen = 0;
    char *raw = convBase64Raw(file, &rawLen);
    char *out = aesCbc("YELLOW SUBMARINE", 128, IV, raw, rawLen, 0);

    free(raw);
    return out;
}
