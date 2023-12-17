#include "stdio.h"
#include "math.h"
#include "string.h"
#include "stdlib.h"
#include "header.h"    // header file
#include "function.c"  // functions file


// Main function to finding "y"
int main()
{   
    while(1){
        char again[2];
        int s1, e1, a3, a2, a1, a0;
        int s2, e2, b3, b2, b1, b0;
        float y;

        // 1st Summ
        printf("Enter start and end of numerator's (up) summ using 'space': ");
        scanf("%d %d", &s1, &e1);
        printf("\ns1: %d; e1: %d.\n", s1, e1);
        if (s1 > e1)
        {
           while (s1 > e1)
            {
                printf("\nYou've entered wrong values: \nStart should be less and both values should exist. Try again!\n");
                printf("Enter start and end of numerator's (up) summ using 'space': ");
                scanf("%d %d", &s1, &e1);
                printf("\ns1: %d; e1: %d\n", s1, e1);
            }
        }
        printf("Enter coefficients for unknowns (a1, b1, c1, d1): ");
        scanf("%d %d %d %d", &a3, &a2, &a1, &a0);
        printf("a1: %d; b1: %d; c1: %d; d1: %d.\n", a3, a2, a1, a0);

        // 2nd Summ
        printf("Enter start and end of denominator's (down) summ using 'space': ");
        scanf("%d %d", &s2, &e2);
        printf("s2: %d; e2: %d.\n", s2, e2);
        if (s2 > e2)
        {
           while (s2 > e2)
            {
                printf("\nYou've entered wrong values: \nStart should be less and both values should exist. Try again!\n");
                printf("Enter start and end of denominator's (down) summ using 'space': ");
                scanf("%d %d", &s2, &e2);
                printf("s2: %d; e2: %d\n", s2, e2);
            }
        }
        printf("Enter coefficients for unknowns (a2, b2, c2, d2): ");
        scanf("%d %d %d %d", &b3, &b2, &b1, &b0);
        printf("a2: %d; b2: %d; c2: %d; d2: %d.\n", b3, b2, b1, b0);

        // Output answer (y) and formula
        y = (float)( (1 + 2 * summ(s1, e1, a3, a2, a1, a0)) / (2 + summ(s2, s2, b3, b2, b1, b0)) );
        printf("\ny = %8.3f", y);

        // Checking for repeat
        printf("\nDo you want to try again? (y, Y, yes, Yes / n, N, no, No): ");
        scanf("%s", &again);
        if ((strcmp(again, ("Y")) == 0) || (strcmp(again, ("y")) == 0) || (strcmp(again, ("Yes")) == 0)) 
        {
            system("cls");
            continue;
        } 
        else if ((strcmp(again, ("N")) == 0) || (strcmp(again, ("n")) == 0) || (strcmp(again, ("No")) == 0) || (strcmp(again, ("no")) == 0))
        { 
            return 0;
        } 
        else 
        {
            while ( ((strcmp(again, ("Y")) != 0) || (strcmp(again, ("y")) != 0) || (strcmp(again, ("Yes")) != 0) || (strcmp(again, ("yes")) != 0)) || ((strcmp(again, ("No")) != 0) || (strcmp(again, ("n")) != 0) || (strcmp(again, ("No")) != 0) || (strcmp(again, ("no")) != 0)) ) 
                {
                    if ((strcmp(again, ("Y")) == 0) || (strcmp(again, ("y")) == 0) || (strcmp(again, ("Yes")) == 0) || (strcmp(again, ("yes")) == 0))
                    {
                        break;
                    } 
                    else if ((strcmp(again, ("N")) == 0) || (strcmp(again, ("n")) == 0) || (strcmp(again, ("No")) == 0) || (strcmp(again, ("no")) == 0))
                    { 
                        return 0;
                    } 
                    else 
                    {
                        printf("OMG! Just write y, Y, yes, Yes / n, N, no, No \n");
                        printf("\nDo you want to try again? (y, Y, yes, Yes / n, N, no, No): ");
                        scanf("%s", &again);
                        continue;
                    }
                }
        continue;
        }
    }
    return 0;
}


// Изменить в ST4 подсветку %d;f зелёным ( сделано )
// Вынести в отдельную функцию ( сделано )
// Сделать проверку на повтор с y, Y, yes, Yes и n, N, no, No ( сделано )