#include "LIST.h"

typedef struct node *link;

struct node{
    int key;
    link next;
};

struct list{
    link head;
    int n;
};

static link NEW(int key, link next){
    link x=malloc(sizeof(*x));
    x->key=key;
    x->next=next;
    return x;
}

list LISTinit(){
    list h=malloc(sizeof(*h));
    h->head=NULL;
    h->n=0;
    return h;
}

link ListIns(link h, int key){
    if(h==NULL)
        return NEW(key,NULL);
    link x,p;
    for(x=h->next, p=h; x!=NULL; p=x, x=x->next);
    p->next=NEW(key,x);

    return h;
}

void insertList(list L, int key){
    L->head= ListIns(L->head, key);
    if(L->head!=NULL)
        L->n++;
}

link searchList(link h, int start){
    link x;
    int i;
    for(x=h, i=0; x!=NULL, i<=start; x=x->next, i++){
        if(i==start)
            return x;
    }
    return NULL;
}

void splice(list L1, list L2, int start, int num){
    link x,s,x1,p1;
    int i;
    for(i=0; i<num; i++){
        if(x==NULL)
            break;
        x=L2->head;
        s= searchList(L1->head, start);
        for(x1=s->next, p1=s; ;p1=x1, x1=x1->next){
            p1->next=NEW(x->key,x1);
            L1->n++;
            start++;
            break;
        }
        L2->head=x->next;
        free(x);
        L2->n--;
        x=x->next;
    }
}
