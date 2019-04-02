#include <stdio.h>
#include <stdlib.h>
#define len 100

void clrscr()
{
    system("@cls||clear");
}

int main()
{
	for(int percent = 0; percent < 100; ++percent)
	{
		for(int i = 0; i < len; ++i)
			printf("#");
		printf("\n");

		if(((len - len * percent / 100 + (percent < 10) - 4) / 100) > 0)
		{
			for(int i = 0; i < len * percent / 100; ++i)
				printf("#");

			printf(" %d%%", percent);
			printf("%*c", len - len * percent / 100 + (percent < 10) - 4, '#');
			printf("\n");
		}
		else
		{
			for(int i = 0; i < len * percent / 100 - 2 * (percent == 100) - 4; ++i)
				printf("#");

			printf(" %d%%", percent);
			printf("%*c", len - len * percent / 100, '#');
			printf("\n");
		}

		for(int i = 0; i < len; ++i)
			printf("#");
		printf("\n");

      	for (int c = 1; c <= 5976; c++)
       		for (int d = 1; d <= 5976; d++);
       	clrscr();
	}

	for(int percent = 100; percent <= 100; ++percent)
	{
		for(int i = 0; i < len; ++i)
			printf("#");
		printf("\n");

		if(((len - len * percent / 100 + (percent < 10) - 4)/10) > 0)
		{
			for(int i = 0; i < len * percent / 100; ++i)
				printf("#");

			printf(" %d%%", percent);
			printf("%*c", len - len * percent / 100 + (percent < 10) - 4, '#');
			printf("\n");
		}
		else
		{
			for(int i = 0; i < len * percent / 100 - 2 * (percent == 100) - 4; ++i)
				printf("#");

			printf(" %d%%", percent);
			printf("%*c", len - len * percent / 100, '#');
			printf("\tDone! ^^\n");
		}

		for(int i = 0; i < len; ++i)
			printf("#");
		printf("\n");
	}

	return 0;
}