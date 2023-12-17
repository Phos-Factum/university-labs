#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "time.h"


void checkingMatrix(char *x, char *y)
{
	printf("\033[0;36m");
	printf("Let initialize a matrix 'x * y'.\n");
	printf("\033[0m");
	printf("\nEnter x: (0 < x <= 5)\nx: ");	
	scanf(" %c", x);
	if ( (*x != '1') && (*x != '2') && (*x != '3') && (*x != '4') && (*x != '5') )
	{
		while ( (*x != '1') && (*x != '2') && (*x != '3') && (*x != '4') && (*x != '5') )
		{
			printf("What is that?");
			printf("\nEnter x: (0 < x <= 5)\nx: ");	
			scanf(" %c", x);
		}
	}
	printf("\nEnter y: (0 < y <= 5)\ny: ");	
	scanf(" %c", y);
	if ( (*y != '1') && (*y != '2') && (*y != '3') && (*y != '4') && (*y != '5') )
	{
		while ( (*y != '1') && (*y != '2') && (*y != '3') && (*y != '4') && (*y != '5') )
		{
			printf("What is that?");
			printf("\nEnter y: (0 < y <= 5)\ny: ");	
			scanf(" %c", y);
		}
	}

	printf("\nMatrix %cx%c have been sucessfully created!\n", *x, *y); 
}

void createRandomMatrix(int x, int y, int matrix[x][y]) 
{
    srand(time(NULL));
    int end;
    printf("Choose the high border of a matrix (0 < end <= 5): ");
    scanf("%d", &end);
    if (end < 1 || end > 5)
    {
    	while (end < 1 || end > 5)
    	{
    		printf("Error! Choose the high border of a matrix (0 < end <= 5): ");
    		scanf("%d", &end);
    	}
    }


    printf("\033[0;31m");
    printf("\nThe resulting matrix is: \n");
    printf("\033[0m");
    for (int i = 0; i < x; i++) 
    {
    	printf("\n");
        for (int j = 0; j < y; j++) 
        {
            matrix[i][j] = (rand() % (end+1));
            printf("%d ", matrix[i][j]);
        }
    }     
}



void createManualMatrix(int x, int y, int matrix[x][y]) 
{
	printf("\033[0;31m");
    printf("\nEnter elements of the matrix (one by one):\n");
    printf("\033[0m");
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\033[0;31m");
    printf("\nThe resulting matrix is: \n");
    printf("\033[0m");
    for (int i = 0; i < x; i++) 
    {
        for (int j = 0; j < y; j++) 
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void findMedium(int x, int y, int matrix[x][y])
{
	float arrayMedium[y];
	printf("\033[0;31m");
	printf("\nMediums (of '%d' elements for every column): \n", x);
	printf("\033[0m");
	for (int j = 0; j < y; j++)
	{
		int medium = 0;
		for (int i = 0; i < x; i++)
		{
			medium += matrix[i][j];
		}
		
		printf("%d ", medium);

		arrayMedium[j] = (float)medium / (float)x;

	}
	printf("\n");
	printf("\033[0;31m");
	printf("\nAverage of every column:\n");
	printf("\033[0m");
	for (int i = 0; i < y; i++)
	{
		printf("Column %d: %5.2f\n", i + 1, arrayMedium[i]);
	}
}







// 1. Random generation +
// 2. Сделать обработку нажатия всех левых кнопок +


// void createArray(int x, int y)
// {
// 	srand(time(NULL));
//     int end;
//     printf("\nChoose the high border of array: ");
//     scanf("%d", &end);

// 	int **array = (int**) malloc (x * sizeof (int*));
// 	for (int i = 0; i < x; i++) 
// 	{
// 	  	array[i] = (int*) malloc (y * sizeof (int));
// 	}

// 	printf("The resulting array is: \n");
// 	for (int j = 0; j < y; j++)
// 	{	
// 		printf("\n");
// 		for (int i = 0; i < x; i++)
// 		{
// 			array[i][j] = rand() % (end + 1);
// 			printf("%3d ", array[i][j]);
// 		}
// 	}

// }
