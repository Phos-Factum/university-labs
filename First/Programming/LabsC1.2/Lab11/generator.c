#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Генерирует случайное действительное число в заданном диапазоне
double random_double(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

// Генерирует файл с исходными данными
void generate_input_file(const char* filename, int num_lines, int max_numbers_per_line, double min_value, double max_value) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error while openning file.\n");
        return;
    }

    // Задаем seed для генерации случайных чисел
    srand(time(NULL));

    // Генерируем каждую строку файла
    for (int i = 0; i < num_lines; i++) {
        // Генерируем случайное количество чисел для каждой строки
        int num_numbers = rand() % max_numbers_per_line + 1;
        // Генерируем числа и записываем их в строку через пробел
        for (int j = 0; j < num_numbers; j++) {
            double number = random_double(min_value, max_value);
            fprintf(file, "%.2f ", number); // "%.2f" используется для вывода чисел с двумя десятичными знаками
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    const char* filename = "input2.txt";
    int num_lines = 40;
    int max_numbers_per_line = 4;
    double min_value = -100.0;
    double max_value = 100.0;

    generate_input_file(filename, num_lines, max_numbers_per_line, min_value, max_value);
    printf("Generated file '%s' with %d string of random numbers.\n", filename, num_lines);

    return 0;
}