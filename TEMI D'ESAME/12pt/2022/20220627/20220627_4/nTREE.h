#ifndef NTREE_H
#define NTREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 2
typedef struct binarytree *nTREE;

nTREE init();
void insertTREE(nTREE t, char *key);
int countIf(nTREE t);
#endif
