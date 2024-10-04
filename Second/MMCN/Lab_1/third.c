#include <stdio.h>
#include <math.h>
#define e 2.718281828
long long getFactorial(long long a)
{
if (a == 0 || a == 1) {
return 1;
}
return getFactorial(a - 1) * a;
}
int main() {
double t = 3.0 / 100;
int k = 24;
int lam = 1;
long double res = (pow(lam * t, k) / getFactorial(k)) * pow(e, -lam * t);
printf("res=%LF", res);
return 0;
}
