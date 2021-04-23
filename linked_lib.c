#include <stdio.h>
#include <stdlib.h>

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

// Sorting

int default_cmp(int l, int r) {
    if (l < r) return 1;
    else if (l == r) return 0;
    else return -1;
}

void bubble_sort(Node head, int(*cmp)(int, int)) {
    if (head == NULL || head->next == NULL) return;
    int sorted = 0;

    // Keep doing the business.
    while (!sorted) {
        sorted = 1;
        Node prev = NULL;
        Node curr = head;
        Node next = head->next; 
        for (;next != NULL;prev=curr,curr=next,next=next->next) {
            int c = cmp(curr->data, next->data);
            if (c == -1) {
                sorted = 0;
                if (prev != NULL) prev->next = next;
                curr->next = next->next;
                next->next = curr;
            }
        }
    }
}

int main(void) {
    Node head = alt_create(NULL, 4);
    head = alt_create(head, 6); 
    head = alt_create(head, 3);
    head = alt_create(head, 8);
    head = alt_create(head, 1);
    traverse_node(head);

    printf("\nAbout to sort...\n");
    bubble_sort(head, default_cmp);

    traverse_node(head);
}
