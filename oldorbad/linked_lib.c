#include <stdio.h>
#include <stdlib.h>
#include <vec_macro.h>

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
int get_nth_last(int n, Node head);

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

int get_nth_last(int n, struct node *head) {
    if (head == NULL) return 0;
    int l = 0;
    Node curr;
    for (curr = head; curr != NULL; curr = curr->next) l++;
    int des_pos = l - n;
    int i = 0;
    for (curr = head; i < des_pos && curr != NULL; curr = curr->next, i++);
    return curr->data;
}

Node getIntersectionNode(Node headA, Node headB) {
    Node currA = headA;
    Node currB;
    while (currA != NULL) {
        currB = headB;
        while (currB != NULL && currB != currA) {
            currB = currB->next;
        }
        if (currB == currA) {
            return currB;
        }
        currA = currA->next;
    }
    return NULL;
}

Node middleNode(Node head){
    if (head == NULL || head->next == NULL) return head;
    int depth = 1;
    for (Node curr = head->next; curr != NULL; curr = curr->next) {
        depth++;
        Node new = curr;
        for (int c = 0; new != NULL && c < depth; new = new->next, c++);
        if (new == NULL) return curr;
    }
    return head;
}

Node reverseBetween(Node head, int left, int right){
    if (left == right) {
        return head;
    }
    Node before_left = head;
    Node nleft = head;
    Node nright = head;
    // Get to the left node and right nodes.
    for (int i = 1; nright->next != NULL && i < right; i++) {
        nright = nright->next;
        if (i < left) nleft = nright;
        if (i < left - 1) before_left = nright;
    }
    Node after_right = nright->next;

    Node prev = after_right;
    Node curr = nleft;
    while (curr->next != after_right) {
        Node tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }
    curr->next = prev;
    if (nleft != before_left) {
        before_left->next = curr;
        return head;
    }
    return nright;
}

int hasCycle(struct node *head) {
    if (head == NULL || head->next == NULL) return 0;
    Node curr = head;
    Node next = head;
    while (next != NULL && next->next != NULL) {
        curr = curr->next;
        next = next->next->next;
        if (next == curr) return 1;
    }

    return 0;
}

VEC_CREATE(Node);

struct node *getIntersectionNode(struct node *headA, struct node *headB) {
    Node_vec *vec = Node_vinit(30);
    struct node *currA = headA;
    for (Node currB = headB; currB != NULL; currB = currB->next) {
        Node_push(vec, currB);
    }
    for (; currA != NULL; currA = currA->next) {
        int i = 0;
        for (; i < vec->size && (vec->arr[i] != currA); i++);
        if (vec->arr[i] == currA) {
            Node res = vec->arr[i];
            Node_vfree(vec);
            return res;
        }
    }
    Node_vfree(vec);
    return NULL;
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
