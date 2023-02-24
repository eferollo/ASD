#include "PQ.h"

typedef struct pqnode *linkp;

struct pqnode{
    int v;
    linkp next;
};

struct pqueue{
    linkp head;
};

PQ PQInit(){
    PQ pq= malloc(sizeof(*pq));
    pq->head=NULL;
    return pq;
}

linkp newPQnode(int v, linkp next){
    linkp x=malloc(sizeof(*x));
    x->v=v;
    x->next=next;
    return x;
}

linkp pop(linkp h, int v){
    if(h==NULL)
        return newPQnode(v,NULL);
    h= newPQnode(v,h);
    return h;
}

void PQpush(PQ pq, int v){
    pq->head=pop(pq->head,v);
}

void PQprint(PQ pq){
    linkp x;
    for(x=pq->head; x!=NULL; x=x->next)
        printf("%d ", x->v);
}

int PQempty(PQ pq){
    return pq->head==NULL;
}

int PQpop(PQ pq){
    int v=pq->head->v;
    linkp t=pq->head->next;
    free(pq->head);
    pq->head=t;
    return v;
}