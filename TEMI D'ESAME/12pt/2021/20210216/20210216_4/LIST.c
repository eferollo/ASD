#include "LIST.h"

typedef struct node *link;

struct node{
    int key;
    link next;
};

struct list{
    link head;
};

LIST LISTinit(){
    LIST list=malloc(sizeof(*list));
    list->head=NULL;
    return list;
}

link newNode(int key, link next){
    link x=malloc(sizeof(*x));
    x->key=key;
    x->next=next;
    return x;
}

link InsListIns(link h, int key){
    if(h==NULL)
        return newNode(key,NULL);

    link x,p;
    for(x=h->next, p=h; x!=NULL; p=x, x=x->next);
    p->next= newNode(key,x);
    return h;
}

void LISTinsert(LIST l, int key){
    l->head= InsListIns(l->head,key);
}

LIST *split(LIST l, int *n){
    LIST *lists=malloc(6*sizeof(lists));
    link x;
    int status, prev_s=-1,i=0;

    for(x=l->head; x!=NULL;  prev_s=status, x=x->next){
        status=(x->key%2);
        if(status!=prev_s){
            i++;
            lists=realloc(lists,i*sizeof(lists));
            lists[i-1]=LISTinit();
            LISTinsert(lists[i-1], x->key);
        }else{
            LISTinsert(lists[i-1], x->key);
        }
    }
    return lists;
}