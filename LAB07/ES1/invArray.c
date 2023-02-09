#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "invArray.h"

typedef struct invArray_s{
    inv_t *vettInv;
    int nInv;
    int maxInv;
}invArr_t;

invArray_t invArray_init(){
    invArray_t invArray=calloc(1, sizeof(invArr_t));
    invArray->maxInv=8;
    return invArray;
}

void invArray_read(FILE *fp, invArray_t invArray){
    if(invArray->vettInv != NULL)
        return;
    fscanf(fp,"%d", &invArray->nInv);
    invArray->vettInv=(inv_t *)malloc(invArray->nInv*sizeof(inv_t));
    int i;
    for(i=0; i<invArray->nInv; i++)
        inv_read(fp,&invArray->vettInv[i]);
}

void invArray_print(FILE *fp, invArray_t invArray){
    if(invArray == NULL)
        return;
    int i;
    for(i=0;i<invArray->nInv;i++)
        inv_print(fp,&invArray->vettInv[i]);
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp,&invArray->vettInv[index]);
}

int invArray_searchByName(invArray_t invArray, char *name){
    int i;
    if(invArray==NULL)
        return -1;
    for(i=0;i<invArray->nInv;i++)
        if(strcmp(invArray->vettInv[i].nome,name)==0)
            return i;
    return -1;
}

inv_t *invArray_getByIndex(invArray_t invArray, int index){
    if(invArray==NULL)
        return NULL;
    return &invArray->vettInv[index];
}