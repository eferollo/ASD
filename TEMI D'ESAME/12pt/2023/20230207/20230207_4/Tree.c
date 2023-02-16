#include "Tree.h"

struct tree{
    link root;
};

T TREEInit(){
    T t=malloc(sizeof(*t));
    t->root=NULL;
    return t;
}

link NEW(int key){
    link x=malloc(sizeof(*x));
    x->key=key;
    x->n=0;
    int i;
    for(i=0; i<N; i++)
        x->children[i]=NULL;
    return x;
}

void insertR(link h, int parent, int *vett, int dim){
    int i,j;
    int child1=N*parent+1;
    if(child1>dim)
        return;

    for(i=0, j=child1; i<N && j<child1+N && j<dim; i++, j++){
        if(vett[j]==INT_MIN)
            continue;
        h->children[i]=NEW(vett[j]);
        insertR(h->children[i],j,vett,dim);
        h->n++;
    }
}

void insertTREE(T t, int *vett, int dim){
    t->root=NEW(vett[0]);
    insertR(t->root,0,vett,dim);
}

int searchR(link h, int cnt, int max){
    if(h==NULL)
        return max;

    if(h->key >= 0)
        cnt++;
    else cnt=0;
    if(cnt>max)
        max=cnt;

    int i;
    for(i=0; i<N; i++)
        max= searchR(h->children[i], cnt, max);

    return max;
}

int f(T t){
    return searchR(t->root,0,0);
}