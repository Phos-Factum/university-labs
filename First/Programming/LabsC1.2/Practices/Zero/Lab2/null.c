#include <stdio.h>

int main() {
    char str[15] = { 'H', 'e', '\0', 'l', 'o', '\0' };
    printf("\n%s\n", str);
    char *strr = str + 5;
    str[2]=*strr;
    for (int i = 0; i < sizeof(str); i++) {
        printf("'%c' - %p\n", str[i], &str[i]);
    }



    char ch='\0';
    if(ch==str[6]){
        printf("This string has been wroten, so \\0 exists!\n");
    } else { printf("Liar!");}

    int nc = 65;
    printf("\n%c -- %d\n", nc, nc);

printf("Size of \\0: %d",sizeof(ch));
    return 0;
}