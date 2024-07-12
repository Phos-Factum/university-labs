#include <stdio.h>
#include <math.h>

int main(){

    int again;
    while(1){
        // Entering variables and checking 'n' (steps)
        float xS, xE, a, y, i, x;
        int n;
        printf("Enter count of steps: \n"); // It's easier to understand, if u enter 5 steps, to see 5 lines :D
        scanf("%d", &n);
        if (n < 1){
            printf("The STEP is too much small (enter at least 1 and try again)\n");
            continue;
        }

        // Entering and checking variables 'a', 'xS', 'xE' (parameter, beginning and ending)
        printf("Enter a (parameter): \n");
        scanf("%f", &a);
        printf("And now enter the beginning and the end: (2 counts through 'space', the second one must be bigger!)\n");
        scanf("%f %f", &xS, &xE);
        if (xS > xE){
            printf("You must enter first count is bigger, than the second one! \n");
            continue;
        } else if (xS == xE){
            printf("Your start and end are the same. Please, try again! \n");
            continue;
        }


        // Finding the step of cycle 
        i = (xE - xS) / (float)(n-1);

        // Formula e ^ (x + a ^ 1.7) cycle and output
        printf("\033[33m\e[1m      y      |      x     \e[m\033[0m\n");
        printf("\033[33m\e[1m_____________|____________\e[m\033[0m\n");
        for (x = xS; x <= xE; x += i){
            y = exp(x + pow(a, 1.7));
            if (y > 100000){
                printf("This count is too big!\n");
                break;
            }
            
            printf("y = %7.2f, | x = %7.2f\n", y, x); 
        }

        // Checking for repeat
        printf("Do you want to try again? (1 - yes / 0 - no)\n");
        scanf("%d", &again);
        if (again == 1){
            continue;
        } else {
            return 0;
        }
    }

    return 0;
}

//     1 - вывод таблицей (сделано) +
//     2 - заголовок таблицы сделать жёлтым и жирным (сделано) +
//     3 - сделать ручной ввод с проверками (сделано) +
//     4 - обернуть всё циклом while (сделано) +