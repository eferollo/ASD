#include "List.h"

typedef struct node *link;

struct node{
    int l,r;
    link next;
};

struct list{
    link head;
};

list_t LISTInit(){
    list_t x=malloc(sizeof(*x));
    x->head=NULL;
    return x;
}

link newNode(int l, int r, link next){
    link x=malloc(sizeof(*x));
    x->next=next;
    x->l=l;
    x->r=r;
    return x;
}

int cmp(int a, int b){
    return (a>b);
}


link SortInsListIns(link h, int l, int r){
    if(h==NULL || cmp(h->l*h->r, l*r))
        return newNode(l,r,NULL);

    link x,p;
    for(x=h->next, p=h; x!=NULL && cmp(l*r, x->l*x->r); p=x, x=x->next);
    p->next= newNode(l,r,x);
    return h;
}

list_t prodCart(int *v1, int d1, int *v2, int d2){
    list_t list=LISTInit();
    int i,j;
    for(i=0; i<d1; i++){
        for(j=0;j<d2;j++){
            list->head= SortInsListIns(list->head, v1[i], v2[j]);
        }
    }
    return list;
}

void print(list_t list){
    link x;
    for(x=list->head; x!=NULL; x=x->next)
        printf("(%d,%d) ",x->l,x->r);
}