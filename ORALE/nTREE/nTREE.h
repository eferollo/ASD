#ifndef NTREE_H
#define NTREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 3

typedef struct binarytree *nTREE;

nTREE init();
void findOddPath(nTREE t);
#endif