#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "time.h"
#define NPOINTS 30

int main() {
    double points[NPOINTS];
    int k;

    printf("%3.1f\n", points[0] = 0.1);
    for(k=1; k < NPOINTS; k++) {
        points[k] = 0.1 + points[k-1];
        printf("%3.1f\n", points[k]);
    }
    return 0;
}
// int normalizeArray(int n, int array1[], int array2[], float array3[])
// {
// 	printf("\nArray 1: \n");
// 	for (int i = 0; i < n; i++)
// 	{
		
// 		printf("%d\n", array1[i]);

// 	}
// 	printf("\nArray 2: \n");
// 	for (int i = 0; i < n; i++)
// 	{

// 		printf("%d\n", array2[i]);

// 	}
// 	printf("\nArray 3: \n");
// 	for (int i = 0; i < n; i++)
// 	{

// 		printf("%.1f\n", array3[i]);

// 	}

// 	return 0;
// }

// int main(void)
// {
// 	printf("Hello!\n");
// 	int n = 5;
// 	int array1[n];
// 	int array2[n];
// 	float array3[n];

// 	printf("Array1: \n");
// 	for (int i = 0; i < 5; i++)
// 	{
// 		printf("%d", array1[i]);
// 	}
	// normalizeArray(n, array1, array2, array3);

// }