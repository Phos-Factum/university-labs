#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "time.h"

int main(void)
{
	srand(time(NULL));
	printf("%d", rand());
}