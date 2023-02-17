#include "nTREE.h"

typedef struct node *link;

struct node{
    int key;
    int n;
    link children[N];
};

struct binarytree{
    link root;
};

static link NEW(int key){
    link x=malloc(sizeof (*x));
    x->key=key;
    x->n=0;
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

nTREE init(){
    nTREE tree=malloc(sizeof (*tree));
    int vett[]={10,1,-2,5,
                6,INT_MIN,1,5,-9,4,3,1,7,
                5,12};
    tree->root=NEW(vett[0]);
    insertR(tree->root, 0, vett, 15);
    return tree;
}

void searchR(link h, int *n1, int *n2, int *n3){
    if(h==NULL)
        return;
    int i;
    if(h->n==1)
        (*n1)++;
    else if(h->n==2)
        (*n2)++;
    else if(h->n==3)
        (*n3)++;
    for(i=0; i<N; i++)
        searchR(h->children[i],n1,n2,n3);
}
void countIf(nTREE t, int *n1, int *n2, int *n3){
    searchR(t->root,n1,n2,n3);
}