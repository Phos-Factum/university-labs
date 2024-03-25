#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "locale.h"


int main() {
    setlocale(LC_ALL, "RU");
    // Открыть файл для чтения
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    // Выделить память для массива строк
    char **lines = NULL;
    int num_lines = 0;

    // Читать строки из файла и добавлять их в массив
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Удалить лишние пробелы
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == ' ' && line[i + 1] == ' ') {
                memmove(line + i, line + i + 1, len - i);
                len--;
                i--;
            }
        }

        // Заменить троеточия на восклицательные знаки
        for (int i = 0; i < len; i++) {
            if (line[i] == '.' && line[i + 1] == '.' && line[i + 2] == '.') {
                line[i] = '!';
                line[i + 1] = '!';
                line[i + 2] = '!';
            }
        }

        // Добавить строку в массив
        lines = realloc(lines, (num_lines + 1) * sizeof(char *));
        lines[num_lines] = strdup(line);
        num_lines++;
    }

    // Закрыть файл
    fclose(file);

    // Вывести обработанные строки на экран
    for (int i = 0; i < num_lines; i++) {
        printf("%s", lines[i]);
    }

    // Освободить память
    for (int i = 0; i < num_lines; i++) {
        free(lines[i]);
    }
    free(lines);
    free(lines);

    return EXIT_SUCCESS;
}