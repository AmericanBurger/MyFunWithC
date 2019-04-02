#include <stdio.h>
#include <stdlib.h>
#define m 200
#define n 1012 * m

int main()
{
    FILE *fp;
    char wae[] = "day1.txt";    int temp = 0, suma = 0, tab[n] = { 0 }, yes = 1;

    fp = fopen(wae, "r");
    for(int i = 0; i < n; ++i)
    {
    	if(feof(fp))	fseek(fp, 0, SEEK_SET);
        fscanf(fp, "%d", &temp); 
        suma += temp;
        tab[i] = suma;
        //printf("tab[%d] = %d\n", i, suma);
    }
    for(int i = 0; i < n; ++i)
    {
    	for(int j = i + 1; j < n; ++j)
    	{
    		if(tab[i] == tab[j])
    		{
    			printf("Znaleziony duplikat: %d\n", tab[i]);
   				yes = 0;
   				break;
    		}
    	}
    	if(!yes) break;
    }
	if(yes)	printf("Nie ma duplikatow!\n");

    fclose(fp);
    //printf("Suma liczb z pliku: %d\n", suma);
    return 0;
}

