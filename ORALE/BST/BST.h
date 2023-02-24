#ifndef BST_H
#define BST_H
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct bst *BST;

BST BSTinit();
void BSTinsert(BST bst, int key);
void freeBST(BST bst);

int oneChildCount(BST bst);
void findLeafMinHeight(BST bst);
void deleteFromLevel(BST bst, int k);
int countLR(BST bst);
int findMax(BST bst);
int isSubTree(BST b1, BST b2);
void BSTinsert_root(BST bst, int key);
#endif
