#include <stdio.h>
#include <limits.h>
#include <malloc.h>
#include <string.h>

char* singleXorHex(char *in, char key);
char* singleXorDetectHex(char *in, char *key, int *score);

// the code here is just for s1c4
char* s1c4Result(void)
{   
    FILE *fp = fopen("4.txt", "r");

    char key = 0, resKey = 0;
    char *result = NULL, *resLine = NULL;
    int score = 0, minScore = INT_MAX;

    size_t size = 0;
    char *file = NULL;
    char *buffer = NULL;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    file = (char *)calloc(size + 1, 1);
    fread(file, size, 1, fp);
    fclose(fp);

    for (int line = 0; (buffer = strtok((0 == line) ? file : NULL, "\n")); ++line) {
        free(singleXorDetectHex(buffer, &key, &score));
        
        if (score < minScore) {
            minScore = score;
            resLine = buffer;
            resKey = key;
        }
    }
    
    result = singleXorHex(resLine, resKey);
    
    free(file);

    return result;
}
