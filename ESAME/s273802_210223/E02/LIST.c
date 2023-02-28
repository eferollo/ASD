#include "LIST.h"

typedef struct node *link;

struct node{
    int key;
    link next;
    link prev;
};

struct list{
    link head;
};

link newNode(int key, link next,link prev){
    link x=malloc(sizeof(*x));
    if(x==NULL)
        return NULL;
    x->key=key;
    x->next=next;
    x->prev=prev;
    return x;
}

LIST LISTinit(){
    LIST h=malloc(sizeof(*h));
    h->head=NULL;
    return h;
}

link insList(link h, int key){
    link x,p;
    if(h==NULL)
        return newNode(key,h,NULL);
    for(x=h->next, p=h; x!=NULL; p=x, x=x->next);
    p->next= newNode(key,x,p);
    return h;
}

void LISTinsert(LIST l, int key){
    l->head= insList(l->head, key);
}

int check(int key, int a, int b){
    if(key>=a && key<=b)
        return 1;
    return 0;
}

link listDelKey(link prev, link x, LIST l){
    link p;

    p=x->next;
    p->prev=prev;
    if(prev!=NULL)
        prev->next=p;
    else l->head=p;
    free(x);
    return p;
}

void f(LIST l, int a, int b){
    link x;
    int flag=0;

    for(x=l->head; x!=NULL; (flag) ? (x=l->head) : (x=x->next)){
        if(check(x->key, a,b)){
            x=listDelKey(x->prev,x,l);
            if(x!=l->head){
                x=x->prev;
                flag=0;
            } else flag=1;
        }else flag=0;
    }

}
