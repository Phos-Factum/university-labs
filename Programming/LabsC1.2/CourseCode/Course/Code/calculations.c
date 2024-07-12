// calculations.c

#include "calculations.h"

// Функция для вывода заставки
void print_splash_screen() {
    FILE *f = fopen("screensaver.txt", "r");
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char ch;
    while ((ch = fgetc(f)) != EOF) {
        putchar(ch);
    }

    fclose(f);
}

// Описание функции формирования массива времени form_t
void form_t(int n, float *t, float *dt) {
    float tn = 10, tk = 35;
    *dt = (tk - tn) / (n - 1);
    for (int i = 0; i < n; i++) {
        t[i] = tn + i * (*dt);
    }
}

// Описание функции формирования массива Uvx
void form_Uvx(int n, float *t, float *Uvx) {
    float t1 = 30, a = 12, b = 48;
    for (int i = 0; i < n; i++) {
        if (t[i] < t1)
            Uvx[i] = a * (t[i] - 10);
        else
            Uvx[i] = a * (t1 - 10) - b * (t[i] - t1);
    }
}

// Описание функции формирования массива Uvix
void form_Uvix(int n, float *Uvx, float *Uvix) {
    float Uvx1 = 5, Uvx2 = 25, U1 = 20, U2 = 150;
    for (int i = 0; i < n; i++) {
        if (Uvx[i] < Uvx1)
            Uvix[i] = U1;
        else if (Uvx[i] <= Uvx2)
            Uvix[i] = 6.5 * Uvx[i] - 12.5;
        else
            Uvix[i] = U2;
    }
}
    
// Описание функции вывода данных в виде таблицы form_tabl
void form_tabl(int n, float *t, float *Uvx, float *Uvix) {
    printf("\n**************************************\n");
    printf("* \033[32mNum\033[0m | \033[32m   t   \033[0m|    \033[32mUvx  \033[0m | \033[32m  Uvix  \033[0m *\n");
    printf("**************************************\n");
    for (int i = 0; i < n; i++) {
        printf("* %3d | %6.2f | %8.2f | %8.2f *\n", i + 1, t[i], Uvx[i], Uvix[i]);
    }
    printf("**************************************\n");

}

// Описание функции записи данных в файлы
void write_data_to_files(int n, float *t, float *Uvx, float *Uvix) {
    FILE *ft = fopen("massiv_t.txt", "w");
    FILE *fUvx = fopen("massiv_Uvx.txt", "w");
    FILE *fUvix = fopen("massiv_Uvix.txt", "w");

    for (int i = 0; i < n; i++) {
        fprintf(ft, "%f\n", t[i]);
        fprintf(fUvx, "%f\n", Uvx[i]);
        fprintf(fUvix, "%f\n", Uvix[i]);
    }

    fclose(ft);
    fclose(fUvx);
    fclose(fUvix);

    printf("           Data written to files.\n");
}

// Функция для нахождения времени, при котором Uvx достигает 80 В
float find_time_80V(int n, float *t, float *Uvx) {
    for (int i = 0; i < n; i++) {
        if (Uvx[i] > 80) {
            return t[i];
        }
    }
    return -1; // Возвращаем -1, если Uvx не достигает 80 В
}

// Функция для контрольного расчета для n точек
void control_calculation(int n, float *t, float *Uvx, float *Uvix, int *calculation_done) {
    float dt;
    form_t(n, t, &dt);
    form_Uvx(n, t, Uvx);
    form_Uvix(n, Uvx, Uvix);
    form_tabl(n, t, Uvx, Uvix);
    *calculation_done = 1;
}

void calculate_parameter_with_precision(int n, float *t, float *Uvx, float *Uvix, float time_80V) {
    float eps = 0.01; // Заданная погрешность
    float p = 1; // Текущая погрешность

    while (p > eps) {
        float par1 = time_80V; // Используем time_80V в качестве параметра
        p = fabs(par - par1) / par1;
        printf("\033[32mn:\033[0m %d, \033[32mparameter:\033[0m %f, \033[32mprecision (until 0.01):\033[0m %.2f.\n", n, par1, par1); // Округляем параметр до двух знаков после запятой
        par = par1;
        n *= 2;
    }
}

// Функция для вывода параметров расчета
void show_parameters() {
    float a = 12, b = 48, t1 = 30, tn = 10, tk = 35;
    printf("            \033[34mInitial parameters:\033[0m     ");
    printf("\n         *************************\n");
    printf("         * \033[32mParameter\033[0m | \033[32m   Value \033[0m *\n");
    printf("         *************************\n");
    printf("         * a         | %8.2f  *\n", a);
    printf("         * b         | %8.2f  *\n", b);
    printf("         * t1        | %8.2f  *\n", t1);
    printf("         * tn        | %8.2f  *\n", tn);
    printf("         * tk        | %8.2f  *\n", tk);
    printf("         *************************\n");
}