#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Прототип функции для вычисления среднего арифметического чисел в строке
double averageInLine(const char *line);

// Определение типа файла
enum FileType {
    NUMERIC,
    ALPHABETIC,
    ALPHANUMERIC
};

// Функция для определения типа строки (числовая, символьная или символьно-числовая)
enum FileType detectFileType(const char *line) {
    int hasDigit = 0;
    int hasAlpha = 0;
    int i;

    // Проверяем наличие цифр и букв в строке
    for (i = 0; line[i] != '\0'; i++) {
        if (isdigit(line[i]))
            hasDigit = 1;
        if (isalpha(line[i]))
            hasAlpha = 1;
    }

    // Определяем тип файла на основе наличия цифр и букв
    if (hasDigit && hasAlpha)
        return ALPHANUMERIC;
    else if (hasDigit)
        return NUMERIC;
    else
        return ALPHABETIC;
}

// Функция для сравнения числовых строк по убыванию среднего арифметического
int compareNumericLines(const void *a, const void *b) {
    const char *line1 = *(const char **)a;
    const char *line2 = *(const char **)b;

    double avg1 = averageInLine(line1);
    double avg2 = averageInLine(line2);

    if (avg1 < avg2) return 1;
    if (avg1 > avg2) return -1;
    return 0;
}

// Функция для вычисления среднего арифметического чисел в строке
double averageInLine(const char *line) {
    double sum = 0;
    int count = 0;
    char *token;
    char *line_copy = strdup(line); // Создаем копию строки для безопасного использования в strtok

    // Используем функцию strtok для преобразования строкового представления числа в double
    token = strtok(line_copy, " ");
    while (token != NULL) {
        // Преобразуем токен в число только если это возможно
        double num;
        if (sscanf(token, "%lf", &num) == 1) {
            sum += num;
            count++;
        }
        token = strtok(NULL, " "); // передаем NULL, чтобы продолжить разбор той же строки
    }

    free(line_copy); // Освобождаем память, выделенную для копии строки
    return (count > 0) ? sum / count : 0; // Проверяем деление на ноль
}

// Функция для сравнения символов по убыванию в таблице ASCII
int compareChars(const void *a, const void *b) {
    return (*(char *)b) - (*(char *)a);
}

int main() {
    FILE *inputFile = fopen("input1.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    char buffer[1000];   // Буфер для чтения строки из файла
    char *numericLines[100]; // Массив указателей на числовые строки
    int numericCount = 0; // Счетчик числовых строк

    // Читаем строки из файла
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        // Удаляем символ новой строки, если он присутствует
        char *newline = strchr(buffer, '\n');
        if (newline != NULL) *newline = '\0';

        // Проверяем тип файла
        enum FileType fileType = detectFileType(buffer);

        // Если файл числовой, сохраняем его в отдельный массив и продолжаем
        if (fileType == NUMERIC) {
            numericLines[numericCount] = strdup(buffer);
            numericCount++;
            continue;
        }

        // Если файл текстовый, сортируем символы в строке по убыванию
        qsort(buffer, strlen(buffer), sizeof(char), compareChars);

        // Записываем отсортированную строку в новый файл
        fprintf(outputFile, "%s\n", buffer);
    }

    // Сортируем числовые строки в порядке убывания среднего арифметического
    qsort(numericLines, numericCount, sizeof(char *), compareNumericLines);

    // Записываем отсортированные средние арифметические в новый файл
    for (int i = 0; i < numericCount; i++) {
        fprintf(outputFile, "%.2f\n", averageInLine(numericLines[i]));
        free(numericLines[i]); // Освобождаем память, выделенную для каждой строки
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Sorting completed.\n");

    return 0;
}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Прототип функции для вычисления среднего арифметического чисел в строке
double averageInLine(const char *line);

// Определение типа файла
enum FileType {
    NUMERIC,
    ALPHABETIC,
    ALPHANUMERIC
};

// Функция для определения типа строки (числовая, символьная или символьно-числовая)
enum FileType detectFileType(const char *line) {
    int hasDigit = 0;
    int hasAlpha = 0;
    int i;

    // Проверяем наличие цифр и букв в строке
    for (i = 0; line[i] != '\0'; i++) {
        if (isdigit(line[i]))
            hasDigit = 1;
        if (isalpha(line[i]))
            hasAlpha = 1;
    }

    // Определяем тип файла на основе наличия цифр и букв
    if (hasDigit && hasAlpha)
        return ALPHANUMERIC;
    else if (hasDigit)
        return NUMERIC;
    else
        return ALPHABETIC;
}

// Функция для сравнения числовых строк по убыванию среднего арифметического
int compareNumericLines(const void *a, const void *b) {
    const char *line1 = *(const char **)a;
    const char *line2 = *(const char **)b;

    double avg1 = averageInLine(line1);
    double avg2 = averageInLine(line2);

    if (avg1 < avg2) return 1;
    if (avg1 > avg2) return -1;
    return 0;
}

// Функция для вычисления среднего арифметического чисел в строке
double averageInLine(const char *line) {
    double sum = 0;
    int count = 0;
    char *token;
    char *line_copy = strdup(line); // Создаем копию строки для безопасного использования в strtok

    // Используем функцию strtok для преобразования строкового представления числа в double
    token = strtok(line_copy, " ");
    while (token != NULL) {
        // Преобразуем токен в число только если это возможно
        double num;
        if (sscanf(token, "%lf", &num) == 1) {
            sum += num;
            count++;
        }
        token = strtok(NULL, " "); // передаем NULL, чтобы продолжить разбор той же строки
    }

    free(line_copy); // Освобождаем память, выделенную для копии строки
    return (count > 0) ? sum / count : 0; // Проверяем деление на ноль
}

// Функция для сравнения символов по убыванию в таблице ASCII
int compareChars(const void *a, const void *b) {
    return (*(char *)b) - (*(char *)a);
}

int main() {
    FILE *inputFile = fopen("input1.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    char buffer[1000];   // Буфер для чтения строки из файла
    char *numericLines[100]; // Массив указателей на числовые строки
    int numericCount = 0; // Счетчик числовых строк
    int numericFilePrinted = 0; // Флаг для вывода сообщения о числовом файле
    int alphabeticFilePrinted = 0; // Флаг для вывода сообщения о алфавитном файле
    int alphanumericFilePrinted = 0; // Флаг для вывода сообщения о алфанумерическом файле

    // Читаем строки из файла
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        // Удаляем символ новой строки, если он присутствует
        char *newline = strchr(buffer, '\n');
        if (newline != NULL) *newline = '\0';

        // Проверяем тип файла
        enum FileType fileType = detectFileType(buffer);

        // Если файл числовой, сохраняем его в отдельном массиве и продолжаем
        if (fileType == NUMERIC) {
            if (!numericFilePrinted) {
                printf("Processing numeric file...\n");
                numericFilePrinted = 1;
            }
            numericLines[numericCount] = strdup(buffer);
            numericCount++;
            continue;
        }

        // Если файл текстовый и еще не выведено сообщение о нем
        if (fileType == ALPHABETIC && !alphabeticFilePrinted) {
            printf("Processing alphabetic file...\n");
            alphabeticFilePrinted = 1;
        }

        // Если файл алфавитно-цифровой и еще не выведено сообщение о нем
        if (fileType == ALPHANUMERIC && !alphanumericFilePrinted) {
            printf("Processing alphanumeric file...\n");
            alphanumericFilePrinted = 1;
        }

        // Сортируем символы в строке по убыванию
        qsort(buffer, strlen(buffer), sizeof(char), compareChars);

        // Записываем отсортированную строку в новый файл
        fprintf(outputFile, "%s\n", buffer);
    }

    // Сортируем числовые строки в порядке убывания среднего арифметического
    qsort(numericLines, numericCount, sizeof(char *), compareNumericLines);

    // Записываем отсортированные средние арифметические в новый файл
    for (int i = 0; i < numericCount; i++) {
        fprintf(outputFile, "%.2f\n", averageInLine(numericLines[i]));
        free(numericLines[i]); // Освобождаем память, выделенную для каждой строки
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Sorting completed.\n");

    return 0;
}
