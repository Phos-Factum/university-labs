#include "stdio.h"
#include "math.h"


int summ(int n1, int n2, int a, int b, int c, int d)
{
    int s, i;
    s = 0;
    for (i = n1; i <= n2; i++)
    {
        s += a * pow(i, 3) + b * pow(i, 2) + c * pow(i, 1) + d;
    }
    return s;
}