#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "functions.h"
#include "functions.c"


int main()
{

	float a, b;

	printf("Enter a: ");
	scanf("%f", &a);
	printf("Enter b: ");
	scanf("%f", &b);
	printf("So, let create a simple Calculator!\n");
	calculate(a, b);

	return 0;
}