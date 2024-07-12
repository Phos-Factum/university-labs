#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int finderUnkown(int a, int b, int c, float x, float addX)
{
	int D;							// discriminant

	if (a == 0)
	{

		if (b == 0)
		{
			if (c == 0)
			{
				printf("x - any real number");
				return 0;
			}
			else
			{
				printf("No solution");
				return 0;
			}
		}
		else
		{
			if (c == 0)
			{
				printf("x = 0");
			}
			else
			{
				printf("Solving lineal equation: %dx = -(%d)\n", b, c);
				x = (float)(-c) / (float)(b);
				printf("x = %f", x);
			}
		}

	}
	else 
	{

		if (b == 0)
		{
			if (c == 0)
			{
				printf("x = 0");
			}
			else
			{
				printf("Incomplete quadratic equation: %dx^2 = -(%d)\n", a, c);
				x = pow(-c / a, 1.0 / 2.0);
				addX = -x;
				printf("x1 = %f, x2 = %f", x, addX);
			}
		}
		else 
		{
			if (c == 0)
			{
				printf("Incomplete quadratic equation: %dx^2 + %dx = 0\n", a, b);
				x = (float)(-b) / (float)(a);
				printf("x1 = 0; x = %f", x);
			}
			else	// Complete quadratic equation
			{
				printf("Standard quadratic equation: %dx^2 + %dx + %d = 0\n", a, b, c);
				D = pow(b, 2) - 4 * a * c;
				if (D > 0)
				{
					x = (-b + pow(D, 1.0 / 2.0)) / (2 * a);
					addX = (-b - pow(D, 1.0 / 2.0)) / (2 * a);
					printf("x1 = %f; x2 = %f", x, addX);
				}
				else if (D == 0)
				{
					x = -b / (2 * a);
					printf("x = %f", x);
				}
				else
				{
					printf("You have negative roots!");
					return 0;
				}
			}
		}

	}
	return 0;
}