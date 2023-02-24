#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
typedef struct graph *Graph;
typedef struct{
    int v,w,wt;
}Edge;

Graph GRAPHload();
void hamiltonPath(Graph G);
#endif