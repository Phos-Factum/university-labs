#include <stdio.h> 
#include <math.h>

#define e 2.718281828

long long getFactorial(long long a)
{
if (a == 0 || a == 1) { return 1;
}

return getFactorial(a - 1) * a;

}

int main() {
printf("maxT="); int maxT; scanf("%d", &maxT);

printf("mu="); double mu; scanf("%lf", &mu);

long double h; printf("t h\n");
for (int t = 0; t <= maxT; t++) { h = 1 - pow(e, -mu * t);

printf("%d %LF\n", t, h);
}

return 0;
}

