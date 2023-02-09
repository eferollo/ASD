#include "ST.h"

#define MAX 31

struct symboltable{
    Item *a;
    int M, N;
};

ST STinit(int maxN){
    ST st=malloc(sizeof(*st));
    int i;
    st->a=malloc(maxN*sizeof (Item));
    for(i=0; i<maxN; i++)
        st->a[i]=ITEMsetvoid();
    st->N=0;
    st->M=maxN;
    return st;
}

void STinsert(ST st, Item val){
    int i = st->N++;
    if(st->N >= st->M){
        st->a= realloc(st->a, 2*st->M*sizeof(Item));
        if(st->a == NULL){
            printf("Error alloc\n");
            STfree(st);
            return;
        }
        st->M=2*st->M;
    }
    while((i>0) && KEYcmp(KEYget(&val), KEYget(&st->a[i-1]))==-1){
        st->a[i]=st->a[i-1];
        i--;
    }
    st->a[i]=val;
}

int searchR(ST st, int l, int r, Key k){
    int m= (l+r)/2;
    if(l>r)
        return -1;
    if(KEYcmp(k, KEYget(&st->a[m]))==0)
        return m;
    if(l==r)
        return -1;
    if(KEYcmp(k, KEYget(&st->a[m]))<0)
        return searchR(st,l,m-1,k);
    else
        return searchR(st,m+1,r,k);
}

int STsearch(ST st, Key k){
    return searchR(st,0,st->N-1, k);
}

void STdisplay(ST st, int index){
    ITEMstore(st->a[index]);
}

void STfree(ST st){
    if(st->a != NULL)
        free(st->a);
    free(st);
}