#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 50
#define MAX_DATA_LENGTH 100

int main() {
    FILE* file;
    char filename[MAX_FILENAME_LENGTH];
    char buffer[MAX_DATA_LENGTH];
    int data[5] = {10, 20, 30, 40, 50};
    int i;

    // 4.1: Открыть файл с проверкой на наличие
    printf("Введите имя файла для чтения: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Не удалось открыть файл для чтения или файл не существует.\n");
        return 1;
    }

    // 4.2: Считать данные из файла и вывести на экран
    printf("Содержимое файла:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);

    // 4.3: Заполнить массив и вывести его содержимое
    printf("\n\nСодержимое массива:\n");
    for (i = 0; i < 5; i++) {
        printf("%d ", data[i]);
    }

    // 4.4: Записать данные массива в файл
    printf("\n\nВведите имя файла для записи (без расширения): ");
    scanf("%s", filename);

    // Добавить расширение .txt к имени файла
    strcat(filename, ".txt");

    file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Не удалось открыть файл для записи.\n");
        return 1;
    }

    // Записать данные массива в файл
    for (i = 0; i < 5; i++) {
        fprintf(file, "%d\n", data[i]);
    }

    fclose(file);

    // 4.5 и 4.6: Вывести информацию о новом файле
    printf("\nФайл %s успешно создан. Вы можете найти его в текущей директории.\n", filename);

    return 0; // Успешное завершение программы
}