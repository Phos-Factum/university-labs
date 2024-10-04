#include <conio.h>
#include <stdio.h>
#include <math.h>

int main(){
    float x, y;
    printf("Enter x:");
    scanf("%f", &x);
    if (x < -14){
        y = x * fabs(x + 21);
    }
    else if (x < -5){
        y = x * x * log(fabs(x * x + 48));
    }
    else if (x < 0){
        y = x / 3.0 + pow(x * x + 16, 1 / 2.0);
    }
    else{
        y = 2 + x / 3;
    }

    printf("%6.2f", y);
    return 0;
}
