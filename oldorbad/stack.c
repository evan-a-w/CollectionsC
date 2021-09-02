#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    int *arr;
    int start;
    int end;
    int size;
    int capacity;
} *Stack;

Stack create_stack(int cap) {
    Stack s = malloc(sizeof(struct stack));
    s->start = 0;
    s->end = 0;
    s->size = 0;
    s->capacity = cap;
    s->arr = calloc(cap, sizeof(int));
}

void free_stack(Stack s) {
    free(s->arr);
    free(s);
}

void push(Stack s, int val) {
    if (s->size == 0) {
        s->arr[s->start] = val;
        s->end = (s->start + 1) % s->capacity;
    } else if (s->size < s->capacity) {
        s->arr[s->end++] = val;
        s->end %= s->capacity;
    } else {
        s->capacity *= 2;
        s->arr = realloc(s->arr, sizeof(int) * s->capacity);
        s->arr[s->end++] = val;
        s->end %= s->capacity;
    }
    s->size++;
}
