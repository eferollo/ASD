#ifndef BST_H
#define BST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct binarysearchtree *BST;

BST BSTinit();
void BSTinsert(BST bst, int val);
int f(BST t);
#endif