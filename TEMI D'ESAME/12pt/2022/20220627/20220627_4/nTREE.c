#include "nTREE.h"

struct node{
    char *key;
    struct node *children[N];
};

struct binarytree{
    struct node *root;
};

nTREE init(){
    nTREE bst=malloc(sizeof (*bst));
    bst->root=NULL;
    return bst;
}

static struct node *NEW(char *key, struct node *l, struct node *r){
    struct node *x=malloc(sizeof(*x));
    x->key=malloc(sizeof(char));
    strcpy(x->key,key);
    x->children[0]=l;
    x->children[1]=r;
    return x;
}

static struct node *insertR(struct node *node, char *key){
    if(node==NULL)
        return NEW(key,NULL,NULL);
    if(strcmp(key, node->key)>0)
        node->children[1]= insertR(node->children[1],key);
    else if(strcmp(key,node->key)<0)
        node->children[0]= insertR(node->children[0],key);
    return node;
}

void insertTREE(nTREE t, char *key){
    t->root=insertR(t->root, key);
}

void searchR(struct node *h, int *cnt){

    if(h==NULL)
        return;
    if(h->children[0]!=NULL & h->children[1]!=NULL){
        *cnt=*cnt+1;
        searchR(h->children[0],cnt);
        searchR(h->children[1],cnt);
    }
    if(h->children[0]!=NULL && h->children[1]==NULL)
        searchR(h->children[0],cnt);
    else if(h->children[0]==NULL && h->children[1]!=NULL)
        searchR(h->children[1],cnt);
}
int countIf(nTREE t){
    int cnt=0;
    searchR(t->root,&cnt);
    return cnt;
}




