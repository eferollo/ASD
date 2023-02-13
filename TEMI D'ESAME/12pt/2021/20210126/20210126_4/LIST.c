#include "LIST.h"

typedef struct node *link;

struct node{
    int key;
    link next;
};

struct list{
    link head;
};

LIST LISTIinit(){
    LIST list=malloc(sizeof(*list));
    list->head=NULL;
    return list;
}

link newNode(int key, link next){
    link x = malloc(sizeof(*x));
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

void LISTInsert(LIST l, int key){
    l->head= InsListIns(l->head,key);
}

int find(int key, int *v, int n){
    int i;
    for(i=0; i<n; i++)
        if(key==v[i])
            return 1;
    return 0;
}

link ListDelKey(link h, int key){
    if(h==NULL)
        return NULL;

    link x,p;
    for(x=h, p=NULL; x!=NULL ; p=x,x=x->next){
        if(x->key==key){
            if(x==h)
                h=x->next;
            else
                p->next=x->next;
            free(x);
            break;
        }
    }
    return h;
}

void f(LIST l, int *v, int n){
    link x;
    int i=1,j;
    int *vr= malloc(sizeof(int));
    for(x=l->head; x!=NULL; x=x->next){
        if(!find(x->key,v,n)){
            vr= realloc(vr,i*sizeof(int));
            vr[i-1]=x->key;
            i++;
        }
    }
    for(j=0; j<i-1; j++)
        l->head= ListDelKey(l->head,vr[j]);
    free(vr);
}
