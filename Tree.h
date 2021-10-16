#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

typedef float Item;

typedef struct tree *Tree;

Tree TreeNew(int (*compare)(Item a, Item b));

void TreeFree(Tree t);

bool TreeMember(Tree t, Item v);

void TreeInsert(Tree t, Item v);

void TreeDelete(Tree t, Item v);

#endif
