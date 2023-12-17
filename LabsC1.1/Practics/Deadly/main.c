#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "hangman.h"
#include "hangman.c"


int main() {
    srand(time(NULL));

    int difficulty;
    printf("Choose difficulty (1 - easy, 2 - medium, 3 - hard): ");
    scanf("%d", &difficulty);

    int length;
    switch (difficulty) {
        case 1:
            length = 5;
            break;
        case 2:
            length = 7;
            break;
        case 3:
            length = 9;
            break;
        default:
            printf("Error with choosing difficuly. System has chosen standart difficulty (easy).\n");
            length = 5;
    }

    playHangman(length);

    return 0;
}