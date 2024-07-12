#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define N 4
#define M 81

int main()
{
	char s[N][M];
	char *middle, *last;

	printf("Before: \n");
	for (int i = 0; i < N; i++)
	{
		scanf("%80[^\n]%*c", s[i]);
	}

	printf("\nAfter: \n");
	for (int i = 0; i < N; i++)
	{
		middle = strchr(s[i], ' ');
		last = strrchr(s[i], ' ');

		printf("%s%.*s%.*s\n", last, int(s[i] - middle), middle, int(middle - s[i]), s[i]);
	}

	return 0;
}