#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include <ctype.h>

int main()
{
	char again;

	while (1)
	{

		int a = 0;
		char text[30];
		printf("Enter count 'a': ");
		scanf("%d", &a);
		printf("Enter text: ");
		scanf("%s", text);
		// if ()
		printf("\nYour count is: %d;", a);
		printf("\nYour text is: %d - %s.", text, text);
		if (isdigit(a))
		{
			printf("Nice! 'a' is int");
		}

		// char s[30];

		// bool valid = 0;
		// fgets(s, sizeof(s), stdin);
		// int len = strlen(s);
		// while (len > 0 && isspace(s[len - 1]))
		//     len--;     // strip trailing newline or other white space
		// if (len > 0)
		// {
		//     valid = 1;
		//     for (int i = 0; i < len; ++i)
		//     {
		//         if (!isdigit(s[i]))
		//         {
		//             valid = 0;
		//             break;
		//         }
		//     }
		// }


		printf("\nRepeat program? ('y'/'Y' --- yes / other --- no)\nAnswer: ");
	    scanf(" %c", &again);
	    if ( (again != 'y') && (again != 'Y') )
	    {
	        break;
	    } 

    }
	return 0;
}