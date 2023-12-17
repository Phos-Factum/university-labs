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

        word = strtok(line, " \n");             // разделить по строкам  
        firstWord[i] = word;
        if (word != NULL)
        {
            while (word != NULL)
            {
                goodWords[numCount] = word;
                // printf("%s ", goodWords[numCount]);
                numCount++;

                lastWord[i] = word;
                word = strtok(NULL, " \n");          
            }
        }

        
        goodWords[0] = lastWord[i];
        goodWords[numCount-1] = firstWord[i];

        for (int j = 0; j < numCount; i++)
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




















// printf("\n\nFors: \n");
        // for (int k = 0; k < oddCount; k++) 
        // {
        //     printf("%s ", oddWords[k]);
        // }

        // for (int k = 0; k < evenCount; k++) 
        // {
        //     printf("%s ", evenWords[k]);
        // }

        // printf("\n");