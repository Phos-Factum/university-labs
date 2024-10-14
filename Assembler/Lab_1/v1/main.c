// main.c

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

// Объявление ассемблерной функции
extern long signed_unsigned_calc(int16_t d, int8_t a, int8_t b, int type);

// Ввод и валидация для signed данных
void input_and_validate_signed(int8_t *a, int8_t *b, int16_t *d) {
    int temp;
    do {
        printf("Enter signed char value for 'a' (-128 to 127): ");
        if (scanf("%d", &temp) != 1 || temp < -128 || temp > 127) {
            printf("Invalid input. Please enter a value in range -128 to 127.\n");
            while (getchar() != '\n'); // Очистка буфера ввода
        } else {
            *a = (int8_t)temp;
            break;
        }
    } while (1);

    do {
        printf("Enter signed char value for 'b' (-128 to 127): ");
        if (scanf("%d", &temp) != 1 || temp < -128 || temp > 127) {
            printf("Invalid input. Please enter a value in range -128 to 127.\n");
            while (getchar() != '\n'); // Очистка буфера ввода
        } else {
            *b = (int8_t)temp;
            break;
        }
    } while (1);

    do {
        printf("Enter signed 16-bit integer for 'd' (-32768 to 32767): ");
        if (scanf("%d", &temp) != 1 || temp < -32768 || temp > 32767) {
            printf("Invalid input. Please enter a value in range -32768 to 32767.\n");
            while (getchar() != '\n'); // Очистка буфера ввода
        } else {
            *d = (int16_t)temp;
            break;
        }
    } while (1);
}

// Ввод и валидация для unsigned данных
void input_and_validate_unsigned(uint8_t *a, uint8_t *b, uint16_t *d) {
    int temp;
    do {
        printf("Enter unsigned char value for 'a' (0 to 255): ");
        if (scanf("%d", &temp) != 1 || temp < 0 || temp > 255) {
            printf("Invalid input. Please enter a value in range 0 to 255.\n");
            while (getchar() != '\n'); // Очистка буфера ввода
        } else {
            *a = (uint8_t)temp;
            break;
        }
    } while (1);

    do {
        printf("Enter unsigned char value for 'b' (0 to 255): ");
        if (scanf("%d", &temp) != 1 || temp < 0 || temp > 255) {
            printf("Invalid input. Please enter a value in range 0 to 255.\n");
            while (getchar() != '\n'); // Очистка буфера ввода
        } else {
            *b = (uint8_t)temp;
            break;
        }
    } while (1);

    do {
        printf("Enter unsigned 16-bit integer for 'd' (0 to 65535): ");
        if (scanf("%d", &temp) != 1 || temp < 0 || temp > 65535) {
            printf("Invalid input. Please enter a value in range 0 to 65535.\n");
            while (getchar() != '\n'); // Очистка буфера ввода
        } else {
            *d = (uint16_t)temp;
            break;
        }
    } while (1);
}

// Функция для проверки деления на ноль и переполнения
void check_division_and_overflow(int32_t numerator, int32_t denominator) {
    if (denominator == 0) {
        printf("\nError: Division by zero detected. Program will terminate.\n");
        exit(EXIT_FAILURE); // Завершение программы с ошибкой
    }
    // Проверка на переполнение
    if ((numerator == INT32_MIN && denominator == -1) || (numerator > INT32_MAX || numerator < INT32_MIN)) {
        printf("\nError: Integer overflow detected. Program will terminate.\n");
        exit(EXIT_FAILURE); // Завершение программы с ошибкой
    }
}

int main() {
    int8_t a_signed, b_signed;
    int16_t d_signed;
    uint8_t a_unsigned, b_unsigned;
    uint16_t d_unsigned;

    int32_t signed_numerator, signed_denominator, signed_result;
    uint32_t unsigned_numerator, unsigned_denominator, unsigned_result;

    // Ввод и валидация для signed данных
    printf("Input values for signed data:\n");
    input_and_validate_signed(&a_signed, &b_signed, &d_signed);

    // Ввод и валидация для unsigned данных
    printf("\nInput values for unsigned data:\n");
    input_and_validate_unsigned(&a_unsigned, &b_unsigned, &d_unsigned); 

    // Проверка, чтобы избежать деления на ноль
    if (a_signed == 0 || b_signed == 0) {
        printf("\nError: Division by zero detected in signed values. Program will terminate.\n");
        return 0;
    }

    if (a_unsigned == 0 || b_unsigned == 0) {
        printf("\nError: Division by zero detected in unsigned values. Program will terminate.\n");
        return 0;
    }

    // Расчёты для программы на C
    signed_numerator = (2 * d_signed - (96 / a_signed)); // Убедитесь, что деление идёт как ожидалось
    signed_denominator = ((34 / b_signed) - a_signed + 1); // Используйте скобки для ясности
    check_division_and_overflow(signed_numerator, signed_denominator); // Проверка на ноль и переполнение
    signed_result = signed_numerator / signed_denominator;

    unsigned_numerator = (2 * d_unsigned - (96 / a_unsigned));
    unsigned_denominator = ((34 / b_unsigned) - a_unsigned + 1);
    check_division_and_overflow(unsigned_numerator, unsigned_denominator); // Проверка на ноль и переполнение
    unsigned_result = unsigned_numerator / unsigned_denominator;

    // Вызов ассемблерной функции для знаковых значений
    long signed_output = signed_unsigned_calc(d_signed, a_signed, b_signed, 1); // Тип 1 для signed
    // Вызов ассемблерной функции для беззнаковых значений
    long unsigned_output = signed_unsigned_calc(d_unsigned, a_unsigned, b_unsigned, 0); // Тип 0 для unsigned

    // Вывод значений, посчитанных в программе на C
    printf("\nC program results for signed values:\n");
    printf("Numerator = %d, Denominator = %d, Result = %d\n", signed_numerator, signed_denominator, signed_result);
    printf("Assembler results for signed values: %ld\n", signed_output);

    printf("\nC program results for unsigned values:\n");
    printf("Numerator = %u, Denominator = %u, Result = %u\n", unsigned_numerator, unsigned_denominator, unsigned_result);
    printf("Assembler results for unsigned values: %ld\n", unsigned_output);

    return 0;
}

