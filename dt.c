#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int data;
    struct node *next;
} *Node;

typedef struct deque {
    int size;
    Node list;
    Node end;
} *Deque;

void push_front(Deque, int);
int pop_front(Deque);
void push_back(Deque, int);
int pop_back(Deque);

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

Deque create_deque() {
    Deque res = malloc(sizeof(struct deque));
    res->size = 0;
    res->list = NULL;
    res->end = NULL;
    return res;
}

void free_deque(Deque s) {
    free_list(s->list);
    free(s);
}

void push_front(Deque s, int val) {
    Node new = create_node(val);
    new->next = s->list;
    s->list = new;
    if (s->end == NULL) s->end = new;
    s->size++;
}

int pop_front(Deque s) {
    if (s->list == NULL) {
        printf("Deque buffer underflow\n");
        return 0;
    }
    Node tmp = s->list;
    if (s->end == tmp) s->end = NULL;
    s->list = s->list->next;
    int res = tmp->data;
    free(tmp);
    s->size--;
    return res;
}

int peek_front(Deque s) {
    if (s->list == NULL) return 0;
    return s->list->data;
}

int peek_back(Deque s) {
    if (s->end == NULL) return 0;
    return s->end->data;
}

void push_back(Deque s, int val) {
    Node new = create_node(val);
    s->end->next = new;
    s->end = new;
    s->size++;
}

int pop_back(Deque s) {
    if (s->list == NULL) {
        printf("Deque buffer underflow\n");
        return 0;
    }
    Node tmp = s->list;
    s->list = s->list->next;
    int res = tmp->data;
    free(tmp);
    s->size--;
    return res;
}

int main(void) {
    Deque d = create_deque();
    push_back(d, 1);
    push_back(d, 2);
    push_back(d, 3);
    while (d->size > 0) printf("%d\n", pop_back(d));
}
