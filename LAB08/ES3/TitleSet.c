#include "TitleSet.h"

typedef struct node *link;

struct node{
    Title t;
    link next;
};

struct titles_s{
    link head;
    int nt;
};

Titles titles_init(){
    Titles titles=calloc(1, sizeof(*titles));
    return titles;
}

static link newNode(Title t, link next){
    link x=calloc(1,sizeof(*x));
    if(x==NULL)
        return NULL;
    x->t=t;
    x->next=next;
    return x;
}

void TitlesListIns(Titles titles, Title t){
    link x,p;
    if(titles==NULL)
        return;
    if(titles->head == NULL)
        titles->head= newNode(t,NULL);
    else if(TITLEcmp(TITLEgetKey(t), TITLEgetKey(titles->head->t)) < 0)
        titles->head= newNode(t,titles->head);
    else{
        for(x=titles->head->next, p=titles->head; x!=NULL && TITLEcmp(TITLEgetKey(t), TITLEgetKey(x->t))>0; p=x, x=x->next);
        p->next= newNode(t,x);
    }
    titles->nt++;
}

Title TitlesListSearch(Titles t, char *name){
    link x;
    if(TitlesListEmpty(t))
        return NULL;
    for(x=t->head; x!=NULL; x=x->next){
        if(TITLEcmp((Key)name, TITLEgetKey(x->t))==0)
            return x->t;
        if(TITLEcmp((Key)name, TITLEgetKey(x->t))<0)
            return NULL;
    }
    return NULL;
}
int TitlesListEmpty(Titles titles){
    if(titles == NULL || titles->head==NULL)
        return 1;
    return 0;
}

void printTitles(Titles titles){
    link x;
    if(TitlesListEmpty(titles))
        return;
    for(x=titles->head; x!=NULL; x=x->next)
        TITLEprint(x->t);
}

void freeTitlesLIST(Titles titles){
    link x,p;
    for(x=titles->head; x!=NULL; x=p){
        p=x->next;
        freeTITLE(x->t);
        free(x);
    }
    free(titles);
}