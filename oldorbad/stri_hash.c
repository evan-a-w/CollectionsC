#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "stri_hash.h"

pstri_node *pstri_node_init(pstri *p) {
    pstri_node *node = (pstri_node *) malloc(sizeof(pstri_node));
    node->p = p;
    node->next = NULL;
    return node;
}

void pstri_node_free(pstri_node *head) {
    if (head == NULL) {
        return;
    }
    pstri_node *curr = head;
    pstri_node *next = head->next;
    while (next != NULL) {
        pstri_free(curr->p);
        free(curr);
        curr = next;
        next = curr->next;
    }
}

pstri_node *pstri_node_insert(pstri_node *head, pstri *p) {
    pstri_node *curr = head;
    pstri_node *next = curr->next;
    while (next != NULL) {
        curr = next;
        next = curr->next;
    }
    pstri_node *new = pstri_node_init(p);
    curr->next = new;
    return new;
}

pstri_node *pstri_node_insert_after(pstri_node *node, pstri *p) {
    pstri_node *next = node->next;
    pstri_node *new = pstri_node_init(p);
    node->next = new;
    new->next = next;
    return new;
}

pstri *pstri_node_remove(pstri_node *head, int pos) {
    pstri_node *prev = head;
    pstri_node *curr = head->next;
    int i = 0;
    while (i < pos && curr != NULL) {
        prev = curr;
        curr = curr->next;
        i++;
    }
    if (curr == NULL) {
        return 0;
    }
    prev->next = curr->next;
    pstri *p = curr->p;
    free(curr);
    return p;
}

pstri *pstri_node_remove_after(pstri_node *node) {
    if (node->next == NULL) {
        return NULL;
    }
    pstri_node *new_next = node->next->next;
    pstri *res = node->next->p;
    free(node->next);
    node->next = new_next;
    return res;
}

void pstri_node_delete(pstri_node *head, int pos) {
    pstri_node *prev = head;
    pstri_node *curr = head->next;
    int i = 0;
    while (i < pos && curr != NULL) {
        prev = curr;
        curr = curr->next;
        i++;
    }
    if (curr == NULL) {
        return;
    }
    prev->next = curr->next;
    free(curr->p);
    free(curr);
}

void pstri_node_delete_after(pstri_node *node) {
    if (node->next == NULL) {
        return;
    }
    pstri_node *new_next = node->next->next;
    free(node->next->p);
    free(node->next);
    node->next = new_next;
}

void pstri_node_traverse(pstri_node *head) {
    pstri_node *curr = head;
    while (curr != NULL) {
        printf("%s : %d\n", curr->p->str, curr->p->val);
        curr = curr->next;
    }
}

pstri_node *pstri_node_reverse(pstri_node *head) {
    if (head == NULL)
        return NULL;
    pstri_node *curr = head->next;
    pstri_node *prev = head;
    prev->next = NULL;
    while (curr != NULL) {
        pstri_node *next = curr->next;
        curr->next = prev;
        prev = curr;
        if (next == NULL)
            break;
        else
            curr = next;
    }
    return curr;
}

pstri *pstri_init(char *str, int val) {
    pstri *p = malloc(sizeof(pstri));
    p->str = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(p->str, str);
    p->val = val;
    return p;
}

void pstri_free(pstri *p) {
    if (p == NULL) {
        return;
    }
    free(p->str);
    free(p);
}

int default_hash_func(char *str, int capacity) {
    int len = strlen(str);
    int index = 7;
    for (int i = 0; i < len; i++) {
        index = (31 * index + str[i]) % capacity;
    }
    return index;
}

hash_stri *hash_stri_init(int capacity) {
    hash_stri *t = malloc(sizeof(hash_stri));
    t->hash_func = default_hash_func;
    t->size = 0;
    t->capacity = capacity;
    t->arr = calloc(t->capacity, sizeof(pstri_node *));
    return t;
}

void hash_stri_free(hash_stri *t) {
    for (int i = 0; i < t->capacity; i++) {
        pstri_node_free(t->arr[i]);
    }
    free(t->arr);
    free(t);
}

hash_stri *hash_stri_resize(hash_stri *t) {
    hash_stri *n = hash_stri_init(t->capacity * 2 + 1);
    n->size = t->size;
    for (int i = 0; i < t->capacity; i++) {
        pstri_node *node = t->arr[i];
        while (node != NULL) {
            pstri_node *next = node->next;
            node->next = NULL;
            hash_stri_set_nocopy(n, node);
            node = next;
        }
    }
    free(t->arr);
    free(t);
    return n;
}

int hash_stri_get(hash_stri *t, char *key, int *res) {
    pstri_node *node = t->arr[t->hash_func(key, t->capacity)];
    while (node != NULL && strcmp(node->p->str, key) != 0) {
        node = node->next;
    }
    if (node == NULL) {
        return 0;
    }
    *res = node->p->val;
    return 1;
}

hash_stri *hash_stri_set(hash_stri *t, char *key, int val) {
    double load_factor = (1.0 * t->size) / t->capacity;
    if (load_factor > 0.8) {
        t = hash_stri_resize(t);
    }

    pstri_node *node = t->arr[t->hash_func(key, t->capacity)];
    pstri_node *prev;
    if (node == NULL) {
        t->arr[t->hash_func(key, t->capacity)] = pstri_node_init(pstri_init(key, val));
        t->size++;
        return t;
    }
    while (node != NULL && strcmp(node->p->str, key) != 0) {
        prev = node;
        node = node->next;
    }
    if (node == NULL) {
        prev->next = pstri_node_init(pstri_init(key, val));
        t->size++;
        return t;
    }
    node->p->val = val;
    return t;
}

void hash_stri_set_nocopy(hash_stri *t, pstri_node *p) {
    pstri_node *node = t->arr[t->hash_func(p->p->str, t->capacity)];
    pstri_node *prev;
    if (node == NULL) {
        t->arr[t->hash_func(p->p->str, t->capacity)] = p;
        return;
    }
    while (node != NULL) {
        prev = node;
        node = node->next;
    }
    prev->next = p;
}
