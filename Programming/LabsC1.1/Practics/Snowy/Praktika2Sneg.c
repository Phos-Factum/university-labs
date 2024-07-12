#include <stdio.h>


int main(){
    FILE *file;
    char name[] = "snow.txt";
    if ((file = fopen(name, "r")) == NULL){
        printf("Не удалось открыть файл");
        getchar();
        return 0;
    } else {
        printf("Success!");
    }
    // открыть файл удалось
    // требуемые действия над данными
    fclose(file);
    getchar();
    return 0;
}
// Открыть файл, считать значения с файла, а также вывести этот файл
// Написать в начале программы где наврала А.В.