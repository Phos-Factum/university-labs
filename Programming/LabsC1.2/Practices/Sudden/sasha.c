#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

char alp[40] = {'a','e','y','u','o','i','A','E','Y','U','O','I'};

char how_much(char *word, char letter[2]){
    int count = 0;

    for (int i = 0; i < strlen(word); i++) {
        if (word[i] == letter[0]) {
            
            count++;
        }
    }

    return count;
   
}

int sort(char *word){
    int c=0;
    
    for (int i=0; i< strlen(word); i++){
        for ( int j=0;j<strlen(alp);j++){
            if (word[i]==alp[j]){
                c=1;
                break;
            }
        
        }
        if (c==1){
            return 0;
            break;
        }
    
    }
    if (c==0){
        return 1;
    }
}
int main()
{
    
    while(1){
    char xf[100];
 
    char pol[100];
    char *word;
    printf("You can use program, while you don't press z\n");
    scanf ("%s",&xf);
    if  (strcmp(xf,"z")==0){
   return 0;
    }
    printf("Enter line: ");
    scanf ("%s",&pol);
    word = strtok(pol," ");
    while(word != NULL){
        int a=0;
        a=sort(word);
        if (a == 0) {
            while(1){
            char y[10],v[10]="",v2[10]="";
            int v1;
            int cv,b,m,cv2,nv;
            printf("%s\n",word);
            printf("\nChange word? ");
            scanf ("%s",&y);
            
            if (strcmp(y,"y")==0){
                printf("Choose vowel\n");
                 scanf ("%s",&v);
                cv =sort(v);
                
                if (cv==0){
                    b= how_much(word,v);
                    if (b ==0) printf("Incorrect input\n");

                    else if (b == 1){
                        
                        printf("Choose new vowel\n");
                        scanf ("%s",&v2);
                        cv2 = sort(v2);
                        if (cv2 == 0) {
                            //strcpy(v1,v);
                            for ( int i = 0; i< strlen(word);i++){
                                if ( word[i]== v[0]) {
                                    m = i;
                                    break;
                                }
                            }
                            word[m]= v2[0];
                        }
                        else printf("Incorrect input\n");

                    }
                    else if (b>1){
                        printf("Choose a vowel number\n");
                        scanf("%d",&nv);
                        if ( nv <= b){
                            int n=0,i;
                            for ( i = 0; i< strlen(word);i++){
                                if ( n== nv) {
                                    i--;
                                    break;
                                }
                                else if ( word[i]== v[0] && n!= nv) n++;
                            }
                            printf("Choose new vowel\n");
                            scanf ("%s",&v2);
                            cv2 = sort(v2);
                            if (cv2 == 0) {
                                word[i]= v2[0];
                            }
                            else printf("Incorrect input\n");
                        }
                        else printf("Incorrect input\n");
                    }

                }
                else printf("Incorrect input\n");

            }
            else break;
            }

        }
        
        word = strtok (NULL, " ");
        
    }

    }


}