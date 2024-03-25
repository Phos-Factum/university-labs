#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_LENGTH 1000

void rearrangeWords(char **lines, int lineCount, int letterCount)
{
    for (int i = 0; i < lineCount; i++) 
    {
        char *line = lines[i];
        char *word;                             // массив со словами
        char firstWord[MAX_LENGTH]; // Изменено: хранит само слово
        char lastWord[MAX_LENGTH];  // Изменено: хранит само слово
        char *goodWords[MAX_LENGTH];
        char temp[MAX_LENGTH];
        int numCount = 0;

        int spaces = 0;
        
        // Count spaces
        for (int j = 0; j < strlen(line); j++)
        {
            if (lines[i][j] == ' ')
            {
                spaces++;
            }
        }
        printf("%d spaces: ", spaces);

        // Cut by lines
        word = strtok(line, " ");               
        strcpy(firstWord, word); // Изменено: сохраняем само слово

        while (word != NULL)
        {
            if (strlen(word) != letterCount  && !strchr(word, ' '))
            {
                goodWords[numCount] = word;
                numCount++;
            }
            // goodWords[numCount] = word;
            // numCount++;
            strcpy(lastWord, word); // Изменено: сохраняем само слово
            word = strtok(NULL, " ");          
        }

        // Word-changer
        strcpy(temp, goodWords[0]);
        strcpy(goodWords[0], goodWords[numCount - 1]);
        strcpy(goodWords[numCount - 1], temp);
        
        // Printing output array
        for (int j = 0; j < numCount; j++)
        { 
            if (goodWords[j] != NULL)
            {
                printf("%s ", goodWords[j]);
            }
        }
        printf("\n");
    }

    printf("\n");
}