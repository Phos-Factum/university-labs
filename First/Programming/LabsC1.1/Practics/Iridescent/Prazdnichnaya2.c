#include <stdio.h>
#include <math.h>

//Вариант №11:
//Составить программу, которая для заданного числа от 1 до 12 выводит его отображение римскими числами.

int main(){
    while (1){
        int count, a;
        printf("Enter a number from 1 to 12: ");
        scanf("%d", &count);
        if ( (count < 1) || (count > 12) ){
            printf("You've entered invalid value. Please, try again! ");
        } 

        if (count == 1){
            printf("I");
        } else if (count == 2){
            printf("II");
        } else if (count == 3){
            printf("III");
        } else if (count == 4){
            printf("IV");
        } else if (count == 5){
            printf("V");
        } else if (count == 6){
            printf("VI");
        } else if (count == 7){
            printf("VII");
        } else if (count == 8){
            printf("VIII");
        } else if (count == 9){
            printf("IX");
        } else if (count == 10){
            printf("X");
        } else if (count == 11){
            printf("XI");
        } else if (count == 12){
            printf("XII");
        }
    printf("\n");
    printf("Wanna continue? (1 - yes / 0 - no) ");
    scanf("%d", &a);
    if (a == 1){
        continue;
    } else{break;}
    } 

    return 0;
}

