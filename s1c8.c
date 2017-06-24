#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <openssl/aes.h>

#define KEY_SIZE 16

static int strCompare(const void *a, const void *b) {
	return strncmp((const char *)a, (const char *)b, 2 * KEY_SIZE);
}

int s1c8Result(void)
{
    FILE *fp = fopen("8.txt", "r");

    size_t size = 0;
    char *file = NULL;
    char *buffer = NULL;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    file = (char *)calloc(size + 1, 1);
    fread(file, size, 1, fp);
    fclose(fp);

    float score = 0, minScore = 1.0f;
    int minLine = 0;

    for (int line = 0; (buffer = strtok((0 == line) ? file : NULL, "\n")); ++line) {
        int nMember = strlen(buffer) / 2 / KEY_SIZE;
        qsort(buffer, nMember, 2 * KEY_SIZE, strCompare);

        int nScore = nMember;
        for (int i = 0; i < nMember - 1; ++i) {
            if (0 == strncmp(&buffer[i * 2 * KEY_SIZE], &buffer[(i + 1) * 2 * KEY_SIZE], 2 * KEY_SIZE)) {
                --nScore;
            }
        }

        score = (float)nScore / nMember;
        if (score < minScore) {
            minScore = score;
            minLine = line;
        }
    }

    free(file);

    return minLine;
}
