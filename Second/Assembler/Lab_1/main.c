#include <stdio.h>

extern void calc_signed_expression(char a, char b, int d);
extern void calc_unsigned_expression(unsigned char a, unsigned char b, unsigned int d); // Исправлено

long long numerator;
long long denominator;
long long result;

int main() {
    // Знакованные данные
    char a_signed, b_signed;
    int d_signed;

    printf("Введите a (signed char, -128 до 127): ");
    scanf("%hhd", &a_signed);

    printf("Введите b (signed char, -128 до 127): ");
    scanf("%hhd", &b_signed);

    printf("Введите d (signed int): ");
    scanf("%d", &d_signed);

    // Вызов функции на ассемблере
    calc_signed_expression(a_signed, b_signed, d_signed);
    printf("Знаковые данные:\n");
    printf("Числитель: %lld\n", numerator);
    printf("Знаменатель: %lld\n", denominator);
    printf("Результат: %lld\n", result);

    // Беззнаковые данные
    unsigned char a_unsigned, b_unsigned;
    unsigned int d_unsigned;

    printf("Введите a (unsigned char, 0 до 255): ");
    scanf("%hhu", &a_unsigned);

    printf("Введите b (unsigned char, 0 до 255): ");
    scanf("%hhu", &b_unsigned);

    printf("Введите d (unsigned int): ");
    scanf("%u", &d_unsigned);

    // Вызов функции на ассемблере
    calc_unsigned_expression(a_unsigned, b_unsigned, d_unsigned);
    printf("Беззнаковые данные:\n");
    printf("Числитель: %lld\n", numerator);
    printf("Знаменатель: %lld\n", denominator);
    printf("Результат: %lld\n", result);

    return 0;
}

