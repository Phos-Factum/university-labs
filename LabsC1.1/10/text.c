#include "stdio.h"
#include "stdlib.h"


int main() 
{
    int again;
    while (1) 
    {
        system("cls");
        char text[20];
        fflush(stdin);
        fputs("Enter some number: ", stdout);
        if ( fgets(text, sizeof text, stdin) ) 
        {
            int number;
            if ( sscanf(text, "%d", &number) == 1 ) 
            {
                printf("Number:  %d\n", number);
            }
            else
            {
                printf("Mistake! You've wrote: %s", text);
            }
        }



        // Repeat
        printf("\nChecking for repeat (1 -- yes / other -- no): ");
        scanf("%d", &again);
        if (again != 1)
        {
            break;
        }

    }
    return 0;
}