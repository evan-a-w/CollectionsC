#include "Tree.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define ABS(a) (((a) >= 0) ? (a) : (-(a)))

typedef struct avl
{
    Item v;
    struct avl *left;
    struct avl *right;
    int height;
} *AVL;

struct tree
{
    AVL t;
    int (*compare)(Item a, Item b); 
};

int height(AVL t);

AVL AVLNew(Item x);

AVL AVLInsert(AVL t, Item x, int (*compare)(Item a, Item b));

AVL AVLDelete(AVL t, Item x, int (*compare)(Item a, Item b));

AVL rotateLeft(AVL t);

AVL rotateRight(AVL t);

void AVLFree(AVL t);

bool AVLMember(AVL t, Item v, int (*compare)(Item a, Item b));

void AVLFree(AVL t)
{
    if (t)
    {
        AVLFree(t->left);
        AVLFree(t->right);
        free(t);
    }
}

Tree TreeNew(int (*compare)(Item a, Item b))
{
    Tree res = malloc(sizeof *res);
    res->t = NULL;
    res->compare = compare;
    return res;
}

AVL AVLNew(Item x)
{
    AVL res = malloc(sizeof *res);
    res->v = x;
    res->left = NULL;
    res->right = NULL;
    res->height = 0;
    return res;
}

AVL rotateLeft(AVL t)
{
    AVL res = t->right;
    int ah = height(t->left);
    int bh = height(res->left);
    int zh = height(res->right);
    t->right = res->left;
    res->left = t;
    t->height = MAX(ah, bh) + 1;
    res->height = MAX(t->height, zh) + 1;
    return res;
}

AVL rotateRight(AVL t)
{
    AVL res = t->left;
    int bh = height(res->right);
    int zh = height(t->right);
    int ah = height(res->left);
    t->left = res->right;
    res->right = t;
    t->height = MAX(bh, zh) + 1;
    res->height = MAX(ah, t->height) + 1;
    return res;
}

int height(AVL t)
{
    if (t)
        return t->height;
    else
        return -1;
}

AVL AVLInsert(AVL t, Item x, int (*compare)(Item a, Item b))
{
    if (t)
    {
        int cmp = compare(x, t->v);
        if (cmp == 0)
        {
            return t;
        }
        else if (cmp < 0)
        {
            int cl = (t->left) ? (t->left->v) : 0;
            t->left = AVLInsert(t->left, x, compare);
            t->height = MAX(height(t->left), height(t->right)) + 1;
            if (height(t->left) - height(t->right) > 1)
            {
                if (compare(cl, x) < 0)
                    t->left = rotateLeft(t->left);
                return rotateRight(t);
            }
            return t;
        }
        else
        {
            int cl = (t->right) ? (t->right->v) : 0;
            t->right = AVLInsert(t->right, x, compare);
            t->height = MAX(height(t->left), height(t->right)) + 1;
            if (height(t->right) - height(t->left) > 1)
            {
                if (compare(cl, x) > 0)
                    t->right = rotateRight(t->right);
                return rotateLeft(t);
            }
            return t;
        }
    }
    else
    {
        return AVLNew(x);
    }
}

AVL AVLDelete(AVL t, Item x, int (*compare)(Item a, Item b))
{
    return t;
}

void AVLFree(AVL t);

bool AVLMember(AVL t, Item v, int (*compare)(Item a, Item b));

void TreeFree(Tree t);

bool TreeMember(Tree t, Item v);

void TreeInsert(Tree t, Item v);

void TreeDelete(Tree t, Item v);

void printInOrder(AVL t)
{
    if (t)
    {
        printInOrder(t->left);
        printf(" %f", t->v);
        printInOrder(t->right);
    }
}

int cmpo(float a, float b)
{
    if (a > b)
        return 1;
    else if (a == b)
        return 0;
    else
        return -1;
}

void printLevel(AVL t, int l)
{
    if (t)
    {
        printLevel(t->right, l + 1);
        for (int i = 0; i < l; i++)
            putchar('\t');
        printf("%f\n", t->v);
        printLevel(t->left, l + 1);
    }
}

int main(void)
{
    AVL x = AVLNew(6);
    x = AVLInsert(x, 7, cmpo);
    x = AVLInsert(x, 4, cmpo);
    x = AVLInsert(x, 2, cmpo);
    x = AVLInsert(x, 5, cmpo);
    printLevel(x, 0);
    printf("-------\n");
    x = AVLInsert(x, 1, cmpo);
    printLevel(x, 0);
    printf("-------\n");
    x = AVLInsert(x, 8, cmpo);
    x = AVLInsert(x, 0, cmpo);
    printLevel(x, 0);
    printf("-------\n");
    x = AVLInsert(x, 7.5, cmpo);
    printLevel(x, 0);
    printf("-------\n");
    x = AVLInsert(x, 7, cmpo);
    printLevel(x, 0);
    printf("-------\n");
}
