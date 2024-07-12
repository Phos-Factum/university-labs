#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Функция очистки буффера для scanf()
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
            printf("\nError occured! Please try again: ");
        }
        
    }
    return c;
}

//замена гласных
void replaceVowels(char word[]) {
    int len = strlen(word);
    int counter;
    char newWord[len];
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

        //луп замены гласной
        while (1) {
            printf("\nChoose a vowel to change: ");
            c = checkChar();
            Clear();

            counter = 0;
            for (int i = 0; i < len; i++) {
                if (vowels[i] == c) {
                    printf("Change to what?: ");
                    vowels[i] = checkChar();
                    Clear();
                }
                else {
                    counter++;
                }
            }

            if (counter == len) {
                printf("No such vowel in the word! Try again.");
            }
            else {
                break;
            }
        }
        

        int key;
        printf("\nDone(Y - yes | N - no)? - ");
        //луп выбора действия
        while (1){
            char newChar = checkChar();
            Clear();
            if (newChar == 'Y' || newChar == 'y') {
                key = 1;
                for (int i = 0; i < len; i++) {
                    if (isVowel(vowels[i])) {
                        newWord[i] = vowels[i];
                    }
                    else {
                        newWord[i] = word[i];
                    }
                }
                break;
            }
            else if (newChar == 'N' || newChar == 'n') {
                break;
            }
            else {
                printf("Error occured! Please try again: ");
            }
        }
        if (key == 1) {
            break;
        }
    }
    
    printf("\nFinal word: ");
    for (int i = 0; i < len; i++) {
            printf("%c", newWord[i]);
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
            printf("\nWord \"%s\" has a vowel. Do you wish to change vowels(Y - yes | N - no)?", token);
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
                    printf("Error occured! Please try again: ");
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
        printf("\n\nEnter 1 to start the programm\nEnter 0 to exit.\nYour choice: ");
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