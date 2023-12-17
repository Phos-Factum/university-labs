#include <conio.h>
#include <stdio.h>
#include <math.h>

int main() 
{ 
    float x, a, b, p, y, z;
    printf("Enter x: ");
    scanf("%f", &x);
    if (pow(x, 3) == -0.5){
        printf("Division on zero occured! Please enter variables again.");
        return 0;
    }
    if (x < -12){
        printf("Division on zero occured! Please enter variables again.");
        return 0;
    }

    printf("Enter a: ");
    scanf("%f", &a);
    printf("Enter b: ");
    scanf("%f", &b);
    
    y = pow((x + 12), 1 / 2.0) / (2 * pow(x, 3) + 1);
    p = fabs(pow(y, 2) - a) + 6;
    z = p / (2 * cos(b) + p);

    printf("y = %8.4f  z = %8.4f\n", y, z);
    return 0;
}
