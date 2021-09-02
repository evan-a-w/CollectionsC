#ifndef HEAP_MACRO_H
#define HEAP_MACRO_H

#ifndef NULL
#include <stdlib.h>
#endif

#define LEFT(x) (x << 1) + 1
#define RIGHT(x) (x << 1) + 2
#define PARENT(x) (x - 1) / 2

#define HEAP(T)\
typedef struct heap_##T\
{\
    T *arr;\
    int i;\
    int size;\
    int (*comp)(T, T);\
} heap_##T;\
heap_##T *new_heap_##T(int n, int (*comp)(T, T))\
{\
    heap_##T *res = malloc(sizeof(heap_##T));\
    res->arr = malloc(sizeof(T) * n);\
    res->size = n;\
    res->i = 0;\
    res->comp = comp;\
    return res;\
}\
void free_heap_##T(heap_##T *h)\
{\
    free(h->arr);\
    free(h);\
}\
int heap_empty_##T(heap_##T *h)\
{\
    return h->i == 0;\
}\
void heap_insert_##T(heap_##T *h, T x)\
{\
    if (h->i == h->size)\
    {\
        h->size *= 2;\
        h->arr = realloc(h->arr, h->size * sizeof(T));\
    }\
    h->arr[h->i] = x;\
    for (int i = h->i; i > 0; i = PARENT(i))\
    {\
        if (h->comp(h->arr[i], h->arr[PARENT(i)]))\
        {\
            T t = h->arr[PARENT(i)];\
            h->arr[PARENT(i)] = h->arr[i];\
            h->arr[i] = t;\
        }\
        else\
            break;\
    }\
    h->i++;\
}\
T heap_top_##T(heap_##T *h)\
{\
    return h->arr[0];\
}\
T heap_pop_##T(heap_##T *h)\
{\
    T res = h->arr[0];\
    if (heap_empty_##T(h)) return res;\
    h->arr[0] = h->arr[--h->i];\
    for (int i = 0; i < h->i;)\
    {\
        int r1 = (LEFT(i) <= h->i) ? LEFT(i) : -1, r2 = (RIGHT(i) <= h->i) ? RIGHT(i) : -1;\
        int r = (h->comp(h->arr[r1], h->arr[r2])) ? r1 : r2;\
        if (r != -1 && h->comp(h->arr[r], h->arr[i]))\
        {\
            T t = h->arr[r];\
            h->arr[r] = h->arr[i];\
            h->arr[i] = t;\
            i = r;\
        }\
        else\
            break;\
    }\
    return res;\
}

#endif