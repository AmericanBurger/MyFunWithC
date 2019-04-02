#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "windows.h"
#include <time.h>
#define SIZE 111 /* Jak dluga jest obramowka? */

void gotoxy(int x, int y) /* Ta funkcja ustawia kursor na pozycje (x,y)*/
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void pct2str(int pct, char *str) 
/* Ta funkcja zmienia int procentowy (0-100, zmienna pct) na napis (str)*/
{
	int jednosci, dziesiatki, setki; /* Zmienne pomocnicze */
	int kopia = pct; /* Kopia potrzebna pozniej */
	while (pct > 100) /* Na prawidlowy przedzial od 0 - 100 */
		pct -= 100;
	/* Wydobywamy cyfry */
	jednosci = pct % 10;
	pct /= 10;
	dziesiatki = pct % 10;
	pct /= 10;
	setki = pct % 10;
	/* Ustawiamy odpowiednio napis */
	str[0] = (kopia < 100) ? ' ' : setki + '0';
	str[1] = (kopia < 10) ?  ' ' : dziesiatki + '0';
	str[2] = jednosci + '0';
	str[3] = '%';
	str[4] = 0;
}

int main()
{
	/* Zmienne */
	int i; /* Licznik */
	char obr[SIZE], bar[SIZE]; /* Napisy: obramowka i sam pasek */
	char napis[5]; /* 3 cyfry + znak procentu + znak NULL */
	time_t start, stop; /* By ustalic czas */
	double timeElapsed; /* Ile czasu uplynelo? */
	double maxTime = 0.25; /* Max czas pomiedzy procentami*/
	memset(napis, ' ', sizeof(napis)); /* Wyczysc napis na procenty */
	napis[3] = '%'; napis[4] = 0; /* Zapisz tam znak procentu i koniec napisu */
	memset(obr, '#', sizeof(obr) - 1); /* Stworz obramowke... */
	memset(bar, ' ', sizeof(bar) - 1); /* i sam pasek */
	obr[SIZE - 1] = bar[SIZE - 1] = 0;
	bar[0] = bar[SIZE - 2] = '#';
	printf("Co ile czasu (w sek.) ma sie zwiekszac procent: ");
	scanf_s("%lf", &maxTime);
	gotoxy(0, 0);
	printf("%s\n", obr);
	printf("%s\n", bar);
	for (i = 0; i <= 100; ++i)
	{
		start = clock();
		timeElapsed = 0.0;
		while (timeElapsed < maxTime) /* Dopoki czas max nie jest osiagniety */
		{
			stop = clock(); /* Obliczaj go od nowa */
			timeElapsed = (double)(stop - start) / CLOCKS_PER_SEC;
		}
		gotoxy(2 + i, 1);
		printf("#");
		pct2str(i, napis);
		gotoxy(SIZE - 7, 1); /* Minus 7 jako wycofanie */
		printf("%s", napis);
		printf("\n%s\n", obr);
	}
	puts("KONIEC PROGRAMU - WCISNIJ ENTER BY ZAKONCZYC");
	_getch();
	_getch();
	return EXIT_SUCCESS;
}