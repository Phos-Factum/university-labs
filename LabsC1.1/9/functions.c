#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_LENGTH 1000

void rearrangeWords(char **lines, int lineCount) 
{
    for (int i = 0; i < lineCount; i++) 
    {
        char *line = lines[i];
        char *word;                             // массив со словами
        char *firstWord[MAX_LENGTH];
        char *lastWord[MAX_LENGTH];
        char *goodWords[MAX_LENGTH];
        int numCount = 0;

        int spaces = 0;
        
        for (int j = 0; j < strlen(line); j++)
        {
            if (lines[i][j] == ' ')
            {
                spaces++;
            }
        }
        printf("%d ", spaces);

        word = strtok(line, " ");             // разделить по строкам  
        firstWord[i] = word;

        while (word != NULL)
        {
            goodWords[numCount] = word;
            numCount++;

            lastWord[i] = word;
            word = strtok(NULL, "\n");          
        }

        
        goodWords[0] = lastWord[i];
        goodWords[numCount - 1] = firstWord[i];

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





































































































































































































































































































































































































































































































































































































































































































