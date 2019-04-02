#include <stdio.h>
#include <stdlib.h>

struct circular_buffer_t 
{
    int *ptr;
    int begin;
    int end;
    int capacity;
    unsigned char full : 1;
};

int create(struct circular_buffer_t *cb, int N)
{
    if (!cb || N < 1)
        return 1;

    cb->ptr = (int*)malloc(N * sizeof(int));

    if (!cb->ptr)
        return 2;

    cb->begin = 0;
    cb->end = 0;
    cb->capacity = N;
    cb->full = 0;

    return 0;
}

int create_circular_buffer(struct circular_buffer_t **cb, int N)
{
    if (!cb || N < 1)
        return 1;

    *cb = (struct circular_buffer_t*)malloc(sizeof(struct circular_buffer_t));

    if (!(*cb))
        return 2;

    (*cb)->ptr = (int*)malloc(N * sizeof(int));

    if (!(*cb)->ptr) 
    {
        free(*cb);
        return 2;
    }

    (*cb)->begin = 0;
    (*cb)->end = 0;
    (*cb)->capacity = N;
    (*cb)->full = 0;

    return 0;
}

void destroy(struct circular_buffer_t *cb)
{
    if (cb && cb->ptr && cb->capacity > 0)
    {
        free(cb->ptr);  cb->capacity = 0;
    }
}

void destroy_circular_buffer(struct circular_buffer_t **cb)
{
    if (cb)
    {
        destroy(*cb); free(*cb);
    }
}

int empty(const struct circular_buffer_t *cb)
{
    if (!cb || cb->capacity < 0)
        return -1;

    return (cb->begin == cb->end && !cb->full);
}

int full(const struct circular_buffer_t *cb)
{
    if (!cb || cb->capacity < 0)
        return -1;

    return cb->full;
}

int push_back(struct circular_buffer_t *cb, int value)
{
    //printf("begin1 = %d\nend1 = %d\nfull1 = %d\n", cb->begin, cb->end, cb->full);

    if (!cb || !cb->ptr || cb->begin < 0 || cb->end < 0 || cb->begin >= cb->capacity || cb->end >= cb->capacity)
        return 1;

    if (cb->end >= cb->capacity)
        cb->end = 0;

    if (cb->full)
    {
        *(cb->ptr + cb->begin) = value; cb->begin++;

        if (cb->begin >= cb->capacity)
            cb->begin = 0;
    }
    else
        *(cb->ptr + cb->end) = value;   
    
    cb->end++;

    if (cb->end >= cb->capacity) 
        cb->end = 0;

    if (cb->begin == cb->end)
        cb->full = 1;

    //printf("begin2 = %d\nend2 = %d\nfull2 = %d\n", cb->begin, cb->end, cb->full);

    return 0;
}

int pop_front(struct circular_buffer_t *cb, int *err_code)
{
    //printf("begin1 = %d\nend1 = %d\nfull1 = %d\n", cb->begin, cb->end, cb->full);

    if (!cb || !cb->ptr || cb->begin < 0 || cb->end < 0 || cb->begin >= cb->capacity || cb->end >= cb->capacity)
    {
        if (err_code)
            *err_code = 1;

        return 1;
    }

    if (empty(cb))
    {
        if (err_code)
            *err_code = 2;

        return 2;
    }

    int next = *(cb->ptr + cb->begin);  cb->begin++;

    if (cb->begin >= cb->capacity)
        cb->begin = 0;

    if (err_code)
        *err_code = 0;

    cb->full = 0;

    //printf("begin2 = %d\nend2 = %d\nfull2 = %d\n", cb->begin, cb->end, cb->full);

    return next;
}

int pop_back(struct circular_buffer_t *cb, int *err_code)
{
    //printf("begin1 = %d\nend1 = %d\nfull1 = %d\n", cb->begin, cb->end, cb->full);1

    if (!cb || !cb->ptr || cb->begin < 0 || cb->end < 0 || cb->begin >= cb->capacity || cb->end >= cb->capacity)
    {
        if (err_code)
            *err_code = 1;

        return 1;
    }

    if (empty(cb))
    {
        if (err_code)
            *err_code = 2;

        return 2;
    }

    int next = 0;

    if (cb->end <= 0)
        next = *(cb->ptr + cb->capacity - 1);
    else 
        next = *(cb->ptr + cb->end - 1);

    cb->end--;

    if (cb->end < 0) 
        cb->end = cb->capacity - 1; 

    if (err_code)
        *err_code = 0;

    cb->full = 0;

    //printf("begin2 = %d\nend2 = %d\nfull2 = %d\n", cb->begin, cb->end, cb->full);

    return next;
}

void display(const struct circular_buffer_t *cb)
{
    if (cb && cb->ptr && !empty(cb) && cb->capacity > 0 && cb->begin >= 0 && cb->end >= 0 && cb->begin < cb->capacity && cb->end < cb->capacity)
    {
        printf("%d ", *(cb->ptr + cb->begin));

        for (int i = (cb->begin + 1) % cb->capacity; i != cb->end; i = (i + 1) % cb->capacity)
            printf("%d ", *(cb->ptr + i));

        printf("\n");
    }
}

int main()
{
    struct circular_buffer_t *zmienna;
    int n = 0, temp = 0, op = 0, value = 0, error = 0;

    printf("Podaj rozmiar buforu: ");
    scanf("%d", &n);

    if (n < 1)
    {
        printf("Error\n");
        return 1;
    }

    temp = create_circular_buffer(&zmienna, n);

    if (temp == 1)
    {
        printf("Error\n");
        return 1;
    }
    else if(temp == 2)
    {
        printf("Failed to allocate memory\n");
        return 2;
    }
    else
        while (1)
        {
            printf("Jaka operacje chcesz wykonac?: ");
            scanf("%d", &op);

            switch (op)
            {
            case 0:
            {
                destroy_circular_buffer(&zmienna);  //destroy(zmienna);
                return 0;
            }
            case 1:
            {
                printf("Podaj wartosc jaka chcesz dodac do tablicy: ");
                scanf("%d", &value);
                push_back(zmienna, value);
                continue;
            }
            case 2:
            {
                if (empty(zmienna))
                {
                    printf("Buffer is empty\n");
                    continue;
                }
                else
                {
                    printf("%d\n", pop_back(zmienna, &error));
                    continue;
                }
            }
            case 3:
            {
                if (empty(zmienna))
                {
                    printf("Buffer is empty\n");
                    continue;
                }
                else
                {
                    printf("%d\n", pop_front(zmienna, &error));
                    continue;
                }
            }
            case 4:
            {
                if (empty(zmienna))
                {
                    printf("Buffer is empty\n");
                    continue;
                }
                else
                {
                    display(zmienna);
                    continue;
                }
            }
            case 5:
            {
                printf("%d\n", empty(zmienna));
                continue;
            }
            case 6:
            {
                printf("%d\n", full(zmienna));
                continue;
            }
            default:
            {
                printf("Incorrect input\n");
                continue;
            }
            }
        }

    destroy(zmienna);   destroy_circular_buffer(&zmienna);

    return 0;
}

