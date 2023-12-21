#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"

struct Worker {
	char name[30];
	char famName[30];
	char surName[30];
	char post[30];
	char year;
	};

void checkingString(char *arg, char workers)
{
    char text[20];
    fflush(stdin);
    fputs(" ", stdout);
    if ( fgets(text, sizeof text, stdin) ) 
    {
        int number;
        if ( sscanf(text, "%d", &number) == 1 ) 
        {
            while ( sscanf(text, "%d", &number) == 1 )
            {
                printf("\n(Error!) You've wrote not a string! \n", text);
                fflush(stdin);
                fputs("Try again: ", stdout);
                fgets(text, sizeof text, stdin);
            }   
            printf("\n");
        }
        else
        {
        }
    }
}

void checkingNumber(char *arg, char workers)
{
    char text[20];
    fflush(stdin);
    fputs(" ", stdout);
    if ( fgets(text, sizeof text, stdin) ) 
    {
        int number;
        if (sscanf(text, "%d", &number) != 1) 
        {
            while (sscanf(text, "%d", &number) != 1)
            {
                printf("\n(Error!) You've wrote not a number! \n", text);
                fflush(stdin);
                fputs("Try again: ", stdout);
                fgets(text, sizeof text, stdin);
            }   
            printf("\n");   
        }
    }
}

void inputWorker(struct Worker *workers, int n) 
{
    for (int i = 0; i < n; i++) 
    {
        char arg[20];
        printf("\n\033[0;32mInfo about worker %d:\033[0m\n", i + 1);
        printf("First name:");
        strcpy(arg, "first name");
        checkingString(arg, *workers[i].name);
        workers[i].name =

        printf("\nFamily name:");
        strcpy(arg, "family name");
        checkingString(arg, *workers[i].famName);

        printf("\nFamily name:");
        strcpy(arg, "surname");
        checkingString(arg, *workers[i].surName);

        printf("\nPost:");
        strcpy(arg, "post");
        checkingString(arg, *workers[i].post);

        printf("\nYear:");
        strcpy(arg, "post");
        checkingNumber(arg, workers[i].year);
    }
}

void display(struct Worker *workers, int n, int k) 
{
    printf("\n\033[0;32mWorker(s) with '%d and more' year(s) of job experience here:\033[0m\n", k);
    for (int i = 0; i < n; i++) {
        if ((int)workers[i].year >= k) {
            printf("First name: %s,\nFamily Name: %s,\n" 
           	"Surname: %s,\nPost: %s,\nYear: %s.\n",
            workers[i].name, workers[i].famName, workers[i].surName,
            workers[i].post, &workers[i].year);
            printf("\n");
        }
    }
}