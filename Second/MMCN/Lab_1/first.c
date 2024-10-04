#include <stdio.h> 
#include <math.h>

#define e 2.718281828

long long getFactorial(long long a)
{

if (a == 0 || a == 1) { return 1;}

return getFactorial(a - 1) * a;
}

int main() {
printf("maxK="); int maxK; scanf("%d", &maxK);

printf("lam="); int lam; scanf("%d", &lam);

printf("t="); int t; scanf("%d", &t);
long double p; printf("k p\n");
for (int k = 0; k <= maxK; k++) {
p = (pow(lam * t, k) / getFactorial(k)) * pow(e, -lam * t);

printf("%d %LF\n", k, p);
}

return 0;
}
