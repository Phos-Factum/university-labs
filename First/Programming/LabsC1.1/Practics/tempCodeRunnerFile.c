#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main(void){
    float x,proiz,y;
    int n,cnt = 0,nexx = 1;
    bool contin = true;
    while (contin){
        printf("x = ");
        scanf("%f", &x);
        if (x == -4){
            while (x == -4){
                printf("При x = -4 происходит деление на ноль, что недопустимо. Пожалуйста, измените значение для переменной x:\n");
                printf("x = ");
                scanf("%f", &x);
            }
        }
        printf("n = ");
        scanf("%d", &n);
        
        if (n < 2){
            while (n < 2){
                printf("При n < 2 функция произведения в алгоритме невозможна, пожалуйста, измените значение для переменной n:\n");
                printf("n = ");
                scanf("%d", &n);
            }
        }
        proiz = 1 + pow(2.71, -2/(x + 4));
        printf("Результаты функции произведения:\n");
        printf("%d. %f\n", cnt, proiz);
        for(int i = 3; i <= n; i++){
            proiz *= 1 + pow(2.71, -i/(x + 4));
            cnt += 1;
            printf("%d. %f\n", cnt, proiz);
            
        }
        y = sin(0.01*proiz);
        printf("y = %f\n", y);
        printf("Хотите продолжить вычисления, начав с начала? 0 - да, 1 - нет\n");
        scanf("%d", &nexx);
        if (nexx != 0 & nexx != 1){
            while (nexx != 0 & nexx != 1){
                printf("Видимо, мы промахнулись по кнопке))) Введите число снова.\n");
                printf("Хотите продолжить вычисления, начав с начала? 0 - да, 1 - нет\n");
                scanf("%d", &nexx);
            }
        }
        if (nexx == 0)
            contin = true;
        if (nexx == 1)
            contin = false;
    }
    return 0;
}