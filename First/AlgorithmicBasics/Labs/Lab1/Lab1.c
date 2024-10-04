#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "functions.c"

int main()
{
	char again; 			// checking-for-repeat var
	int a, b, c;		// coefficients before x
	float x, addX;		// unknowns (х1, х2)

	while(1)
	{
		system("cls");
		printf("\033[0;35mHello! Here is a program that finds roots of quadratic equation.\033[0m\n\n");


		printf("Enter your a, b, c (one by one / using 'space'): ");
		scanf("%d %d %d", &a, &b, &c);
		printf("\n\033[0;36m%dx^2 + %dx + %d = 0\033[0m\n\n", a, b, c);
		finderUnkown(a, b, c, x, addX);

		// Repeat-check part
		printf("\n\n\033[0;33mDo you want to try again? (y - yes / other - no)\033[0m \nAnswer: ");
		scanf(" %s", &again);
		if (again != 'y')
		{
			break;
		}
	}

	return 0;
}