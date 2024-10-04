#include <math.h>
#include <stdio.h>

int main(){

    int height, width, amount;
    int again;
    while(1){
        // Entering and checking variables
        printf("Enter height: ");
        scanf("%d", &height);
        printf("Enter width: ");
        scanf("%d", &width);
        printf("Enter amount (x2): ");
        scanf("%d", &amount);
        if (height < 1 || width < 1 || amount < 1){
            printf("That triangle doesn't exist. Please, try again!");
            continue;
        }

        // Clearing screen and data output
        printf("\033[0d\033[2J");
        printf("Height: %d \nWidth: %d\nAmount: %d\n", height, width, amount);

        for (int i = 0; i < amount; i++){
            printf("\n");
            for (int j = 0; j < width; j++){
                printf("\n");
                for (int k = 0; k < height; k++){
                    printf("*");
                }
            }
            /*******/
        }

        // Checking for repeat of program
        printf("Do you want to repeat program? (1 - yes / 0 - no) \n");
        scanf("%d", &again);
        printf("\033[0d\033[2J");
        if (again == 1){
            continue;
        } else {
            return 0;
        }
    }
    return 0;
}
