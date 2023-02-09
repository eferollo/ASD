#include "nTREE.h"

typedef struct node *link;

struct node{
    int key;
    link l,c,r;
    int cnt;
};

struct binarytree{
    link root;
};

nTREE init(){
    nTREE t=malloc(sizeof (*t));
    t->root=NULL;
    return t;
}

static link NEW(int key, link l, link c, link r){
    link x=malloc(sizeof (*x));
    x->key=key;
    x->l=l;
    x->c=c;
    x->r=r;
    x->cnt=0;
    return x;
}

static link insertR(link h, int key, int *prec){
    if(h==NULL)
        return NEW(key,NULL,NULL,NULL);
    if(key>90 && key <96){
        *prec=h->key;
        h->c= insertR(h->c, key,prec);
    }
    else if(key<h->key){
        *prec=h->key;
        h->l= insertR(h->l,key,prec);
    }
    else if(key>h->key){
        *prec=h->key;
        h->r= insertR(h->r,key,prec);
    }
    if(h!=NULL && h->key==*prec)
        h->cnt++;
    return h;
}
void insertTREE(nTREE t, int c){
    int prec;
    t->root= insertR(t->root,c,&prec);
}

void searchR(link h, int *n1, int *n2, int *n3){
    if(h==NULL)
        return;
    if(h->cnt==1)
        *n1=*n1+1;
    else if(h->cnt==2)
        *n2=*n2+1;
    else if(h->cnt==3)
        *n3=*n3+1;
    if(h->l!=NULL) searchR(h->l,n1,n2,n3);
    if(h->r!=NULL) searchR(h->r,n1,n2,n3);
    if(h->c!=NULL) searchR(h->c,n1,n2,n3);
}
void countIf(nTREE t, int *n1, int *n2, int *n3){
    searchR(t->root,n1,n2,n3);
}