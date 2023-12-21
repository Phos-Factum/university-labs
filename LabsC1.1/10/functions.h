#ifndef functions_h
#define functions_h
struct Worker;
void checkingString(char *arg, char workers);
void checkingNumber(char *arg, char workers);
void inputWorker(struct Worker *workers, int n);
void display(struct Worker *workers, int n, int k);
#endif