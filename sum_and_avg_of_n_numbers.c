#include <stdio.h>

int main()
{
    int i;
    int n;

    printf("Podaj liczbe wartosci:");
    scanf("%d", &n);

    float sum = 0;
    for(i = 0; i < n; i++)
    {
        printf("Podaj wartosc %d:", i+1);
        float value;
        scanf("%f", &value);
        sum = sum + value;
    }
    printf("\nSuma = %f", sum);
    printf("\nSrednia = %f\n", sum/n);
    if(n <= 0 || n == 0 && n != 0)
    {
        printf("\nNieprawidlowa liczba wartosci\n");
        return 1;
    }

    getc(stdin);
    return 0;
}
