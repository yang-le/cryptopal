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
