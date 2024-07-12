#include <stdio.h>
#include <string.h>

int main(){
    char c[]="string";
    for (int i=1; i<=7; i++)
    {
        printf("%d. is %c = ASCII %d. address: %p, bytes: %d\n", i, c[i], c[i], (void*)&c[i], sizeof c[i]);
    }
    int length = sizeof c;
    printf("Array length: %d\n", length);

    return 0;
}