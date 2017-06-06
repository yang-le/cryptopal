#include <stdio.h>
#include <limits.h>
#include <malloc.h>
#include <string.h>

char* singleXor(char *in, char key);
char* singleXorDetect(char *in, char *key, int *score);

// the code here is just for s1c4
char* s1c4Result(void)
{
    char buffer[512] = {0};    
    FILE *fp = fopen("4.txt", "r");

    char *result = NULL;
    int line = 0, resLine = 0;
    char key = 0, resKey = 0;
    int score = 0, minScore = INT_MAX;

    for (line = 0; fgets(buffer, 512, fp); ++line) {
        if ('\n' == buffer[strlen(buffer) - 1])
           buffer[strlen(buffer) - 1] = 0; // get rid of '\n'
        
        result = singleXorDetect(buffer, &key, &score);
        
        if (score < minScore) {
            minScore = score;
            resLine = line;
            resKey = key;
        }

        free(result);
    }

    for (rewind(fp), line = 0; fgets(buffer, 512, fp) && (line < resLine); ++line);
    
    if ('\n' == buffer[strlen(buffer) - 1])
        buffer[strlen(buffer) - 1] = 0; // get rid of '\n'
    
    result = singleXor(buffer, resKey);

    fclose(fp);

    return result;
}
