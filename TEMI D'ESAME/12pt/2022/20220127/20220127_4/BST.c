#include "BST.h"

typedef struct BSTnode *link;

struct BSTnode{
    int val;
    link l, r;
    int cnt
};

struct binarysearchtree{
    link root;
};

static link NEW(int val, link l, link r){
    link x = malloc(sizeof(*x));
    x->val=val;
    x->l=l;
    x->r=r;
    x->cnt=0;
    return x;
}

BST BSTinit(){
    BST bst = malloc(sizeof(*bst));
    bst->root=NULL;
    return bst;
}

static link insertR(link h, int val){
    if(h==NULL)
        return NEW(val, NULL, NULL);
    if(val>h->val)
        h->r= insertR(h->r, val);
    else if(val<h->val)
        h->l=insertR(h->l, val);
    if(h!=NULL)
        h->cnt++;
    return h;
}

void BSTinsert(BST bst, int val){
    bst->root= insertR(bst->root, val);
}

static int isBST(link h){
    if(h==NULL)
        return 1;
    if(h->l!=NULL && h->val < h->l->val || h->r!=NULL && h->val > h->r->val)
        return 0;
    return isBST(h->l) && isBST(h->r);
}

int f(BST t){
    //t->root->r->r->val=10;
   return isBST(t->root);
}