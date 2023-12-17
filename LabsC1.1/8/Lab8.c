#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "functions.h"
#include "functions.c"

int main()
{

	while(1)
	{
		// Entering variables
		system("cls");
		char x, y;
		char again;

		// Manual / Random matrix creating
		char randChoice;


		checkingMatrix(&x, &y);
		printf("%c   %c   ", x, y);
		int n, m;
		n = x - '0';
		m = y - '0';
		printf("%d   %d   ", n, m);
		int matrix[n][m];

		printf("\nFill arrays randomly or manually? "
			"('r' or 'R' -- randomly / other -- manually)\nAnswer: ");
		scanf(" %c", &randChoice);
		if (randChoice == 'r' || randChoice == 'R') 
		{
			createRandomMatrix(n, m, matrix);
			findMedium(n, m, matrix);
		} 
		else
		{
  			createManualMatrix(n, m, matrix);
  			findMedium(n, m, matrix);
		}

		// Using functions to find and output answer		
  		

  		// Checking for repeat
		printf("\n\033[0;32mRepeat program? \033[0m(Y, y -- yes / other -- no) \nAnswer: ");
        scanf(" %c", &again);
        if ( (again != 'Y') && (again != 'y') ) 
        {
            break;
        }
    }

  	return 0;
}

// int **array = (int**) malloc (sizeof (int*) * x);
// 	for (int i = 0; i < x; i++) 
// 	{
//   		array [i] = (int*) malloc (sizeof (int) * y);
//   	}

// \x1B[33m