#include "List.h"

typedef struct node *link;

struct node{
    int key;
    int cnt;
    link next;
};

struct list{
    link head;
    int size;
};

list_t LISTinit(){
    list_t l=malloc(sizeof(*l));
    l->head=NULL;
    l->size=1;
    return l;
}

link newNode(int key, link next){
    link x=malloc(sizeof(*x));
    x->key=key;
    x->cnt=0;
    x->next=next;
    return x;
}

link InsListIns(link h, int key, int pos){
    if(h==NULL){
        h=newNode(key,NULL);
        h->next=h;
        h->cnt++;
        return h;
    }

    link x,p;
    if(pos==0){
        p=newNode(h->key,h->next);
        p->cnt++;
        h->key=key;
        h->next=p;
        return h;
    }

    for(x=h; x->next!=h; x=x->next){
        if(x->key==key){
            x->cnt++;
            return h;
        }
    }

    int i;
    for(x=h,i=0; i<pos; i++,x=x->next){
        if(i==pos-1){
            p=x->next;
            x->next= newNode(key,p);
            x->next->cnt++;
        }
    }
    return h;
}

void LISTinsert(list_t L, int posizione, int key){
    int pos;
    pos=posizione%L->size;
    L->head= InsListIns(L->head, key,pos);
    L->size++;
}

