#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int generateRandomNumber(int length) {
    int min = 1;
    int max = 1;
    for (int i = 1; i < length; i++) {
        min *= 10;
        max *= 10;
    }
    max = max * 10 - 1;
    return min + rand() % (max - min + 1);
}

void displayHangman(int incorrectAttempts) {
    printf("\n");
    switch (incorrectAttempts) {
        case 1:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 2:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 3:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 4:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 5:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 6:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf(" / \\  |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        default:
            break;
    }
}

void playHangman(int length) {
    int secretNumber = generateRandomNumber(length);

    char guessedDigits[length + 1];
    for (int i = 0; i < length; i++) {
        guessedDigits[i] = '_';
    }
    guessedDigits[length] = '\0';

    int incorrectAttempts = 0;

    while (1) {
        printf("Guessed number: %s\n", guessedDigits);

        displayHangman(incorrectAttempts);

        printf("Enter count: ");
        char input;
        scanf(" %c", &input);

        int found = 0;
        for (int i = 0; i < length; i++) {
            if (input - '0' == (secretNumber / (int) pow(10, length - i - 1)) % 10) {
                guessedDigits[i] = input;
                found = 1;
            }
        }

        if (found) {
            int allGuessed = 1;
            for (int i = 0; i < length; i++) {
                if (guessedDigits[i] == '_') {
                    allGuessed = 0;
                    break;
                }
            }

            if (allGuessed) {
                printf("Congrats! You have guessed counts %d with %d attempts.\n", secretNumber, incorrectAttempts);
                break;
            }
        } else {
            incorrectAttempts++;
            printf("Not right! Try again.\n");

            if (incorrectAttempts == 6) {
                displayHangman(incorrectAttempts);
                printf("Game Over. Guessed number was: %d\n", secretNumber);
                break;
            }
        }
    }
}