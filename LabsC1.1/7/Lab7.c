#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "functions.h"	// header file
#include "functions.c"	// functions file

int main(void)
{

	while (1)
	{

		//// Main func

		// n (array dimension) entering and checking
		int n;

		printf("Choose the dimension of arrays (a, b, c): (>= 20)\nDimension: ");
		scanf("%d", &n);
		if (n < 20) 
		{
			while(n < 20) 
			{
				printf("\n(Error) Hey, you need to choose 'dim >= 20'!\n");
				printf("Choose the dimension of an arrays (a, b, c): (>= 20)\nDimension: ");
				scanf("%d", &n);
			}
		}

		// Arrays initialization and filling (random / manual)
		int *array1;
		int *array2;
		int *array3;
		
		array1 = (int*)malloc(n * sizeof(int));
		array2 = (int*)malloc(n * sizeof(int));
		array3 = (int*)malloc(n * sizeof(int));

		char randChoice;

		printf("\nFill arrays randomly or manually? "
			"('r' or 'R' -- randomly / other -- manually)\nAnswer: ");
		scanf(" %c", &randChoice);
		if (randChoice == 'r' || randChoice == 'R') 
		{
			createRandomArray(n, array1, 'a');
			createRandomArray(n, array2, 'b');
			createRandomArray(n, array3, 'c');
		} 
		else
		{
			createManualArray(n, array1, 'a');
			createManualArray(n, array2, 'b');
			createManualArray(n, array3, 'c');
		}
		printArray(n, array1, 'a');
		printArray(n, array2, 'b');
		printArray(n, array3, 'c');

		// a', b' and c' arrays initialization, normalize and output
		double *array11;
		double *array22;
		double *array33;
		
		array11 = (double*)malloc(n * sizeof(double));
		array22 = (double*)malloc(n * sizeof(double));
		array33 = (double*)malloc(n * sizeof(double));

		normalizeArray(array1, array11, n, 'A');
		normalizeArray(array2, array22, n, 'B');
		normalizeArray(array3, array33, n, 'C');

		// x and y arrays initialization, normalization and output
		double *x;
		double *y;

		x = (double*)malloc(n * sizeof(double));
		y = (double*)malloc(n * sizeof(double));


		finalizeArray(x, n, array11, array22, 'X');
		finalizeArray(y, n, array22, array33, 'Y');

		// Putting arrays into the file array.txt
		FILE *file;
		file = fopen("array.txt", "w");
		fprintf(file, "Array 'A': ");
		for (int i = 0; i < n; i++)
		{
			fprintf(file, "%5.3f ", array11[i]);
		}
		fprintf(file, "\nArray 'B': ");
		for (int i = 0; i < n; i++)
		{
			fprintf(file, "%5.3f ", array22[i]);
		}
		fprintf(file, "\nArray 'C': ");
		for (int i = 0; i < n; i++)
		{
			fprintf(file, "%5.3f ", array33[i]);
		}
		fprintf(file, "\nArray 'x': ");
		for (int i = 0; i < n; i++)
		{
			fprintf(file, "%5.3f ", x[i]);
		}
		fprintf(file, "\nArray 'y': ");
		for (int i = 0; i < n; i++)
		{
			fprintf(file, "%5.3f", y[i]);
		}
		fclose(file);

		//// Main func (end)

		//// Checking for program reiteration
		char again;
		printf("\nDo you want to try again? ('y' or 'Y' -- yes / other -- no)\n");
		printf("Answer: ");
		scanf(" %c", &again);
		if (again != 'Y' && again != 'y')
		{
			break;
		} 
		else 
		{
			continue;
		}
		//// Checking for program reiteration (end)
	}

	return 0;
}


// --- Задания --- //
// 0. + Прочитать методичку ещё раз (рекомендации)
// 1. + Оформить инициализацию исходных массивов a, b, c
// 2. + Оформить нормирование массивов a, b, c (три формулы расписать)
// 3. + Получить массивы x, y
// 4. + Вывести на экран массивы x, y

// --- Защита --- //
// 1. + Сколько места занимает пустой одномерный массив (4 на длину массива,
//4 на длину массива и 8 на дескриптор (то есть на значение массива). 
//Итого: 16 байт занимает пустой массив)
// 2. + Перевести статику в динамику
// 3. + Сделать вывод 5 массивов в отдельный файл

// // -- Код для файла и одного массива -- //
// FILE *file;
// file = fopen("array.txt", "w");
// fprintf(file, "Array 'a': ");
// for (int i = 0; i < n; i++)
// {
// 	fprintf(file, "%d", array1[i]);
// }		
// fclose(file);

// -- Функция для вывода массивов в файл -- //
// FILE *file;
// file = fopen("array.txt", "w");
// writingArraysFile(array11, n, 'A');
// writingArraysFile(array22, n, 'B');
// writingArraysFile(array33, n, 'C');
// writingArraysFile(x, n, 'x');
// writingArraysFile(y, n, 'y');
// fclose(file);