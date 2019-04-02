#include <stdio.h>

void loading_bar(int len, int percent)
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
		printf("\n");
	}

	for(int i = 0; i < len; ++i)
		printf("#");
	printf("\n");
}

int main()
{
	int len = 0, percent = 0;

	printf("Podaj dlugosc: ");
	scanf("%d", &len);
	printf("Podaj ile procent: ");
	scanf("%d", &percent);

	loading_bar(len, percent);

	return 0;
}