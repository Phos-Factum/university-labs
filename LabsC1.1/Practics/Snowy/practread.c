#include <stdio.h>
#include <conio.h>

char b[256];
char buffer[256];
int main()
{
    char * filename = "snow.txt";
    printf("File name: ");
    scanf("%s",&b);
    printf("%s",b);
    char * filename2 = ("%c.txt",b);
    FILE *f1 = fopen(filename, "r");
    FILE *f2 = fopen(filename2, "w");

    if(!f1 || !f2)
    {
        printf("Error occured while opening file\n");
    }

    
    

    else
    {
        while((fgets(buffer, 256, f1))!=NULL)
        {
            fputs(buffer, f2);
            printf("%s", buffer);
        }
    }
     
    fclose(f1);
    fclose(f2);
     
    return 0;
}