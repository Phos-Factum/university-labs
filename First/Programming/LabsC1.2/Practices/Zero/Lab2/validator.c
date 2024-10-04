#include <stdio.h>
#include <string.h>

int main() 
{ 
	char str[] = "Hello, World!";
	char ch = '\0';
	
	int found = 0;
	int i;

	for (i = 0; i < strlen(str); i++) 
	{
		if (str[i] == ch) 
		{
			found = 1;
			break;
		}
	}
	if (found) 	
	{
		printf("Symbol %c was found in string.", ch);
	} 
	else 
	{
		printf("Symbol %c was not found in string.", ch);
	}

	return 0;
}
