#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "format_type.h"

struct statistic_t
{
    int min;
    int max;
    float avg;
    float standard_deviation;
    int range;
};

int statistics(int **ptr, struct statistic_t **stats)
{
    if (!ptr || !stats)
        return 1;

    *stats = (struct statistic_t*)malloc(sizeof(struct statistic_t));

    if (!(*stats))
        return 2;

    if (!(*ptr))
    {
        free(*stats);
        return 3;
    }

    int suma = 0, min = 0, max = 0, n = 0;
    float srednia = 0, temp = 0;

    min = (*(*(ptr)));  max = min;

    for (int i = 0; *(ptr + i) != NULL; ++i)
    {
        for (int j = 0; *(*(ptr + i) + j) != -1; ++j)
        {
            if (*(*(ptr + i) + j) < min)
                min = *(*(ptr + i) + j);

            if (*(*(ptr + i) + j) > max)
                max = *(*(ptr + i) + j);

            suma += *(*(ptr + i) + j);
            ++n;
        }
    }

    if (n < 1)
    {
        free(*stats);
        return 3;
    }

    srednia = (float)suma / n;

    for (int i = 0; *(ptr + i) != NULL; ++i)
        for (int j = 0; *(*(ptr + i) + j) != -1; ++j)
            temp += pow(*(*(ptr + i) + j) - srednia, 2) / n;

    (*stats)->standard_deviation = sqrt(temp);
    (*stats)->range = max - min;
    (*stats)->min = min;
    (*stats)->max = max;
    (*stats)->avg = srednia;

    return 0;
}

void display(int **ptr)
{
    if (ptr)
    {
        for (int i = 0; *(ptr + i) != NULL; ++i)
        {
            for (int j = 0; *(*(ptr + i) + j) != -1; ++j)
                printf("%d ", *(*(ptr + i) + j));
            printf("\n");
        }
    }
}

int save(const char *filename, int **ptr, enum save_format_t format)
{
    if (!filename || !ptr || !*ptr || (format != fmt_binary && format != fmt_text))
        return 1;

    FILE *fp;
    char *trans;
    int a = -1;

    trans = (char*)malloc(40 * sizeof(char));

    if (!trans)
        return 3;

    char *pZnak = strpbrk(filename, ".");

    if (!pZnak)
    {
        free(trans);
        return 2;
    }

    pZnak++;

    /*if (!strcmp("txt", pZnak) || !strcmp("bin", pZnak))
    strcpy(trans, filename);
    else
    {
    strcpy(trans, filename);

    int i = 0;  for (char temp = *(trans + i); temp == '.'; ++i);   ++i;    *(trans + i) = '\0';

    if (format == fmt_text)
    strcat(trans, "txt");
    else if (format == fmt_binary)
    strcat(trans, "bin");
    else
    {
    free(trans);
    return 1;
    }
    }*/

    strcpy(trans, filename);

    if (format == fmt_text)
    {
        fp = fopen(trans, "w");

        if (!fp)
        {
            free(trans);
            return 2;
        }

        for (int i = 0; *(ptr + i); ++i)
        {
            for (int j = 0; *(*(ptr + i) + j) != -1; ++j)
                fprintf(fp, "%d ", *(*(ptr + i) + j));

            fprintf(fp, "-1\n");
        }
    }
    else if (format == fmt_binary)
    {
        fp = fopen(trans, "wb");

        if (!fp)
        {
            free(trans);
            return 2;
        }

        for (int i = 0; *(ptr + i); ++i)
        {
            for (int j = 0; *(*(ptr + i) + j) != -1; ++j)
                fwrite(*(ptr + i) + j, sizeof(int), 1, fp);

            fwrite(&a, sizeof(int), 1, fp);
        }
    }
    else
    {
        free(trans);
        return 1;
    }

    free(trans);
    fclose(fp);

    return 0;
}

void destroy(int ***ptr) 
{
    if (ptr) 
    {
        for (int i = 0; *(*ptr + i); ++i) 
            free(*(*ptr + i));

        free(*ptr);
    }
}

int statistics_row(int **ptr, struct statistic_t **stats)
{
    if (!ptr || !stats)
        return -1;

    int suma = 0, n = 0, temp = 0, flaga = 0, min = 0, max = 0;
    float srednia = 0, stdev = 0;

    for (int i = 0; *(ptr + i); ++i)
        ++n;

    *stats = (struct statistic_t*)malloc(n * sizeof(struct statistic_t));

    if (!(*stats))
        return -2;

    temp = n;   n = 0;

    for (int i = 0; i < temp; ++i)
    {
        flaga = 0;  n = 0;  suma = 0;   stdev = 0;

        min = *(*(ptr + i));
        max = min;

        if (*(*(ptr + i)) == -1)
            flaga = 1;

        for (int j = 0; *(*(ptr + i) + j) != -1; ++j)
        {
            if (*(*(ptr + i) + j) < min)
                min = *(*(ptr + i) + j);

            if (*(*(ptr + i) + j) > max)
                max = *(*(ptr + i) + j);

            suma += *(*(ptr + i) + j);  ++n;
        }
        if (flaga)
        {
            ((*stats) + i)->standard_deviation = -1;
            ((*stats) + i)->range = -1;
            ((*stats) + i)->min = -1;
            ((*stats) + i)->max = -1;
            ((*stats) + i)->avg = -1;

            if (!(*stats))
                return -2;

            continue;
        }

        srednia = (float)suma / n;

        for (int j = 0; *(*(ptr + i) + j) != -1; ++j)
            stdev += pow((*(*(ptr + i) + j) - srednia), 2) / (float)n;

        ((*stats) + i)->standard_deviation = (float)sqrt(stdev);
        ((*stats) + i)->range = max - min;
        ((*stats) + i)->min = min;
        ((*stats) + i)->max = max;
        ((*stats) + i)->avg = srednia;
    }

    return temp;
}

int load(const char *filename, int ***ptr, enum save_format_t format)
{
    if (!filename || !ptr)
        return 1;

    if (format != fmt_text && format != fmt_binary)
        return 1;

    FILE* fp;
    int temp = 0, size = 0, n = 0, x = 0;

    if (format == fmt_text)
    {
        fp = fopen(filename, "r");

        if (!fp)
            return 2;

        fseek(fp, 0, SEEK_END);
        size = ftell(fp);

        if (!size) 
        {
            fclose(fp);
            return 3;
        }

        fseek(fp, 0, SEEK_SET);

        for (;!feof(fp);)
        {
            fscanf(fp, "%d", &temp);

            if (!temp)
            {
                fclose(fp);
                return 3;
            }

            if (!feof(fp) && temp == -1)
                ++n;
        }

        /*if (n < 1)
        {
            fclose(fp);
            return 3;
        }*/

        *ptr = (int**)malloc((n + 1) * sizeof(int*));

        if (!(*ptr))
        {
            fclose(fp);
            return 4;
        }

        *(*ptr + n) = NULL;

        fseek(fp, 0, SEEK_SET);

        for (int i = 0; i < n; ++i)
        {
            x = 0;

            for (;!feof(fp);)
            {
                fscanf(fp, "%d", &temp);

                if (!temp)
                {
                    free(*ptr);
                    fclose(fp);
                    return 3;
                }

                if (temp == -1)
                    break;

                ++x;
            }

            *(*ptr + i) = (int*)malloc((x + 1) * sizeof(int));

            if (!(*(*ptr + i)))
            {
                for (int j = 0; j < i; ++j)
                    free(*(*ptr + j));

                free(*ptr);
                fclose(fp);

                return 4;
            }
        }

        fseek(fp, 0, SEEK_SET);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; ; ++j)
            {
                if (!feof(fp) && fscanf(fp, "%d", *(*ptr + i) + j) < 1)
                {
                    for (int k = 0; k < n; ++k)
                        free(*(*ptr + k));

                    free(*ptr);
                    fclose(fp);

                    return 3;
                }
                if (!feof(fp) && *(*(*ptr + i) + j) == -1)
                    break;
            }
        }

        *(*ptr + n) = NULL;

        fclose(fp);
    }
    else if (format == fmt_binary)
    {
        /*char *pZnak = strpbrk(filename, ".");

        if (!pZnak)
            return 2;

        pZnak++;

        if (strcmp(pZnak, "bin"))
            return 3;*/

        fp = fopen(filename, "rb");

        if (!fp)
            return 2;

        fseek(fp, 0, SEEK_END);

        size = ftell(fp);

        if (!size)
        {
            fclose(fp);
            return 3;
        }

        fseek(fp, 0, SEEK_SET);

        for (;!feof(fp);)
        {
            fread(&temp, sizeof(int), 1, fp);

            if (!feof(fp) && temp == -1)
                ++n;
        }

        *ptr = (int**)malloc((n + 1) * sizeof(int*));

        if (!(*ptr))
        {
            fclose(fp);
            return 4;
        }

        *(*ptr + n) = NULL;

        fseek(fp, 0, SEEK_SET);

        for (int i = 0; i < n; ++i)
        {
            x = 0;

            for (;!feof(fp);)
            {
                if (!feof(fp))
                {
                    if (!fread(&temp, sizeof(int), 1, fp))
                    {
                        fclose(fp);
                        free(*ptr);
                        return 3;
                    }
                }
                else
                    break;

                if (!feof(fp) && temp == -1)
                    break;

                ++x;
            }

            *(*ptr + i) = (int*)malloc((x + 1) * sizeof(int));

            if (!(*(*ptr + i)))
            {
                for (int j = 0; j < i; ++j)
                    free(*(*ptr + j));

                free(*ptr);
                fclose(fp);

                return 4;
            }
        }

        fseek(fp, 0, SEEK_SET);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; ; ++j)
            {
                if (!feof(fp))
                {
                    if (!fread(&temp, sizeof(int), 1, fp))
                    {
                        for (int k = 0; k < n; ++k)
                            free(*(*ptr + k));

                        free(*ptr);
                        fclose(fp);

                        return 3;
                    }
                }
                *(*(*ptr + i) + j) = temp;

                if (*(*(*ptr + i) + j) == -1 && !feof(fp))
                    break;
            }
        }
        fclose(fp);
    }

    return 0;
}

int main()
{
    char* wae;
    struct statistic_t *staty;
    int res = 0, ult = 0, **D;

    wae = (char*)malloc(40 * sizeof(char));

    if (!wae)
    {
        printf("Failed to allocate memory\n");
        return 4;
    }

    printf("Podaj nazwe pliku: ");
    scanf("%39s", wae);

    char *pZnak = strpbrk(wae, ".");

    if (!pZnak)
    {
        printf("Wrong filename\n");
        free(wae);
        return 1;
    }

    pZnak++;

    if (strcmp(pZnak, "txt") && strcmp(pZnak, "bin"))
    {
        printf("Wrong filename\n");
        free(wae);
        return 1;
    }

    if (!strcmp(pZnak, "txt"))
    {
        res = load(wae, &D, fmt_text);

        if (res == 1)
        {
            printf("Incorrect input\n");
            free(wae);
            return 1;
        }
        else if (res == 2)
        {
            printf("Couldn't open file\n");
            free(wae);
            return 2;
        }
        else if (res == 3)
        {
            printf("File corrupted\n");
            free(wae);
            return 3;
        }
        else if (res == 4)
        {
            printf("Failed to allocate memory\n");
            free(wae);
            return 4;
        }
        //display(D);

        ult = statistics_row(D, &staty);

        if (ult == -1)
        {
            printf("Error\n");
            free(wae);
            destroy(&D);
            return 1;
        }
        else if (ult == -2)
        {
            printf("Failed to allocate memory\n");
            free(wae);
            destroy(&D);
            return 4;
        }

        for (int i = 0; i < ult; ++i)
        {
            printf("%d %d ", (staty + i)->min, (staty + i)->max);
            printf("%d %f ", (staty + i)->range, (staty + i)->avg);
            printf("%f ", (staty + i)->standard_deviation);
            printf("\n");
        }
        free(staty);
    }
    else if (!strcmp(pZnak, "bin"))
    {
        res = load(wae, &D, fmt_binary);

        if (res == 1)
        {
            printf("Incorrect input\n");
            free(wae);
            return 1;
        }
        else if (res == 2)
        {
            printf("Couldn't open file\n");
            free(wae);
            return 2;
        }
        else if (res == 3)
        {
            printf("File corrupted\n");
            free(wae);
            return 3;
        }
        else if (res == 4)
        {
            printf("Failed to allocate memory\n");
            free(wae);
            return 4;
        }
        //display(D);

        ult = statistics_row(D, &staty);

        if (ult == -1)
        {
            printf("Error\n");
            free(wae);
            destroy(&D);
            return 1;
        }
        else if (ult == -2)
        {
            printf("Failed to allocate memory\n");
            free(wae);
            destroy(&D);
            return 4;
        }

        for (int i = 0; i < ult; ++i)
        {
            printf("%d %d ", (staty + i)->min, (staty + i)->max);
            printf("%d %f ", (staty + i)->range, (staty + i)->avg);
            printf("%f ", (staty + i)->standard_deviation);
            printf("\n");
        }
        free(staty);
    }

    free(wae);
    destroy(&D);

    return 0;
}