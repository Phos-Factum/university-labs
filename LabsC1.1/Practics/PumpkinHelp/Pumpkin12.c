#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    int height, width, itnum, dor;
    char symbol;
    printf("Enter height:\n");
    scanf("%d", &height);
    printf("Enter width: \n");
    scanf("%d", &width);
    printf("Enter amount (2x): \n");
    scanf("%d", &itnum);
    printf("Enter symbol \n");
    scanf(" %c", &symbol);
    printf("Do you want a spiral downwards or to the right?    (1 / 0) ");
    scanf(" %d", &dor);
    
    if (dor == 1) {
        char x[height];
        for (int i = 1; i <= itnum; i++) {
            for (int indexOfSymbol = 0; indexOfSymbol < height; indexOfSymbol++) {
                int invertedHeight = (height - 1) - indexOfSymbol;
                for (int i = 0; i < indexOfSymbol; i++) {
                    x[i] = ' ';
                    printf("%c", x[i]);
                }
                x[indexOfSymbol] = symbol;
                printf("%c", x[indexOfSymbol]);
                for (int j = indexOfSymbol + 1; j <= invertedHeight; j++) {
                    x[j] = ' ';
                    printf("%c", x[j]);
                }
                for (int i = 1; i <= width; i++) {
                    printf("\n");
                }
            }
            for (int indexOfSymbol = height - 1; indexOfSymbol >= 0; indexOfSymbol--) {
                int invertedHeight = (height - 1) - indexOfSymbol;
                for (int i = 0; i < indexOfSymbol; i++) {
                    x[i] = ' ';
                    printf("%c", x[i]);
                }
                x[indexOfSymbol] = symbol;
                printf("%c", x[indexOfSymbol]);
                for (int j = indexOfSymbol; j <= invertedHeight; j++) {
                    x[j] = ' ';
                    printf("%c", x[j]);
                }
                for (int i = 1; i <= width; i++) {
                    printf("\n");
                }
            }
        }
    }
    else {
        char wave[height][width * itnum];
        int lengthOfWave = (int)sizeof(wave[0]);
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < lengthOfWave; w++) {
                wave[h][w] = ' ';
            }
        }
        for (int w = 0; w < lengthOfWave; w++) {
            int y = abs((w + height - 1) % ((height - 1) * 2) - (height - 1));
            if (y > height || y < 0) {
                continue;
            }
            wave[y][w] = symbol;
        }
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < lengthOfWave; w++) {
                printf("%c", wave[h][w]);
            }
            printf("\n");
        }
    }
}