#include <stdio.h>
#include <limits.h>
#include <memory.h>

#if 1
int main(int argc, char** argv)
{
    FILE *fp = fopen("4.txt", "r");
    char line[512] = {0}, result[512] = {0};
    int nLine = 0, minLine = 0;
    int minByte = 0, minScore = INT_MAX;

    while (fgets(line, 512, fp)) {
        int i = 0, curScore = 0;
        for (i = 0; i < 128; ++i) {
            memset(result, 0, 512);
            singleXor(line, i, result);
            curScore = strScore(result);
            if (curScore < minScore) {
                minLine = nLine;
                minByte = i;
                minScore = curScore;
            }
        }
        ++nLine;
    }

    rewind(fp);
    for (nLine = 0; nLine <=minLine; ++nLine)
        fgets(line, 512, fp);

    memset(result, 0, 512);
    singleXor(line, minByte, result);
    puts(result);

    return 0;
}
#endif
