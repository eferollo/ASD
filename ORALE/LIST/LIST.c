#include "LIST.h"

typedef struct node *link;

struct node{
    int val;
    link next;
};

struct list{
    link head;
};

link newNode(int val, link next){
    link x=malloc(sizeof(*x));
    x->val=val;
    x->next=next;
    return x;
}

LIST LISTinit(){
    LIST list=malloc(sizeof(*list));
    list->head=NULL;
    return list;
}

link insertR(link h, int val){
    if(h==NULL || val < h->val)
        return newNode(val,h);
    link x,p;
    for(x=h->next, p=h; x!=NULL && val > x->val; p=x, x=x->next);
    p->next= newNode(val,x);
    return h;
}

void LISTinsert(LIST l, int val){
    l->head= insertR(l->head, val);
}

link ListDelDup(link h){
    link x,p;
    x=h;
    while(x->next!=NULL){
        if(x->val==x->next->val) {
            p = x->next->next;
            free(x->next);
            x->next = p;
        }else
            x=x->next;
    }
    return h;
}

void listReverse(LIST l){
    link t, y=l->head, r=NULL;
    while(y!=NULL){
        t=y->next;
        y->next=r;
        r=y;
        y=t;
    }
    l->head=r;
}

LIST merge(LIST l1, LIST l2){
    link x,x1;
    LIST l3=LISTinit();

    for(x=l1->head, x1=l2->head; x!=NULL; x1=x1->next, x=x->next){
        LISTinsert(l3,x->val);
        LISTinsert(l3,x1->val);
    }

    l3->head= ListDelDup(l3->head);
    return l3;
}

void removeMinMax(LIST l, int min, int max){
    link x,p;
    int flag;

    for(x=l->head, p=NULL; x!=NULL; p=x, x= (flag) ? l->head : x->next){
        if(x->val >= min && x->val <= max){
            if(x==l->head){
                l->head=x->next;
                free(x);
                x=NULL;
                flag=1;
            }else{
                p->next=x->next;
                free(x);
                x=p;
                flag=0;
            }
        }else
            flag=0;
    }
}

void removeEven(LIST l){
    link x,p;
    int k,flag=0;
    for(x=l->head, p=NULL, k=0; x!=NULL; k++,p=x, x=(flag) ? l->head : x->next){
        if(k%2==0){
            if(x==l->head){
                l->head=x->next;
                free(x);
                x=NULL;
                flag=1;
            }else{
                flag=0;
                p->next=x->next;
                free(x);
                x=p;
            }
        }else
            flag=0;
    }
}

void addMissing(LIST l){
    link x;
    int r,i;
    for(x=l->head; x->next!= NULL; x=x->next){
        r=x->next->val-x->val;
        if(r!=1){
            for(i=x->val+1; i< x->next->val; i++){
                x->next= newNode(i,x->next);
                x=x->next;
            }
        }
    }
}

void freeList(link h){
    if(h==NULL)
        return;

    freeList(h->next);
    free(h);
}
