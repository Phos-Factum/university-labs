#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Функция очистки буфера ввода
void Clear(void) {
    while ((getchar()) != '\n');
}

// Функция проверки, является ли символ гласной
int isVowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

// Функция проверки и ввода символа
char checkChar() {
    char c;
    while (1) {
        if (scanf(" %c", &c) == 1) {
            break;
        } else {
            printf("\nError occurred! Please try again: ");
        }
    }
    return c;
}

// Функция замены гласных в слове
char* replaceVowels(char word[]) {
    int len = strlen(word);
    char vowels[len];
    char c;
    int changed = 0;
    char *newWord = strdup(word); // Создаем копию слова для изменений
    
    // Сохраняем гласные в отдельный массив
    for (int i = 0; i < len; i++) {
        if (isVowel(word[i])) {
            vowels[i] = word[i];
        } else {
            vowels[i] = ' ';
        }
    }

    // Цикл для замены гласных
    while (1) {
        printf("Vowels are: ");
        for (int i = 0; i < len; i++) {
            printf("%c", vowels[i]);
        }

        // Цикл для выбора гласной для замены
        while (1) {
            printf("\nChoose a vowel to change: ");
            c = checkChar();
            Clear();

            int found = 0;
            for (int i = 0; i < len; i++) {
                if (vowels[i] == c) {
                    printf("Change to: ");
                    vowels[i] = checkChar();
                    Clear();
                    newWord[i] = vowels[i]; // Заменяем гласную в копии слова
                    found = 1;
                    changed = 1;
                }
            }

            if (!found) {
                printf("No such vowel in the word! Try again.");
            } else {
                break;
            }
        }

        // Спрашиваем пользователя о продолжении
        int key;
        printf("\nDone (Y - yes | N - no)? - ");
        while (1) {
            char newChar = checkChar();
            Clear();
            if (newChar == 'Y' || newChar == 'y') {
                key = 1;
                break;
            } else if (newChar == 'N' || newChar == 'n') {
                break;
            } else {
                printf("Error occurred! Please try again: ");
            }
        }
        if (key == 1) {
            break;
        }
    }
    
    // Если слово было изменено, возвращаем его
    if (changed) {
        return newWord;
    } else {
        return word; // Если слово не было изменено, возвращаем оригинальное слово
    }
}

// Основная логика программы
int Program() {
    char sentence[1000];
    printf("\nEnter a line: ");
    fgets(sentence, sizeof(sentence), stdin);
    
    char *token = strtok(sentence, " ,.!?\n");
    char updatedSentence[1000] = ""; // Инициализируем пустую строку
    
    // Обрабатываем каждое слово в строке
    while (token != NULL) {
        int hasVowel = 0;
        int len = strlen(token);
        
        for (int i = 0; i < len; i++) {
            if (isVowel(token[i])) {
                hasVowel = 1;
                break;
            }
        }
        
        // Если в слове есть гласные, предлагаем замену
        if (hasVowel) {
            printf("\nWord \"%s\" has a vowel. Do you wish to change vowels (Y - yes | N - no)? - ", token);
            while (1) {
                char newChar = checkChar();
                if (newChar == 'Y' || newChar == 'y') {
                    char *replacedWord = replaceVowels(token);
                    strcat(updatedSentence, replacedWord); // Добавляем измененное слово к обновленной строке
                    strcat(updatedSentence, " "); // Добавляем пробел между словами
                    free(replacedWord); // Освобождаем память, выделенную для копии слова
                    break;
                } else if (newChar == 'N' || newChar == 'n') {
                    strcat(updatedSentence, token); // Если пользователь не хочет менять гласные, добавляем слово без изменений
                    strcat(updatedSentence, " "); // Добавляем пробел между словами
                    break;
                } else {
                    printf("Error occurred! Please try again: ");
                }
            }
        } else {
            strcat(updatedSentence, token); // Если в слове нет гласных, добавляем его без изменений
            strcat(updatedSentence, " "); // Добавляем пробел между словами
        }
        
        token = strtok(NULL, " ,.!?\n");
    }
    
    // Выводим окончательную обновленную строку
    printf("\nUpdated sentence: %s\n", updatedSentence);
    
    return 0;
}

// Главное меню
int main() {
    int k;

    while (1) {
        printf("\n\nEnter 1 to start the program\nEnter 0 to exit.\nYour choice: ");
        scanf("%d", &k);
        Clear();
        
        switch(k) {
            case 1:
                Program();
                break;
            case 0:
                return 0;
                break;
            default:
                printf("\nWrong input! Try again");
                break;
        }
    }
}
