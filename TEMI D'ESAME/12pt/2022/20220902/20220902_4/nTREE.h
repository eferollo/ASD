#ifndef NTREE_H
#define NTREE_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct binarytree *nTREE;

nTREE init();
void insertTREE(nTREE t, int c);
void countIf(nTREE t, int *n1, int *n2, int *n3);

#endif
