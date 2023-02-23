#ifndef PQ_H
#define PQ_H
#include <stdio.h>
#include <stdlib.h>

typedef struct pqueue *Q;
typedef struct {int v,w,wt;} Edge;

Q Qinit();
int Qempty(Q q);
Edge Qget(Q q);
void Qput(Q q, Edge e);

#endif
