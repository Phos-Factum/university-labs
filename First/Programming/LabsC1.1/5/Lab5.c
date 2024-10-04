#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{

    float x, y, prod, summ;
    float xS, xE, step;
    int n, m, pS, sS;
    int count = 0;
    char again[1];
    int agn;
    
    while(1){
        //// Entering and checking variables
        // xS, xE (entering and checking)
        printf("\033[0d\033[2J");
        printf("Enter x (start): \n");
        scanf("%f", &xS);
        printf("Enter x (ending): \n");
        scanf("%f", &xE);
        if (xS < 0 || xE < 0 || xS > xE)
        {
            while(xS < 0 || xE < 0 || xS > xE)
            {
                printf("Try again, values should be '> 0' and 'start < end' \n");
                printf("Enter x (start): \n");
                scanf("%f", &xS);
                printf("Enter x (ending): \n");
                scanf("%f", &xE);
                continue;
            }
        }
        
        printf("xS: %f; xE: %f \n", xS, xE);


        // n, step (entering and checking)
        printf("Enter step count: \n");
        scanf("%d", &n);
        if (n < 2)
        {
            while(n < 2)
            {
                printf("Try again, count of steps should be '>= 2' \n");
                printf("Enter step count: \n");
                scanf("%d", &n);
                continue;
            }
        }
        step = (xE - xS) / (float)(n);

        // pS, sS and m (entering and checking)
        printf("Enter prod start: ");
        scanf("%d", &pS);
        printf("Enter summ start: ");
        scanf("%d", &sS);
        printf("Enter the ending of summ and prod: ");
        scanf("%d", &m);
        if (pS < 1 || sS < 1 || m < 1)
        {
            while(pS < 1 || sS < 1 || m < 1)
            {
                printf("Try again, your values should be '> 0' \n");
                printf("Enter prod start: ");
                scanf("%d", &pS);
                printf("Enter summ start: ");
                scanf("%d", &sS);
                printf("Enter the ending of summ and prod: ");
                scanf("%d", &m);
                continue;
            }
        }
        if (pS >= m || sS >= m)
        {
            while(pS >= m || sS >= m){
                printf("Try again, your 'prod / summ' is 'bigger / equal' than 'end' or '<= 1'\n");
                printf("Enter prod start: ");
                scanf("%d", &pS);
                printf("Enter summ start: ");
                scanf("%d", &sS);
                printf("Enter the ending of summ and prod: ");
                scanf("%d", &m);
            }
        }

        printf("pS: %d; sS: %d; m: %d; xS: %f; xE: %f; step: %f\n", pS, sS, m, xS, xE, step);



        // Main cycle
        for (x = xS; x <= xE; x += step)
        {
            // Prod in-cycle
            for (pS; pS <= m; pS++)
            {
                prod *= (x + pS);
            }
            // Summ in-cycle
            for (sS; sS <= m; sS++)
            {
                summ += (pow(sS, 3));
            }
            y = 2 * pow(x, 2) + prod + x * summ + 2;
            count++;
            printf("%d. y = %.2f\n", count, y);
        }


        // Checking for repeat
        printf("\nDo you want to try again? (Y / N): ");
        scanf("%s", &again);
        if (strcmp(again, "Y") == 0)
        {
            continue;
        } 
        else if (strcmp(again, "N") == 0)
        { 
            return 0;
        } 
        else 
        {
            while ((strcmp(again, "Y") != 0) || (strcmp(again, "N") != 0))
                {
                    printf("OMG! Just write Y (yes) / N (no) \n");
                    printf("\nDo you want to try again? (Y / N): ");
                    scanf("%s", &again);
                    if (strcmp(again, "Y") == 0)
                    {
                        break;
                    } else if (strcmp(again, "N") == 0){ 
                        return 0;
                    } else {
                        continue;
                    }
                }
        continue;
        }
    }
    return 0;
}
