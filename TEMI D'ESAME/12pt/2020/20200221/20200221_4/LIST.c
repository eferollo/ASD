#include "LIST.h"

typedef struct node *link;

struct node{
    int key;
    link next;
    link prev;
};

struct LIST{
    link head;
    link tail;
    int cnt;
};

link newNode(int key, link next, link prev){
    link x=malloc(sizeof(x));
    x->key=key;
    x->next=next;
    x->prev=prev;
    return x;
}

list LISTInit(){
    list L=malloc(sizeof(*L));
    if(L==NULL)
        return NULL;
    L->head=NULL;
    L->tail=NULL;
    L->cnt=0;
    return L;
}

link InsListIns(link h, int key, link *t){
    if(h==NULL)
        return newNode(key,NULL,NULL);
    link x,p;
    for(x=h->next, p=h; x!=NULL; p=x, x=x->next);
    p->next= newNode(key,x,p);
    *t=p->next;
    return h;
}
void LISTadd(list L, int key){
    L->head=InsListIns(L->head, key,&L->tail);
    L->cnt++;
}

void swap(list L, int k){
    if(k>L->cnt)
        return;
    int i,key;
    link x,x1;

    for(x=L->head,i=0; i<k && x!=NULL; i++, x=x->next);
    for(x1=L->tail, i=0; i<k && x1!=NULL; i++, x1=x1->prev);

    key=x->key;
    x->key=x1->key;
    x1->key=key;
}