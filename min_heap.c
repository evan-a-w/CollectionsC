#include <stdlib.h>
#include <stdio.h>

#define LEFT(x) (x << 1)
#define RIGHT(x) (x << 1) + 1
#define PARENT(x) x / 2

typedef struct heap
{
    int *arr; // 1 indexed (with size in index 0)
    int i;
} heap;

heap *new_heap(int n)
{
    heap *res = malloc(sizeof(heap));
    res->arr = malloc(sizeof(int) * (n + 1));
    res->arr[0] = n;
    res->i = 1;
    return res;
}

void free_heap(heap *h)
{
    free(h->arr);
    free(h);
}

int heap_empty(heap *h)
{
    return h->i == 1;
}

void heap_insert(heap *h, int x)
{
    if (h->i == h->arr[0])
    {
        h->arr[0] *= 2;
        h->arr = realloc(h->arr, (h->arr[0] + 1) * sizeof(int));
    }
    h->arr[h->i] = x;
    for (int i = h->i; i > 1; i = PARENT(i))
    {
        if (h->arr[i] < h->arr[PARENT(i)])
        {
            int t = h->arr[PARENT(i)];
            h->arr[PARENT(i)] = h->arr[i];
            h->arr[i] = t;
        }
        else
            break;
    }
    h->i++;
}

int heap_top(heap *h)
{
    return h->arr[1]; 
}

int heap_pop(heap *h)
{
    int res = h->arr[1];
    if (heap_empty(h)) return res; // clearly UB
    h->arr[1] = h->arr[--h->i]; // root = last element
    for (int i = 1; i < h->i;) // downheap
    {
        int r1 = (LEFT(i) <= h->i) ? LEFT(i) : -1, r2 = (RIGHT(i) <= h->i) ? RIGHT(i) : -1;
        int r = (h->arr[r1] < h->arr[r2]) ? r1 : r2;
        if (r != -1 && h->arr[r] < h->arr[i])
        {
            int t = h->arr[r];
            h->arr[r] = h->arr[i];
            h->arr[i] = t;
            i = r;
        }
        else
            break;
    }

    return res;
}

int main(void)
{
    heap *h = new_heap(20);
    heap_insert(h, 10);
    heap_insert(h, 20);
    heap_insert(h, 5);
    heap_insert(h, 2);
    heap_insert(h, -1);
    heap_insert(h, 55);
    heap_insert(h, 10000);
    heap_insert(h, -152);

    while (!heap_empty(h))
        printf("%d\n", heap_pop(h));
    
    return 0;
}