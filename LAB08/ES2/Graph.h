#ifndef GRAPH_H_DEFINED
#define GRAPH_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include "ST.h"

typedef struct edge {int v; int w; int wt} Edge;
typedef struct graph *Graph;

Graph GRAPHinit(int V);
void GRAPHfree(Graph G);

void GRAPHinsertE(Graph G, int ind1, int ind2, int wt);
Graph GRAPHload(FILE *fin, ST st);
void GRAPHstore(Graph G, ST st);
int GRAPHlist(Graph G);
int GRAPHcheck(Graph G, int a, int b, int c);


#endif