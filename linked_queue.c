#include <stdlib.h>

typedef struct node
{
    struct node *next;
    int data;
    struct node *prev_pos;
} node;

typedef struct queue
{
    node *head;
    node *tail;
    int size;
} queue;

node *create_node(node *next, int data, node *prev_pos)
{
    node *res = malloc(sizeof(node));
    res->next = next;
    res->data = data;
    res->prev_pos = prev_pos;
    return res;
}

node *pop(queue *q)
{
    if (q->size == 0) return NULL;
    if (q->size == 1) q->tail = NULL;
    node *next = q->head->next;
    node *res = q->head;
    q->size--;
    q->head = next;
    
    return res;
}

void push(queue *q, node *n)
{
    if (q->head == NULL)
    {
        q->head = n; 
        q->tail = n;
    }
    else
    {
        q->tail->next = n;
        q->tail = n;
    }
    q->size++;
}

void free_node(node *n)
{
    if (!n) return;
    free_node(n->next); 
    free(n);
}