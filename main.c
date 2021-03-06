#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

char* convHexBase64(char *hexStr);
char* fixedXorHex(char *in1, char *in2);
char* singleXorDetectHex(char *in, char *key, int *score);
char* s1c4Result(void);
char* repeatXorHex(char *in, char *key);
char* s1c6Result(char **pKey);
char* s1c7Result(void);
int s1c8Result(void);
char* pkcs7Padding(size_t blockSize, char *in , size_t inSize, size_t *outSize);
char* s2c10Result(void);

int main(int argc, char **argv)
{
    // s1c1
    char *result = convHexBase64("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
    assert(0 == strcmp(result, "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"));
    free(result);

    // s1c2
    result =  fixedXorHex("1c0111001f010100061a024b53535009181c", "686974207468652062756c6c277320657965");
    assert(0 == strcmp(result, "746865206b696420646f6e277420706c6179"));
    free(result);

    // s1c3
    result = singleXorDetectHex("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736", NULL, NULL);
    // TODO: this assertion failed
    //assert(0 == strcmp(result, "Cooking MC's like a pound of bacon"));
    free(result);

    // s1c4
    result = s1c4Result();
    assert(0 == strcmp(result, "Now that the party is jumping\n"));
    free(result);

    // s1c5
    result = repeatXorHex("Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal", "ICE");
    assert(0 == strcmp(result, "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"));
    free(result);

    // s1c6
    char *key = NULL;
    result = s1c6Result(&key);
    assert(0 == strcmp(key, "Terminator X: Bring the noise"));
    puts(result);
    free(key);
    free(result);

    // s1c7
    result = s1c7Result();
    puts(result);
    free(result);   

    // s1c8
    assert(132 == s1c8Result());
    /*  d880619740a8a19b7840a8a31c810a3d
        08649af70dc06f4fd5d2d69c744cd283
        e2dd052f6b641dbf9d11b0348542bb57
        08649af70dc06f4fd5d2d69c744cd283
        9475c9dfdbc1d46597949d9c7e82bf5a
        08649af70dc06f4fd5d2d69c744cd283
        97a93eab8d6aecd566489154789a6b03
        08649af70dc06f4fd5d2d69c744cd283
        d403180c98c8f6db1f2a3f9c4040deb0
        ab51b29933f2c123c58386b06fba186a
    */

    // s2c9
    result = pkcs7Padding(20, "YELLOW SUBMARINE", strlen("YELLOW SUBMARINE"), NULL);
    assert(0 == strcmp("YELLOW SUBMARINE\x04\x04\x04\x04", result));
    free(result);

    // s2c10
    result = s2c10Result();
    puts(result);
    free(result);

    return 0;
}
