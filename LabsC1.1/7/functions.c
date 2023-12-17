#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "time.h"


void createRandomArray(int n, int array[], char name) 
{
    srand(time(NULL));
    int end;
    printf("Choose the high border of an array '%c': ", name);
    scanf("%d", &end);
    for (int i = 0; i < n; i++) 
    {
        array[i] = rand() % (end + 1);
    }
}

void createManualArray(int n, int array[], char name)
{
	printf("\nEnter values of array '%c' one by one:\n", name);
	for (int i = 0; i < n; i++) 
	{
		printf("Element %d: ", i + 1);
		scanf("%d", &array[i]);
	}
}

void printArray(int n, int array[], char name) 
{ 	
	printf("Array '%c': ", name);
	for (int i = 0; i < n; i++)
	{
		printf("%d", array[i]);
	}
	printf("\n");
}	

void normalizeArray(int arrayOld[], double arrayNew[], int n, char name)
{
	int sum = 0;
	printf("\nArray '%c': \n", name);

	for (int i = 0; i < n; i++)
	{
		printf("%d", arrayOld[i]);
		for (int j = 0; j <= i; j++)
		{
			sum += abs(arrayOld[j]);
		}
		if (sum == 0)
		{
			arrayNew[i] = (float)0;
		}
		else
		{
			arrayNew[i] = (double)arrayOld[i] / sum;
		}
	}
	printf("\nSum: %d\n", sum);
	for (int i = 0; i < n; i++)
		{ 
			printf("%3.3f\n", arrayNew[i]);
		}
}

void finalizeArray(double x[], int n, double array11[], double array22[], char name)
{
	printf("\n\nFinal array '%c': ", name);
	for (int i = 0; i < n; i++)
	{
		x[i] = array11[i] - array22[i];
		printf("\n%3.3f", x[i]);
	}
	printf("\n");
}

// void writingArraysFile(double array[], int n, char name)
// {	
// 	FILE *file;
// 	fprintf(file, "\nArray 'A': ");
// 	for (int i = 0; i < n; i++)
// 	{
// 		fprintf(file, "%5.3f ", array[i]);
// 	}
// }