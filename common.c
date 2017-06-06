#include <ctype.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include "common.h"

void hex2Str(char *in, char *out)
{

}

void str2Hex(char *in, char *out)
{
	char cur = 0;
	while((cur = *in++)) {
		sprintf(out, "%02x", cur);
		out += 2;
	}
}

int strDistance(char *a, char *b)
{
	int distance = 0;

	while (*a || *b) {
		int sum = 0;
		unsigned char t = *a ^ *b;
		while (t) {
			sum += t & 1;
			t >>= 1;
		}
		distance += sum;
		
		if (*a) ++a;
		if (*b) ++b;
	}

	return distance;
}

int hammingDistance(char *a, char *b, int len)
{
	int distance = 0;

	while (len--) {
		int sum = 0;
		unsigned char t = *a++ ^ *b++;
		while (t) {
			sum += t & 1;
			t >>= 1;
		}
		distance += sum;
	}

	return distance;
}
