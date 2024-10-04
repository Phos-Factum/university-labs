#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *S1, *S2;
  int x, y;
  system("cls");

  printf("Enter count: ");
  scanf("%d", &x);

  S1 = fopen("S1.txt", "w");
  fprintf(S1, "%d", x);
  fclose(S1);

  S1 = fopen("S1.txt", "r");
  S2 = fopen("S2.txt", "w");
  fscanf(S1, "%d", &y);
  y += 3;
  fclose(S1);
  fprintf(S2, "%d\n", y);
  fclose(S2);

  return 0;
}