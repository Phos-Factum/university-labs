#include "stdio.h"
#include "stdlib.h"
#include "functions.h"
#include "functions.c"

int main() 
{
    char again;
    while (1) {

    	system("cls");

    	// Entering count of workers
    	int n;
        printf("\033[0;36mEnter count of workers: \033[0m");
        scanf("%d", &n);
        while (n < 0) 
        {
            printf("\033[0;31m(Error!) Number of workers should be '>= 0'\033[0m\n");
            printf("\033[0;36mEnter count of workers: \033[0m");
            scanf("%d",&n);
        }
        if (n == 0) 
        {
        	printf("\033[0;32mSee you soon!\033[0m"); 
        	break;
        }

        // Creatring an array of structures and memory allocating
        struct Worker *workers = (struct Worker*)malloc(n * sizeof(struct Worker));
        if (workers == NULL) 
        {
    		perror("\033[0;31mMemory allocation failed\033[0m");
    		exit(EXIT_FAILURE);
		}

		// Input info about workers
        inputWorker(workers, n);

        // Main task (k input) and displaying it
        int k;
        printf("\n\033[0;36mEnter condition of 'k' (years on work): \033[0m");
        scanf("%d", &k);

        // Displaying this information and releasing memory
        display(workers, n, k);
        free(workers);

        // Checking for repetiotion of program
        printf("\n\033[0;33mRepeat program? \033[0m('y'/'Y' --- yes / other --- no)\nAnswer: ");
        scanf(" %c", &again);
        if ( (again != 'y') && (again != 'Y') )
        {
            break;
        } 
        
    }
    return 0;
}