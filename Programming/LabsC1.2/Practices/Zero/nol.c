#include "stdio.h"
#include "string.h"

int sec(){
    printf("\nThis strange task...\n\n\n");
    char str[6] = "Hello";
    printf("%s\n",str);
    for (int i = 0;i < sizeof(str);i++){

        printf("Adress of %d element - %p\n",i,&str[i]);
        printf("%d is %c = ASCII %d\n", i, str[i], str[i]);
    }
    printf("\n%d - size (bytes)\n%d - length of word\n",sizeof(str),strlen(str));

    return 0;
}

int main()
{
    sec();
}
