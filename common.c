#include <ctype.h>
#include <limits.h>
#include "common.h"

void str2Hex(char *in, char *out)
{
	char cur = 0;
	char *input = in;
	char *output = out;
	while((cur = *input++)) {
		if (('0' <= cur) && (cur <= '9'))
			*output = cur - '0';
		else if (('a' <= cur) && (cur <= 'f'))
			*output = cur - 'a' + 0xa;
		else if (('A' <= cur) && (cur <= 'F'))
			*output = cur - 'A' + 0xA;
		else
			break;

		*output <<= 4;

		cur = *input++;
		if (('0' <= cur) && (cur <= '9'))
			*output++ |= cur - '0';
		else if (('a' <= cur) && (cur <= 'f'))
			*output++ |= cur - 'a' + 0xa;
		else if (('A' <= cur) && (cur <= 'F'))
			*output++ |= cur - 'A' + 0xA;
		else
			break;
	}
}

// the freq of 'a' - 'z' (/10000)
static int freqs[26] = {
	817,
	149,
	278,
	425,
	1270,
	223,
	202,
	609,
	697,
	15,
	77,
	403,
	240,
	675,
	750,
	193,
	10,
	599,
	633,
	906,
	276,
	98,
	236,
	15,
	197,
	7,
};

int strScore(char *in)
{
	int i = 0;
	int count[26] = {0};
	int score = 0;

	char *input = in;
	char cur = '\0';

	int len = 0;

	while((cur = *input++)) {
		if (!isspace(cur) && !isgraph(cur)) {
			return INT_MAX;
		}		
		if (('a' <= cur) && (cur <= 'z')) {
			++count[cur - 'a'];
			++len;
		}
		if (('A' <= cur) && (cur <= 'Z')) {
			++count[cur - 'A'];
			++len;
		}
	}
	
	if (0 == len)
		return INT_MAX;

	for (i = 0; i < 26; ++i) {
		count[i] *= 10000;
		count[i] /= len;
		score += (count[i] - freqs[i]) * (count[i] - freqs[i]);
	}

	return score;
}
