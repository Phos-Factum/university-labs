#include <conio.h>
#include <stdio.h>
#include <math.h>

int main()
{
    int S, P, r, a, b, c, n, i, x;
    
    printf("Enter a:");
    scanf("%d", &a);
    printf("Enter b:");
    scanf("%d", &b);
    printf("Enter c:");
    scanf("%d", &c);

    printf("Enter step:");
    scanf("%d", &i);

    printf("Enter count of variables (7-15): ");
    scanf("%d", &n);

    if ((n < 7) || (n > 15)) {
        printf("Enter count of variables from 7 to 15");
        return 0;
    } else {
        printf("_________________________________\n");
        printf("|  a  |  b  |  c  |  S  |    P  | \n");
        printf("|-----|-----|-----|-----|-------|\n");
    for (x = 0; x < n; x++){
        r = (a + b + c) / 2;
        P = (a + b + c);
        S = sqrt(r * (r - a) * (r - b) * (r - c));
        printf("| %2d  | %2d  | %2d  | %2d  | %4d  |\n", a, b, c, S, P);
        printf("|-----|-----|-----|-----|-------|\n");
        a += i;
        b += i;
        c += i;
        }
    }
    return 0;
}