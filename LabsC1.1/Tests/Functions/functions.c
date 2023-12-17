#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int calculate(float i, float j)
{
	printf("a: %.0f; b: %.0f\n", i, j);

	printf("+ Addition       = %f\n", i + j);
	printf("- Substraction   = %f\n", i - j);
	printf("* Multiplication = %f\n", i * j);
	printf("/ Division       = %f\n", i / j);

	printf("Thanks for using 'calculate' function!\n");
	return 0;
}