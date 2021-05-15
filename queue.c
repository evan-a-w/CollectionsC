#include <stdio.h>
#include <stdlib.h>

typedef struct char_q {
    char *arr;
    int start;
    int end;
    int size;
    int capacity;
} char_queue;

char_queue *char_qinit(int capacity) {
    char_queue *res = malloc(sizeof(char_queue));
    res->arr = malloc(sizeof(char)*capacity);
    res->start = 0;
    res->end = 0;
    res->size = 0;
    res->capacity = capacity;
    return res;
}

void char_qfree(char_queue *q) {
    free(q->arr);
    free(q);
}

char char_qpop(char_queue *q) {
    if (q->size == 0) return q->arr[0];
    char res = q->arr[q->start++]; 
    q->start %= q->capacity;
    q->size--;
    return res;
}

char_queue *char_qpush(char_queue *q, char val) {
    if (q->size < q->capacity) {
        q->arr[q->end++] = val;
        q->end %= q->capacity;
        q->size++;
    } else {
        char_queue *new = char_qinit(q->capacity * 5); 
        while (q->size > 0) {
            char_qpush(new, char_qpop(q));
        } 
        char_qfree(q);
        q = new;
        q->arr[q->end++] = val;
        q->end %= q->capacity;
        q->size++;
    }
    return q;
}

int main(void) {
    char_queue *q = char_qinit(2);
    q=char_qpush(q, 'a');
    q=char_qpush(q, 'b');
    q=char_qpush(q, 'c');
    q=char_qpush(q, 'd');
    q=char_qpush(q, '\0');
    printf("%s\n", q->arr);
    char_qpop(q);
    char_qpop(q);
    while (q->size > 0) putchar(char_qpop(q));
    putchar('\n');
    q = char_qpush(q, 'z');
    printf("%c\n", q->arr[q->end-1]);
     
}
