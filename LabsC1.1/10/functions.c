#include "stdio.h"
#include "stdlib.h"

struct Worker {
	char name[30];
	char famName[30];
	char surName[30];
	char post[30];
	int year;
	};

void inputWorker(struct Worker *workers, int n) 
{
    for (int i = 0; i < n; i++) {
        printf("\n\033[0;32mInfo about worker %d:\033[0m\n", i + 1);
        printf("First name: ");
        scanf("%s", workers[i].name);
        printf("Family name: ");
        scanf("%s", workers[i].famName);
        printf("Surname: ");
        scanf("%s", workers[i].surName);
        printf("Post: ");
        scanf("%s", workers[i].post);
        printf("Year: ");
        scanf("%d", &workers[i].year);
    }
}

void display(struct Worker *workers, int n, int k) 
{
    printf("\n\033[0;32mWorker(s) with '%d and more' year(s) of job experience here:\033[0m\n", k);
    for (int i = 0; i < n; i++) {
        if (workers[i].year >= k) {
            printf("First name: %s,\nFamily Name: %s,\n" 
           	"Surname: %s,\nPost: %s,\nYear: %d.\n",
            workers[i].name, workers[i].famName, workers[i].surName,
            workers[i].post, workers[i].year);
            printf("\n");
        }
    }
}