#include <stdio.h>
#include <math.h>

int main(){

    int n, k = 1, i, again, count = 1;
    float x, y, summ;
    while(1){

        // Entering variables and checking
        printf("Enter x: \n");
        scanf("%f", &x);
        printf("Enter n (more than 1): \n");
        scanf("%d", &n);
        if (n < 2){
            printf("Invalid value. Please, try again \n");
            continue;
        }

        summ = 1 / ((2 * k - 1) * pow(9, k - 1));
        printf("Result of summ: \n");
        printf("%d. %f\n", count, summ);
        for (k = 2; k <= n; k++){
            summ = summ + ( 1 / ((2 * k - 1) * pow(9, k-1)) );
            count += 1;
            printf("%d. %f\n", count, summ);
        }
        y = 4 * x + (2.0 / 3.0) * summ;
        printf("y = %f\n", y);

        // Checking for repeat
        printf("\nDo you want to try again? (1 - yes / 0 - no)\n");
        scanf("%d", &again);
        if (again == 1){
            continue;
        } else {
            return 0;
        }

    }

    return 0;

}