#include <stdio.h>
#define rows 3
#define columns 3

int main() 
{
  int tab[rows][columns] = { 0 };
  int wiersz = 0, kolumna = 0, wartosc = 1;
  char znaki[] = {' ', 'O', 'X'};

  for(int i = 0; i < rows * columns; ++i, wartosc = !wartosc + (i % 2) + 1)
  {
    printf("|||TURA GRACZA %c|||\n", znaki[(i % 2) + 1]);
    printf("Podaj wiersz i kolumne: ");
    scanf("%d %d", &wiersz, &kolumna);
    
    if(tab[wiersz - 1][kolumna - 1] == 0)
      tab[wiersz - 1][kolumna - 1] = wartosc;
    else{printf("NIE MOZESZ NADPISAC!\n\n"); --i; continue;}

    for(int i = 0; i < rows; ++i)
    {
      for(int j = 0;  j < columns; ++j)
        printf("%c ", znaki[tab[i][j]]);
      printf("\n");
    }
    printf("\n");

    int temp[8] = {0};
    for(int i = 0; i < rows; ++i)
    {
      temp[0] += znaki[tab[i][0]];
      temp[1] += znaki[tab[i][1]];
      temp[2] += znaki[tab[i][2]];
      temp[3] += znaki[tab[0][i]];
      temp[4] += znaki[tab[1][i]];
      temp[5] += znaki[tab[2][i]];
      temp[6] += znaki[tab[i][i]];
      temp[7] += znaki[tab[i][2 - i]];
    }
    for(int i = 0; i < 8; ++i)
    {
      if(temp[i] == 3 * 'X' || temp[i] == 3 * 'O')
      {
        printf("|||WYGRAL GRACZ %c", znaki[(i % 2) + 1]);
        return 0;
      }
    }
  }
  printf("|||REMIS!|||\n");
  
  return 0;
}