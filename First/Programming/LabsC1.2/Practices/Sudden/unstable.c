#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Функция очистки буфера для scanf()
void Clear(void) {
    while ((getchar()) != '\n');
}

//проверка на гласную
int isVowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

//ввод с проверкой на гласные
char checkChar() {
    char c;
    while (1) {
        if (scanf(" %c", &c) == 1) {
            break;
        }
        else {
            printf("\nError occurred! Please try again: ");
            Clear();
        }
        
    }
    return c;
}

//замена гласной по номеру
void replaceVowelAtIndex(char word[], int index) {
    int len = strlen(word);
    char newWord[len + 1]; // увеличиваем размер на 1 для завершающего нулевого символа
    char vowels[len];
    int vowelIndex = 0;

    //запись гласных в отдельный массив vowels
    for (int i = 0; i < len; i++) {
        if (isVowel(word[i])) {
            vowels[vowelIndex] = word[i];
            vowelIndex++;
        }
    }

    //замена гласной по индексу
    for (int i = 0; i < len; i++) {
        if (isVowel(word[i])) {
            if (index == 0) {
                printf("Change on: ");
                vowels[i] = checkChar();
                Clear();
            }
            index--;
        }
    }

    //сбор конечного слова
    for (int i = 0, j = 0; i < len; i++) {
        if (isVowel(word[i])) {
            newWord[i] = vowels[j];
            j++;
        }
        else {
            newWord[i] = word[i];
        }
    }
    
    newWord[len] = '\0'; // добавляем завершающий нулевой символ
    printf("\nFinal word: %s\n", newWord);
}

//замена гласных
void replaceVowels(char word[]) {
    int len = strlen(word);
    int counter;
    char newWord[len + 1]; // увеличиваем размер на 1 для завершающего нулевого символа
    char vowels[len];
    char c;
    
    //запись гласных в отдельный массив vowels
    for (int i = 0; i < len; i++) {
        if (isVowel(word[i])) {
            vowels[i] = word[i];
        }
        else {
            vowels[i] = ' ';
        }
    }

    //луп для нескольких замен
    while(1) {
        
        printf("Vowels are: ");
        for (int i = 0; i < len; i++) {
            printf("%c", vowels[i]);
        }

        //луп замены гласной по индексу
        while (1) {
            printf("\nChoose the index of the vowel to change (starting from 1): ");
            int index;
            if (scanf("%d", &index) != 1 || index <= 0) {
                Clear();
                printf("Invalid index! Please try again.\n");
                continue;
            }
            Clear();

            replaceVowelAtIndex(word, index - 1);
            break;
        }

        int key;
        printf("\nDone (Y - yes | N - no)? - ");
        //луп выбора действия
        while (1){
            char newChar = checkChar();
            Clear();
            if (newChar == 'n' || newChar == 'N') {
                key = 1;
                break;
            }
            else if (newChar == 'Y' || newChar == 'y') {
                key = 0;
                break;
            }
            else {
                printf("Error occurred! Please try again: ");
            }
        }
        if (!key) {
            break;
        }
    }
}

//тело программы
int Program() {
    char sentence[100];
    printf("\nEnter a line: ");
    fgets(sentence, sizeof(sentence), stdin);
    
    char *token = strtok(sentence, " ,.!?\n");
    
    //разбитие слова на токены
    while (token != NULL) {
        int hasVowel = 0;
        int len = strlen(token);
        
        for (int i = 0; i < len; i++) {
            if (isVowel(token[i])) {
                hasVowel = 1;
                break;
            }
        }
        //если в слове есть гласные - предложить замену
        if (hasVowel) {
            printf("\nWord \"%s\" has a vowel. Do you wish to change vowels (Y - yes | N - no)? - ", token);
            while (1){
                char newChar = checkChar();
                if (newChar == 'Y' || newChar == 'y') {
                    replaceVowels(token);
                    break;
                }
                else if (newChar == 'N' || newChar == 'n') {
                    break;
                }
                else {
                    printf("Error occurred! Please try again: ");
                }
            }
        }
        
        token = strtok(NULL, " ,.!?\n");
    }
    
    return 0;
}

//меню
int main(){
    int k;

    while(1){
        printf("\n\nEnter 1 to start the program\nEnter 0 to exit.\nYour choice: ");
        scanf("%d", &k);
        Clear();
        
        switch(k)
        {
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



// Фиксировать изменения при попытке поменять несколько букв
// Выводить итоговую строку строку