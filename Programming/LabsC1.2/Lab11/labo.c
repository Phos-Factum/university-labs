#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция для сравнения символов по убыванию в таблице ASCII
int compareChars(const void *a, const void *b) {
    return (*(char *)b) - (*(char *)a);
}

int main() {
    FILE *inputFile = fopen("input3.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    char buffer[1000];   // Буфер для чтения строки из файла

    // Читаем строки из файла
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        // Удаляем символ новой строки, если он присутствует
        char *newline = strchr(buffer, '\n');
        if (newline != NULL) *newline = '\0';

        // Сортируем символы в строке по убыванию
        qsort(buffer, strlen(buffer), sizeof(char), compareChars);

        // Записываем отсортированную строку в новый файл
        fprintf(outputFile, "%s\n", buffer);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Sorting completed.\n");

    return 0;
}
