#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include "ST.h"

#define MAX 31

typedef struct edge {int v; int w; int wt} Edge;
typedef struct graph *Graph;

Graph GRAPHinit(int V);
void GRAPHfree(Graph G);

Graph GRAPHload(FILE *fin);
void GRAPHstore(Graph G);
void EDGEstore(Graph G, Edge e);
void GRAPHinsertE(Graph G, Edge e);
void GRAPHremoveE(Graph G, Edge e);
void GRAPHedges(Graph G, Edge *a);
int GRAPHgetV(Graph G);
ST GRAPHgetST(Graph G);

void TSdfsR(Graph G, int v, int *ts, int *pre, int *time, int *type);
void createDAG(Graph G);
int *DAGrts(Graph G, int *type);
void GRAPHmaxDist(Graph G, int *ts);

#endif
