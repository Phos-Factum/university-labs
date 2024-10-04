#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Объявление типа функции
typedef double (*FuncPointer)(double);

// Функция для нахождения среднего значения функции на массиве
double average(FuncPointer func, double arr[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += func(arr[i]); // Вызываем функцию, переданную через указатель
    }
    return sum / n;
}

// Пример функции, которую можно использовать
double square(double x) {
    return x * x;
}

// Функция для безопасного ввода числа
double safeInput() {
    double num;
    bool validInput = false;
    while (!validInput) {
        if (scanf("%lf", &num) != 1) { // Если ввод не является числом
            printf("Invalid input. Please enter a number: ");
            while (getchar() != '\n'); // Очистка входного буфера
        } else {
            validInput = true;
        }
    }
    return num;
}

int main() {
    while (1) {
        char again;
        int n;
        
        // Запрос у пользователя количества чисел в массиве
        printf("Enter the number of elements in the array: ");
        scanf("%d", &n);
        
        // Выделение памяти под массив
        double *arr = (double*)malloc(n * sizeof(double));
        
        // Проверка на успешное выделение памяти
        if (arr == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }
        
        // Запрос у пользователя каждого числа и добавление его в массив
        printf("Enter the elements of the array:\n");
        for (int i = 0; i < n; i++) {
            printf("Enter element %d: ", i + 1);
            arr[i] = safeInput(); // Используем безопасный ввод числа
        }

        // Вызываем функцию average и передаем в нее указатель на функцию square
        double avg = average(square, arr, n);
        printf("Average of the square of the array elements: %lf\n", avg);

        // Освобождение памяти, выделенной под массив
        free(arr);
        
        // Проверка на повторение
        printf("\n\033[0;32mRepeat program? \033[0m(Y, y -- yes / other -- no) \nAnswer: ");
        scanf(" %c", &again);
        if ((again != 'Y') && (again != 'y')) {
            break;
        }
    }
    return 0;
}
