#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgList.h"

typedef struct nodoPg_s *link;
typedef struct nodoPg_s{
    pg_t pg;
    link next;
}nodoPg_t;

typedef struct pgList_s{
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

link newNode(pg_t pg, link next){
    link x= malloc(sizeof *x);
    if(x==NULL)
        return NULL;
    x->pg=pg;
    x->next=next;
    return x;
}

pgList_t pgList_init(){
    pgList_t pgList=calloc(1,sizeof(tabPg_t));
    pgList->headPg=NULL;
    pgList->tailPg=NULL;
    pgList->nPg=0;
    return pgList;
}

void pgList_free(pgList_t pgList){
    link x,p;
    for(x=pgList->headPg; x!=NULL; x=p){
        p=x->next;
        pg_clean(&x->pg);
        free(x);
    }

    free(pgList);
}

void pgList_read(FILE *fp, pgList_t pgList){
    pg_t pg;
    if(fp==NULL)
        exit(printf("Error while opening pg file\n"));
    while(pg_read(fp, &pg))
        pgList_insert(pgList,pg);

}
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    if(pgList==NULL)
        return;
    link x;
    for(x=pgList->headPg; x!=NULL; x=x->next)
        pg_print(fp,&x->pg, invArray);
}

void pgList_insert(pgList_t pgList, pg_t pg){
    link x= newNode(pg,NULL);
    if(pgList->headPg==NULL){
        pgList->tailPg=x;
        pgList->headPg= pgList->tailPg;
    }else{
        pgList->tailPg->next=x;
        pgList->tailPg=x;
    }
    pgList->nPg++;
}

void pgList_remove(pgList_t pgList, char* cod){
    link x, p;
    for(x=pgList->headPg, p=NULL; x!=NULL; p=x, x=x->next){
        if(strcmp(x->pg.cod, cod)==0){
            if(x==pgList->headPg && x==pgList->tailPg)
                pgList->headPg= pgList->tailPg = NULL;
            else if(x==pgList->headPg)
                pgList->headPg= x->next;
            else if(x==pgList->tailPg){
                pgList->tailPg = p;
                p->next=NULL;
            }else
                p->next=x->next;
            free(x);
            break;
        }
    }
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link x;
    for(x=pgList->headPg; x!=NULL; x=x->next){
        if(strcmp(x->pg.cod, cod)==0)
            return &x->pg;
    }
    return NULL;
}
