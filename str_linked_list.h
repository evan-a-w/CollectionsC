#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct str_Node {
    struct str_Node *next;
    char *str;
} str_node;

// Initialise a node and its string with malloc, return a pointer to the node
str_node *str_node_init(char *str);

// Traverse the entire list and frees all nodes
void str_node_free(str_node *head);

// Insert at the end or insert after a given node
str_node *str_node_insert(str_node *head, char *str);
str_node *str_node_insert_after(str_node *node, char *str);

// Remove returns a pointer to the string held by the removed node.
// Delete does not, and frees the string.
// After deletes after, other ones delete nth node (0 indexed)
char *str_node_remove(str_node *head, int pos);
char *str_node_remove_after(str_node *node);
void str_node_delete(str_node *head, int pos);
void str_node_delete_after(str_node *node);

// Traverse prints all values, reverse reverses the list and returns a pointer
// to the new head.
void str_node_traverse(str_node *head);
str_node *str_node_reverse(str_node *head);
