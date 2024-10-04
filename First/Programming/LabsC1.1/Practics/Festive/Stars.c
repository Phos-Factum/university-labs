#include <stdio.h>
 
int main(void)
{
    int n;
    printf("Введите число строк:");
    scanf("%d", &n);
    
 
    int i, j, k;
 
    for (i = 1; i <= n; i++)
    {
        for (j = i; j < n; j++) {
            printf(" ");
        }
 
        for (k = 1; k <= i; k++) {
            printf("* ");
        }
 
        printf("\n");
    }
 
    return 0;
}