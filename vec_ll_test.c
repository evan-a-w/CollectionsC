#include <stdio.h>
#include <stdlib.h>

#define VEC_CREATE(TYPE) \
    typedef struct TYPE##_Vec {\
        TYPE * arr;\
        int size;\
        int capacity;\
    } TYPE##_vec;\
    TYPE##_vec * TYPE##_vinit(int start_cap) {\
        TYPE##_vec *vec = (TYPE##_vec *) malloc(sizeof(TYPE##_vec)); \
        vec->arr = (TYPE *) malloc(start_cap * sizeof(TYPE));\
        vec->capacity = start_cap;\
        vec->size = 0;\
        return vec;\
    }\
    void TYPE##_push(TYPE##_vec *vec, TYPE val) {\
        if (vec->size < vec->capacity) {\
            (vec->arr)[vec->size] = val;\
            vec->size++;\
        } else {\
            (vec->arr) = (TYPE *) realloc(vec->arr, vec->capacity * 2 * sizeof(TYPE));\
            vec->capacity *= 2;\
            (vec->arr)[vec->size] = val;\
            vec->size++;\
        }\
    }\
    TYPE TYPE##_pop(TYPE##_vec *vec) {\
        if (vec->size > 0) {\
            TYPE ret = vec->arr[vec->size - 1];\
            vec->size--;\
            return ret;\
        } else {\
            return vec->arr[0];\
        }\
    }\
    void TYPE##_vfree(TYPE##_vec *vec) {\
        free(vec->arr);\
        free(vec);\
    }\
    TYPE TYPE##_peek(TYPE##_vec *vec) {\
        if (vec->size > 0) {\
            return vec->arr[vec->size - 1];\
        }\
        return vec->arr[0];\
    }

typedef struct node {
    int data;
    struct node *next;
} *Node;

// Basic functionality
Node create_node(int);
void free_node(Node);
void insert_pos(Node, int);
int remove_pos(Node, int);
void traverse_node(Node);
Node reverse_node(Node);

// Sorting - cmp should return 1 if the left int should go before the right,
// 0 if it doesn't matter, and -1 if it should go after.
int default_cmp(int, int);

void bubble_sort(Node, int(*cmp)(int, int));

//TODO
void quick_sort(Node, int(*cmp)(int, int));
void merge_sort(Node, int(*cmp)(int, int));

// Basic functionality
Node create_node(int data) {
    Node res = malloc(sizeof(struct node));
    res->data = data;
    res->next = NULL;
    return res;
}

Node alt_create(Node next, int data) {
    Node res = create_node(data);
    res->next = next;
    return res;
}

void free_node(Node head) {
    if (head == NULL) return;
    Node curr = head->next;
    Node prev = head;
    for (Node curr = head->next; curr != NULL; prev = curr, curr = curr->next)
        free(prev); 
    free(prev);
}

void insert_pos(Node head, int data) {
    Node curr = head;
    Node next = curr->next;
    while (next != NULL) {
        curr = next;
        next = curr->next;
    }
    curr->next = create_node(data);
}

int remove_pos(Node head, int pos) {
    Node prev = head;
    Node curr = head->next;
    int i = 0;
    while (i < pos && curr != NULL) {
        prev = curr;
        curr = curr->next;
        i++;
    }
    if (curr == NULL) {
        return 0;
    } else {
        prev->next = curr->next;
        int data = curr->data;
        free(curr);
        return data;
    }
}

void traverse_node(Node head) {
    Node curr = head;
    while (curr != NULL) {
        printf("%d\n", curr->data);
        curr = curr->next;
    }
}

Node reverse_node(Node head) {
    if (head == NULL)
        return NULL;
    Node curr = head->next;
    Node prev = head;
    prev->next = NULL;
    while (curr != NULL) {
        Node next = curr->next;
        curr->next = prev;
        prev = curr;
        if (next == NULL)
            break;
        else
            curr = next;
    }
    return curr;
}

VEC_CREATE(Node)

int main(void) {
    Node head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    Node_vec *v = Node_vinit(5);
    for (Node c = head; c != NULL; c = c->next) {
        Node_push(v, c);
    }
    for (int i = 0; i < v->size; i++) printf("%d\n", v->arr[i]->data);
    Node_vfree(v);
    free_node(head);
}
