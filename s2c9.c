#include <string.h>
#include <malloc.h>
#include <assert.h>

void pkcs7PaddingSimple(size_t paddingSize, char *in, size_t inSize, char *out)
{
    memcpy(out, in, inSize);
    memset(out + inSize, paddingSize, paddingSize);
}

char* pkcs7Padding(size_t blockSize, char *in , size_t inSize, size_t *outSize)
{
    size_t paddingSize = blockSize - (inSize % blockSize);
    
    char *out = calloc(inSize + paddingSize, 1);
    pkcs7PaddingSimple(paddingSize, in, inSize, out);

    if (outSize) {
        *outSize = inSize + paddingSize;
    }

    return out;
}
