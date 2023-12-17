#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "functions.c"
#include "functions.h"

#define MAX_LENGTH 1000


int main() 
{
    char again;
    while (1)
    {
        // Enter number of lines
        int lineCount;
        system("cls");
        printf("\033[0;36mEnter count of strings: \033[0m");
        scanf("%d", &lineCount);
        if ( (lineCount < 1) || (lineCount > 20) )
        {
            while ( (lineCount < 1) || (lineCount > 20) )
            {
                printf("\n\033[0;31m(Error!) Count of strings shoud be '0 < x <= 20'.\033[0m\n");
                printf("\033[0;36mEnter count of strings: \033[0m");
                scanf("%d", &lineCount);
            }
        }

        // Allocating memory for the text
        while (getchar() != '\n' && getchar() != EOF)       // memory allocating cycle (error preventing)
        {
            char **lines = (char**)malloc(lineCount * sizeof(char *));  
        }
    
        // Entering original text
        char *lines[MAX_LENGTH];
        printf("\n\033[0;32m--- Starting text ---\033[0m\n");
        for (int i = 0; i < lineCount; i++)                 // text input cycle
        {
            char inputText[MAX_LENGTH];
            fgets(inputText, sizeof(inputText), stdin);     
            inputText[strcspn(inputText, "\n")] = 0;        

            lines[i] = strdup(inputText);                   
        }

        // Output fixed text
        printf("\n\033[0;32m--- Fixed text ---\033[0m\n");
        rearrangeWords(lines, lineCount);                   
        for (int i = 0; i < lineCount; i++)                 // memory free cycle
        {              
            free(lines[i]);
        }

        // Repeating program
        printf("\n\033[0;33mRepeat program? \033[0m('y'/'Y' --- yes / other --- no)\nAnswer: ");
        scanf(" %c", &again);
        if ( (again != 'y') && (again != 'Y') )
        {
            break;
        } 
    }

    return 0;
}


// Поменять местами первое и последнее слово в каждой строке. 