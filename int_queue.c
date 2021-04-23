#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} *Node;

typedef struct queue {
    int size;
    Node list;
    Node end;
} *Queue;

void push(Queue, int);
int pop(Queue);

Node create_node(int data) {
    Node res = malloc(sizeof(struct node));
    res->data = data;
    res->next = NULL;
    return res;
}

void free_list(Node head) {
    if (head == NULL) return;
    Node curr = head->next;
    Node prev = head;
    for (Node curr = head->next; curr != NULL; prev = curr, curr = curr->next)
        free(prev); 
    free(prev);
}

Queue create_queue() {
    Queue res = malloc(sizeof(struct queue));
    res->size = 0;
    res->list = NULL;
    res->end = NULL;
    return res;
}

void push(Queue s, int val) {
    Node new = create_node(val);
    s->list = new;
    s->end->next = new;
    s->end = new;
    s->size++;
}

int pop(Queue s) {
    if (s->list == NULL) {
        printf("Queue buffer underflow\n");
        return 0;
    }
    Node tmp = s->list;
    s->list = s->list->next;
    int res = tmp->data;
    free(tmp);
    s->size--;
    return res;
}
