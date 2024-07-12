#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void prove()
{
    char null = '\0';
    char string_with_null[] = "abc";
    printf("A string with a null character: '%s'\n", string_with_null);
    printf("Line length: %d\n", (int)sizeof(string_with_null));

}

void concatenate_strings(char *str1, char *str2) {
    char result[100]; // Результирующая строка, достаточно большая для объединения двух строк
    strcpy(result, str1); // Копируем первую строку в результат
    strcat(result, str2); // Конкатенируем вторую строку к результату
    printf("Concatenation result: '%s'\n", result);
}

void process_string_array(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Error of opening file.\n");
        return;
    }

    char line[100]; // Предположим максимальная длина строки - 100 символов
    FILE *temp_file = fopen("temp_file.txt", "w");
    if (temp_file == NULL) {
        printf("Error of creating file.\n");
        fclose(file);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        // Убираем лишние пробелы
        char *token;
        char *rest = line;
        while ((token = strtok_r(rest, " ", &rest))) {
            fprintf(temp_file, "%s ", token);
        }

        // Заменяем троеточия на восклицательные знаки
        char *ellipsis = strstr(line, "...");
        while (ellipsis != NULL) {
            strcpy(ellipsis, "!!!");
            ellipsis = strstr(line, "...");
        }
        fprintf(temp_file, "%s", line);
    }

    fclose(file);
    fclose(temp_file);
    remove(file_path);
    rename("temp_file.txt", file_path);
}

int main()
{
    prove();

    char string1[] = "Hello";
    char string2[] = "World";
    concatenate_strings(string1, string2);

    const char *file_path = "path_to_file.txt";
    process_string_array(file_path);

    return 0;
}
