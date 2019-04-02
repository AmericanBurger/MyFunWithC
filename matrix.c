#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

struct matrix_t 
{
    int **ptr;
    int width;
    int height;
};

int create(struct matrix_t *m, int width, int height)
{
    if (!m || width < 1 || height < 1)  return 1;

    m->ptr = (int**)malloc(height * sizeof(int*));
    if (!m->ptr)    return 2;

    for (int i = 0; i < height; i++)
    {
        *(m->ptr + i) = (int*)malloc(width * sizeof(int));

        if (!(*(m->ptr + i)))
        {
            for (int j = 0; j < i; ++j) free(*(m->ptr + j));
            free(m->ptr);
            return 2;
        }
    }
    m->width = width;
    m->height = height;
    return 0;
}
void destroy(struct matrix_t *m)
{
    if (m && m->ptr && m->height > 0 && m->width > 0)
    {
        for (int j = 0; j < m->height; ++j) free(*(m->ptr + j));
        free(m->ptr);
    }
}
void display(const struct matrix_t *m)
{
    if (m && m->ptr && m->width > 0 && m->height > 0)
        for (int i = 0; i < m->height; ++i)
        {
            for (int j = 0; j < m->width; ++j)  printf("%d ", *(*(m->ptr + i) + j));
            printf("\n");
        }
}
int read(struct matrix_t *m)
{
    if (!m || !m->ptr || m->width < 1 || m->height < 1) return 1;

    printf("Podaj liczby:\n");

    for (int i = 0; i < m->height; ++i)
        for (int j = 0; j < m->width; ++j)  
            scanf("%d", (*(m->ptr + i) + j));

    return 0;
}

int main()
{
    struct matrix_t macierz;
    int szer = 0, wys = 0;

    printf("Podaj szerokosc i wysokosc tablicy: ");
    scanf("%d %d", &szer, &wys);

    if (create(&macierz, szer, wys))
    {
        printf("Failed to allocate memory\n");
        return 1;
    }
    else
    {
        read(&macierz);
        display(&macierz);
    }

    destroy(&macierz);
    return 0;
}

