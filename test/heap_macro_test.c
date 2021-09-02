#include "../heap_macro.h"
#include <stdio.h>

HEAP(int)

int comp(int l, int r) { return l < r; }

typedef struct pair
{
    int l;
    int r;
} pair;

int comp_pair(pair x, pair y)
{
    return (x.l <= y.l) && ((x.l < y.l) || (x.r < y.r));
}

HEAP(pair)

int main(void)
{
    heap_int *h = new_heap_int(20, comp);
    heap_insert_int(h, 10);
    heap_insert_int(h, 20);
    heap_insert_int(h, 5);
    heap_insert_int(h, 2);
    heap_insert_int(h, -1);
    heap_insert_int(h, 55);
    heap_insert_int(h, 10000);
    heap_insert_int(h, -152);

    while (!heap_empty_int(h))
        printf("%d\n", heap_pop_int(h));

    puts("");

    heap_pair *f = new_heap_pair(3, comp_pair);
    heap_insert_pair(f, (struct pair)
                        {
                            0,
                            1,
                        });
    heap_insert_pair(f, (pair)
                        {
                            1,
                            1,
                        });
    heap_insert_pair(f, (pair)
                        {
                            0,
                            0,
                        });
    heap_insert_pair(f, (pair) {-1, 0});
    while (!heap_empty_pair(f))
    {
        pair p = heap_pop_pair(f);
        printf("%d %d\n", p.l, p.r);
    }
    
    return 0; 
}