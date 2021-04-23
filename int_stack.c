#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} *Node;

typedef struct stack {
    int size;
    Node list;
} *Stack;

void push(Stack, int);
int pop(Stack);

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

Stack create_stack() {
    Stack res = malloc(sizeof(struct stack));
    res->size = 0;
    res->list = NULL;
    return res;
}

void push(Stack s, int val) {
    Node new = create_node(val);
    new->next = s->list;
    s->list = new;
    s->size++;
}

int pop(Stack s) {
    if (s->list == NULL) {
        printf("Stack buffer underflow\n");
        return 0;
    }
    Node tmp = s->list;
    s->list = s->list->next;
    int res = tmp->data;
    free(tmp);
    s->size--;
    return res;
}
