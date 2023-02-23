#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"

typedef struct graph *Graph;

/*typedef struct edge{
    int v;
    int w;
    int wt;
} Edge;*/

Graph GRAPHload();
void madjToladj(Graph G);
void GRAPHdfs(Graph G);
void GRAPHbfs(Graph G, int id);

#endif
