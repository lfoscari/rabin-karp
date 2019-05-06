#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char *read_text(int *dim)
{
	int size = 2, i = 0;
	char *s = malloc(size * sizeof(char)), t;

	while(( t = getchar() ) != '\n') {
		if(t > 127 || t < 33)
			continue;

		if(++i >= size) {
			size *= 2;
			s = realloc(s, size * sizeof(char));
		}
		*(s + i - 1) = t;
	}
	s = realloc(s, i * sizeof(char) + 1);
	*(s + i + 1) = '\0';
	*dim = i;
	return s;
}

int main(int argvc, char **argv)
{
	int q, d = 256, p = 0, t = 0, match = 0, n, m;
	char *text, *pattern;
	
	printf("Rabin-Karp algorithm - Pattern matching\n");

	printf("Text: ");
	text = read_text(&n);

	printf("Pattern: ");
	pattern = read_text(&m);

	printf("Modulo [%d]: ", m);
	scanf(" %d", &q);
	
	long h = (int) pow(d, m - 1) % q;

	for(int i = 0; i < m; i++) {
		p = ( d * p + pattern[i] ) % q;
		t = ( d * t + text[i] ) % q;
	}

	for(int s = 0; s <= n - m; s++) {
		if(p == t) {
			char temp[m];
			strncpy(temp, text + s, m);
			if(strcmp(temp, pattern) == 0) {
				printf("|> Match\tshift: %d\n", s);
				match++;
			}
		}
		if(s < n - m)
			t = ( d * ( t - h * text[s] ) + text[s + m] ) % q;
		if(t < 0)
			t += q;
	}

	printf("Number of matches: %d\n", match);

	return 0;
}
