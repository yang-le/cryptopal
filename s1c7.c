#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <openssl/aes.h>

char* convBase64Raw(char *in, size_t *size);

void aesEcbSimple(char *key, size_t keyBits, char *in, char *out, size_t size, int enc)
{
    AES_KEY aes_dec_ctx;
    AES_set_decrypt_key((unsigned char *)key, keyBits, &aes_dec_ctx);
    for (int i = 0, keyBytes = keyBits / 8; i < size; i += keyBytes)
        AES_ecb_encrypt((unsigned char *)in + i, (unsigned char *)out + i, &aes_dec_ctx, enc);	
}

char* aesEcb(char *key, size_t keyBits, char *in, size_t size, int enc)
{
	char *out = (char *)calloc(size + 1, 1);
	aesEcbSimple(key, keyBits, in, out, size, enc);
	return out;
}

char* s1c7Result(void)
{
    FILE *fp = fopen("7.txt", "r");

	size_t size = 0;
	char *file = NULL;
	char *raw = NULL;
	size_t rawLen = 0;
	
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);

	file = (char *)calloc(size + 1, 1);
	fgets(file, size, fp);

	while(fgets(file + strlen(file) - 1, size - strlen(file), fp));
	fclose(fp);

	file[strlen(file) - 1] = 0;

	raw = convBase64Raw(file, &rawLen);
	free(file);

    char *out = aesEcb("YELLOW SUBMARINE", 128, raw, rawLen, 0);

    free(raw);
    return out;
}
