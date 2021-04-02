#include "str_linked_list.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

str_node *str_node_init(char *str) {
    str_node *node = (str_node *) malloc(sizeof(str_node));
    node->str = (char *) malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(node->str, str);
    node->next = NULL;
    return node;
}

void str_node_free(str_node *head) {
    if (head == NULL) {
        return;
    }
    str_node *curr = head;
    str_node *next = head->next;
    while (next != NULL) {
        free(curr->str);
        free(curr);
        curr = next;
        next = curr->next;
    }
}

str_node *str_node_insert(str_node *head, char *str) {
    str_node *curr = head;
    str_node *next = curr->next;
    while (next != NULL) {
        curr = next;
        next = curr->next;
    }
    str_node *new = str_node_init(str);
    curr->next = new;
    return new;
}

str_node *str_node_insert_after(str_node *node, char *str) {
    str_node *next = node->next;
    str_node *new = str_node_init(str);
    node->next = new;
    new->next = next;
    return new;
}

char *str_node_remove(str_node *head, int pos) {
    str_node *prev = head;
    str_node *curr = head->next;
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
    char *str = curr->str;
    free(curr);
    return str;
}

char *str_node_remove_after(str_node *node) {
    if (node->next == NULL) {
        return NULL;
    }
    str_node *new_next = node->next->next;
    char *res = node->next->str;
    free(node->next);
    node->next = new_next;
    return res;
}
void str_node_delete(str_node *head, int pos) {
    str_node *prev = head;
    str_node *curr = head->next;
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
    free(curr->str);
    free(curr);
}

void str_node_delete_after(str_node *node) {
    if (node->next == NULL) {
        return;
    }
    str_node *new_next = node->next->next;
    free(node->next->str);
    free(node->next);
    node->next = new_next;
}

void str_node_traverse(str_node *head) {
    str_node *curr = head;
    while (curr != NULL) {
        printf("%s\n", curr->str);
        curr = curr->next;
    }
}

str_node *str_node_reverse(str_node *head) {
    if (head == NULL)
        return NULL;
    str_node *curr = head->next;
    str_node *prev = head;
    prev->next = NULL;
    while (curr != NULL) {
        str_node *next = curr->next;
        curr->next = prev;
        prev = curr;
        if (next == NULL)
            break;
        else
            curr = next;
    }
    return curr;
}
