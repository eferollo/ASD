#include "PQ.h"

typedef struct Qnode *link;

struct Qnode{
    Edge e;
    link next;
};

struct pqueue{
    link head;
};

link NEW(Edge e, link next){
    link x=malloc(sizeof(*x));
    x->e=e;
    x->next=next;
    return x;
}

Q Qinit(){
    Q q=malloc(sizeof(*q));
    q->head=NULL;
    return q;
}

void Qput(Q q, Edge e){
    q->head=NEW(e,q->head);
}

int Qempty(Q q){
    return q->head==NULL;
}

Edge Qget(Q q){
    link t;
    Edge tmp;
    tmp=q->head->e;
    t=q->head->next;
    free(q->head);
    q->head=t;
    return tmp;
}
