#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 3
typedef struct tree *T;

typedef struct node *link;

struct node{
    int key;
    int n;
    link children[N];
};

T TREEInit();
void insertTREE(T t, int *vett, int dim);
int f(T t);

#endif
