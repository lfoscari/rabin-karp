#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_text(int *dim)
{
	int size = 2, i = 0;
	char *s = malloc(size * sizeof(char)), t;

	while(( t = getchar() ) != '\n') {
		if(t > 126 || t < 33)
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
	int q, h = 1, d = 256, p = 0, t = 0, n, m;
	char *text, *pattern;

	printf("Rabin-Karp algorithm - Pattern matching\n");

	printf("Text: ");
	text = read_text(&n);

	printf("Pattern: ");
	pattern = read_text(&m);

	printf("Modulo [%d]: ", m);
	scanf(" %d", &q);

    // d^(m - 1)
    for(int i = 0; i < m - 1; i++)
        h = ( h * d ) % q;

    // Compute initial hash
	for(int i = 0; i < m; i++) {
		p = ( d * p + pattern[i] ) % q;
		t = ( d * t + text[i] ) % q;
	}

	for(int s = 0; s <= n - m; s++) {
		if(p == t) {
            int i;
            for(i = 0; i < m && text[s + i] != pattern[i]; i++);
            if(i >= m)
                printf("Match at offset %d\n", s);
        }
		if(s < n - m) {
			t = ( ( t - h * text[s] ) * d + text[s + m] ) % q;
		    if(t < 0)
			    t += q;
        }
	}

	return 0;
}
