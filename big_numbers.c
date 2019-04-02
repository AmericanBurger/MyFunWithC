#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int subtract(const char* number1, const char* number2, char** result);

int validate(const char * number)
{
    if (number == NULL)
        return 2;

    if ((int)strlen(number) <= 0 || *number == '-' && (int)strlen(number) == 1 || *number == '+' || *number == '-' && *(number + 1) == '0' || *number == '0' && (int)strlen(number) > 1)
        return 1;

    for (int i = 0; *(number + i) != '\0'; ++i)
    {
        if (*(number + i) < 45 || *(number + i) > 45 && *(number + i) < 48 || *(number + i) > 57)
            return 1;
    }

    return 0;
}

int compare(const char* number1, const char* number2)
{
    if (!number1 || !number2)
        return 2;

    if (validate(number1) || validate(number2))
        return 3;

    /*if (strlen(number1) > strlen(number2))
    return 1;

    if (strlen(number1) < strlen(number2))
    return -1;*/

    int flag = 0;

    if (*number1 == '-' && *number2 == '-')
        flag = 1;
    else if (*number1 == '-' && *number2 != '-')
        return -1;
    else if (*number1 != '-' && *number2 == '-')
        return 1;

    //printf("DUPA1\n");

    if (((int)strlen(number1) > (int)strlen(number2)) || (*number2 == '-' && *number1 != '-'))
        return 1;

    if (((int)strlen(number2) > (int)strlen(number1)) || (*number1 == '-' && *number2 != '-'))
        return -1;

    //printf("DUPA2\n");

    if ((int)strlen(number1) == (int)strlen(number2))
    {
        int i = 0;

        if (flag)
            i = 1;

        for (; *(number1 + i) != '\0'; ++i)
        {
            if (*(number1 + i) > *(number2 + i))
            {
                if (flag == 1)
                    return -1;
                else
                    return 1;

                //printf("DUPA3\n");
            }

            if (*(number1 + i) < *(number2 + i))
            {
                if (flag == 1)
                    return 1;
                else
                    return -1;

                //printf("DUPA4\n");
            }
        }

        return 0;
    }

    //int len = max(strlen(number1), strlen(number2));

    /*for(int i = 0; *(number1 + i) != *(number2 + i) && i < len; ++i)
    {
    if (*(number1 + i) > *(number2 + i))
    return 1;

    if (*(number1 + i) < *(number2 + i))
    return -1;
    }*/

    return 0;
}

int get(const char* text, int pos)
{
    if (pos >= (int)strlen(text))
        return '0';

    return *(text + pos);
}

int add(const char* number1, const char* number2, char** result)
{
    if (!number1 || !number2 || !result)
        return 1;

    if (validate(number1) || validate(number2))
        return 2;

    int size = 0, flag1 = 0, flag2 = 0;

    if (strlen(number2) > strlen(number1))
        size = strlen(number2) + 2;
    else
        size = strlen(number1) + 2;

    if (*(number1) == '-')
        ++flag1;

    if (*(number2) == '-')
        ++flag2;

    if (*(number1) == '-' || *(number2) == '+')
        ++number1;

    if (*(number2) == '-' || *(number2) == '+')
        ++number2;

    const char *tab1 = number1, *tab2 = number2;
    const char *liczba1 = (tab1 + strlen(tab1) - 1), *liczba2 = (tab2 + strlen(tab2) - 1);

    if ((flag1 && flag2) || (!flag1 && !flag2))
    {
        char *tab;
        tab = (char*)malloc(size * sizeof(char));

        if (!tab)
            return 3;

        int i = 0;

        for (; (i + 1) < size; ++i)
            *(tab + i) = '0';

        *(tab + i) = '\0';

        for (i = 0; (liczba1 - i) >= tab1; ++i)
            *(tab + i) = *(liczba1 - i);

        for (i = 0; (liczba2 - i) >= tab2; ++i)
            *(tab + i) += (*(liczba2 - i) - '0');

        for (i = 0; i < size; ++i)
        {
            char temp = *(tab + i);

            if (i + 1 < size && temp > '9')
            {
                *(tab + i) -= 10;
                *(tab + i + 1) += 1;
            }
        }

        for (i -= 2; i >= 0; --i)
        {
            if (*(tab + i) == '0')
                *(tab + i) = '\0';
            else
                break;
        }

        if (!strlen(tab))
        {
            free(tab);

            *(tab + 0) = '0';
            *result = tab;

            free(result);

            return 0;
        }

        if (flag1 && flag2 && (i + 1) < size)
            *(tab + i + 1) = '-';

        int len = (int)strlen(tab);

        for (int i = 0; i < len / 2; ++i)
        {
            char temp = *(tab + i);
            *(tab + i) = *(tab + len - 1 - i);
            *(tab + len - 1 - i) = temp;
        }

        *result = tab;

        return 0;
    }

    if (flag1)
    {
        int res = subtract(tab2, tab1, result);

        if (res == 3)
        {
            free(result);
            return 3;
        }
    }
    else
    {
        int res = subtract(tab1, tab2, result);

        if (res == 3)
        {
            free(result);
            return 3;
        }
    }

    return 0;
}

int subtract(const char* number1, const char* number2, char** result)
{
    if (!number1 || !number2 || !result)
        return 1;

    if (validate(number1) || validate(number2))
        return 2;

    int size = 0, flag1 = 0, flag2 = 0;

    if (strlen(number2) > strlen(number1))
        size = strlen(number2) + 2;
    else
        size = strlen(number1) + 2;

    if (*(number1) == '-')
        ++flag1;

    if (*(number2) == '-')
        ++flag2;

    if (flag1 && !flag2)
    {
        if (*(number2) == '-' || *(number2) == '+')
            ++number2;

        char *liczba = (char*)malloc(sizeof(char) * (strlen(number2) + 2));

        if (!liczba)
            return 3;

        strcpy(liczba, "-");

        if (strcmp(number2, "0"))
            strcat(liczba, number2);
        else
            *liczba = '0';

        int res = add(liczba, number1, result);

        if (res)
        {
            free(liczba);
            free(result);
            return 3;
        }
        free(liczba);

        return 0;
    }

    if (!flag1 && flag2)
    {
        if (*(number2) == '-' || *(number2) == '+')
            ++number2;

        char* liczba = (char*)malloc(sizeof(char)*(strlen(number2) + 2));

        if (!liczba)
        {
            free(result);
            return 3;
        }

        strcpy(liczba, number2);

        int res = add(liczba, number1, result);

        if (res)
        {
            free(liczba);
            free(result);
            return 3;
        }
        free(liczba);

        return 0;
    }

    if (*(number1) == '-' || *(number2) == '+')
        ++number1;

    if (*(number2) == '-' || *(number2) == '+')
        ++number2;

    const char *tab1, *tab2;

    if (strlen(number1) > strlen(number2))
        tab1 = number1;
    else
    {
        if (strlen(number1) < strlen(number2))
            tab1 = number2;
        else
        {
            if (strcmp(number1, number2) > 0)
                tab1 = number1;
            else
                tab1 = number2;
        }
    }

    if (strlen(number1) > strlen(number2))
        tab2 = number2;
    else
    {
        if (strlen(number1) < strlen(number2))
            tab2 = number1;
        else
        {
            if (strcmp(number1, number2) > 0)
                tab2 = number2;
            else
                tab2 = number1;
        }
    }

    const char *liczba1 = (tab1 + strlen(tab1) - 1), *liczba2 = (tab2 + strlen(tab2) - 1);
    char *tab = (char*)malloc(sizeof(char) * size);
    int i = 0;

    if (!tab)
    {
        //free(result);
        return 3;
    }

    for (; (i + 1) < size; ++i)
        *(tab + i) = '0';

    *(tab + i) = '\0';

    for (i = 0; (liczba1 - i) >= tab1; ++i)
        *(tab + i) = *(liczba1 - i);

    for (i = 0; (liczba2 - i) >= tab2; ++i)
        *(tab + i) -= (*(liczba2 - i) - '0');

    for (i = 0; i < size - 2; ++i)
    {
        char temp = *(tab + i);

        if (i + 1 < size && temp < '0')
        {
            *(tab + i) += 10;
            *(tab + i + 1) -= 1;
        }
    }

    for (i = size - 2; i >= 0; --i)
    {
        if (*(tab + i) == '0')
            *(tab + i) = '\0';
        else
            break;
    }

    if (!strlen(tab))
    {
        *(tab + 0) = '0';
        *result = tab;

        //free(result);
        return 0;
    }

    if (((strlen(number1) > strlen(number2) ? 1 : (strlen(number1) < strlen(number2) ? 0 : (strcmp(number1, number2) > 0 ? 1 : 0))) && flag1) || (((strlen(number1) > strlen(number2) ? 0 : (strlen(number1) < strlen(number2) ? 1 : (strcmp(number1, number2) > 0 ? 0 : 1))) && !flag2)))
        *(tab + i + 1) = '-';

    int len = (int)strlen(tab);

    for (int i = 0; i < len / 2; ++i)
    {
        char temp = *(tab + i);
        *(tab + i) = *(tab + len - 1 - i);
        *(tab + len - 1 - i) = temp;
    }

    *result = tab;

    return 0;
}

int main()
{
    char *tab1, *tab2, *wynik, temp;
    int size = 0;

    tab1 = (char*)malloc(201 * sizeof(char));

    if (!tab1)
    {
        printf("Failed to allocate memory\n");
        return 2;
    }

    tab2 = (char*)malloc(201 * sizeof(char));

    if (!tab2)
    {
        printf("Failed to allocate memory\n");
        free(tab1);
        return 2;
    }

    printf("Podaj pierwsza liczbe: ");

    for (;;)
    {
        scanf("%c", &temp);

        if (temp == '\n' || temp == '\0')
        {
            *(tab1 + size) = '\0';
            break;
        }
        if (size < 200)
        {
            *(tab1 + size) = temp;
            ++size;
        }
    }

    printf("Podaj druga liczbe: ");

    for (size = 0;;)
    {
        scanf("%c", &temp);

        if (temp == '\n' || temp == '\0')
        {
            *(tab2 + size) = '\0';
            break;
        }
        if (size < 200)
        {
            *(tab2 + size) = temp;
            ++size;
        }
    }

    int res = add(tab1, tab2, &wynik);

    if (res == 2)
    {
        printf("error");
        free(tab1);
        free(tab2);
        return 1;
    }
    if (res == 3)
    {
        printf("Failed to allocate memory\n");
        free(tab1);
        free(tab2);
        free(wynik);
        return 2;
    }

    printf("%s\n", wynik);

    free(tab1); free(tab2); free(wynik);
    return 0;
}

