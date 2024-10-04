// calculations.h

#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define N 1000

void print_splash_screen();
void form_t(int n, float *t, float *dt);
void form_Uvx(int n, float *t, float *Uvx);
void form_Uvix(int n, float *Uvx, float *Uvix);
void form_tabl(int n, float *t, float *Uvx, float *Uvix);
void write_data_to_files(int n, float *t, float *Uvx, float *Uvix);
float parameter(int n, float *t, float *Uvx, float *Uvix);
void control_calculation(int n, float *t, float *Uvx, float *Uvix, int *calculation_done);
void calculate_parameter_with_precision(int n, float *t, float *Uvx, float *Uvix, float time_80V);
float find_time_80V(int n, float *t, float *Uvx);
void show_parameters();

#endif // CALCULATIONS_H
