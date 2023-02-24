#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>

typedef struct graph *Graph;

typedef struct edge{
    int v;
    int w;
    int wt;
} Edge;

Graph GRAPHload();
void edges(Graph G);
void removeVertex(Graph G, int v);
#endif