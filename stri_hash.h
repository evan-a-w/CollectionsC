#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define HASH_DEFAULT 3217

typedef struct PairStrInt {
    char *str;
    int val;
} pstri;

pstri *pstri_init(char *str, int val);
void pstri_free(pstri *p);

typedef struct pstri_Node {
    struct pstri_Node *next;
    pstri *p;
} pstri_node;

// Initialise a node and its pair with malloc, return a pointer to the node
pstri_node *pstri_node_init(pstri *p);

// Traverse the entire list and frees all nodes
void pstri_node_free(pstri_node *head);

// Insert at the end or insert after a given node
pstri_node *pstri_node_insert(pstri_node *head, pstri *p);
pstri_node *pstri_node_insert_after(pstri_node *node, pstri *p);

// Remove returns a pointer to the string held by the removed node.
// Delete does not, and frees the string.
// After deletes after, other ones delete nth node (0 indexed)
pstri *pistr_node_remove(pstri_node *head, int pos);
pstri *pstri_node_remove_after(pstri_node *node);
void pstri_node_delete(pstri_node *head, int pos);
void pstri_node_delete_after(pstri_node *node);

// Traverse prints all values, reverse reverses the list and returns a pointer
// to the new head.
void pstri_node_traverse(pstri_node *head);
pstri_node *pstri_node_reverse(pstri_node *head);

int default_hash_func(char *str, int capacity);

typedef struct StriHash {
    pstri_node **arr;
    int capacity;
    int size;
    int (*hash_func)(char* str, int capacity);
} hash_stri;

hash_stri *hash_stri_init(int capacity);
void hash_stri_free(hash_stri *t);
hash_stri *hash_stri_resize(hash_stri *t);

int hash_stri_get(hash_stri *t, char *key, int *res);
hash_stri *hash_stri_set(hash_stri *t, char *key, int val);
void hash_stri_set_nocopy(hash_stri *t, pstri_node *p);
