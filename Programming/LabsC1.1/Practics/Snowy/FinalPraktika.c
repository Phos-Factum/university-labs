#include <stdio.h> 
#include <string.h>  
 
int open(); 
int create(); 
 
int main() 
{ 
    int k; 
 
    while(1){ 
        printf("\n\nEnter 1 to read a file\nEnter 2 to create a file\nEnter 0 to exit.\nYour choice: "); 
        scanf("%d", &k); 
         
        switch(k) 
        { 
            case 1: 
                open(); 
                break; 
            case 2: 
                create(); 
                break; 
            case 0: 
                return 0; 
                break; 
            default: 
                printf("\n Wrong input! Try again"); 
                break; 
        } 
    } 
    return 0; 
} 
 
int open(){ 
     
    FILE* file; 
    char name[25]; 
    int ch; 
 
    printf("\nEnter the name of the file with it's definition: "); 
    scanf(" %[^\n]s", name); 
 
    file = fopen(name, "r"); 
    if (file == NULL){ 
        printf("\nFile doesn't exist! Create it and try again.\n"); 
        return 0; 
    } 
    else{ 
        printf("\nFile opened successfuly\n"); 
    } 
 
    printf("\nContent of the file: \n"); 
    while (1) { 
        ch = fgetc(file); 
  
        if (feof(file)) 
            break; 
  
        printf("%c", ch); 
    } 
 
    fclose(file); 
 
    return 0; 
} 
 
int create(){ 
 
    FILE* file; 
    char name[25]; 
    char str[50]; 
 
    printf("\nEnter the name for the file: "); 
    scanf(" %[^\n]s", name); 
 
    strcat(name, ".txt"); 
 
    file = fopen(name, "w+"); 
    if (file == NULL){ 
        printf("\nFile creation error! Try again.\n"); 
        return 0; 
    } 
    else{ 
        printf("\n\nFile created successfuly\n"); 
    } 
     
    printf("\nEnter the text to put into the file: "); 
    scanf(" %[^\n]s", str); 
    fprintf(file,"%s\n", str); 
 
    printf("\nYou can find your file in the following directory with the name: C:/Users/Phosphorus/Desktop/University/ProgLabs/MyLabs/Practics/Snejnaya/%s\n", name); 
 
    fclose(file); 
 
    return 0; 
}