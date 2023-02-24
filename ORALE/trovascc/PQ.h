#ifndef PQ_H
#define PQ_H
#include <stdio.h>
#include <stdlib.h>

typedef struct pqueue *PQ;

PQ PQInit();
void PQpush(PQ pq, int v);
void PQprint(PQ pq);
int PQempty(PQ pq);
int PQpop(PQ pq);
#endif
