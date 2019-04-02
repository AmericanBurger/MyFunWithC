#include <stdio.h>

int main()
{
    while(1)
    {
        float a, b;
        printf("Podaj wartosc a:");
        scanf("%f", &a);
        printf("Podaj wartosc b:");
        scanf("%f", &b);

        printf("\nMENU\n");

        int choice;

        printf("\n1. Dodawanie");
        printf("\n2. Odejmowanie");
        printf("\n3. Mnozenie");
        printf("\n4. Dzielenie");
        printf("\n5. Podaj ponownie wartosci");
        printf("\n6. Zakoncz\n");

        printf("\nWybierz opcje:");
        scanf("%d", &choice);

        float suma = a + b;
        float roznica = a - b;
        float iloczyn = a*b;
        float iloraz = a/b;

        switch(choice)
        {
        case 1:
            printf("\nSuma wynosi: %f\n\n", suma);
            break;
        case 2:
            printf("\nRoznica wynosi: %f\n\n", roznica);
            break;
        case 3:
            printf("\nIloczyn wynosi: %f\n\n", iloczyn);
            break;
        case 4:
            if(b==0)
                printf("\nNie mozna dzielic przez zero\n\n");
            else
                printf("\nIloraz wynosi: %f\n\n", iloraz);
            break;
        case 5:
            break;
        case 6:
            return 0;
            break;
        default:
            printf("\nBledna wartosc\n\n");
        }
    }
}
