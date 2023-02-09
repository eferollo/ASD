#include "ST.h"

struct symboltable{
    Item *a;
    int size;
    int maxN;
};

int searchR(ST st, int l, int r, KEY k);
void MergeSortR(ST A, ST B, int l, int r);
void Merge(ST A, ST B, int l, int q, int r);

ST STinit(int maxN){
    ST st=malloc(sizeof(*st));
    int i;
    st->a=malloc(maxN*sizeof(Item));
    for(i=0; i<maxN; i++)
        st->a[i]=ITEMsetvoid();
    st->maxN=maxN;
    st->size=0;
    return st;
}

void STfree(ST st){
    if(st->a != NULL)
        free(st->a);
    free(st);
}

int STcount(ST st){
    return st->size;
}

void STinsert(ST st, Item val){
    int i = st->size++;
    if(st->size >= st->maxN){
        st->a=realloc(st->a, 2*st->maxN*sizeof(Item));
        if(st->a == NULL){
            printf("Error alloc\n");
            STfree(st);
            return;
        }
        st->maxN = 2*st->maxN;
    }
    while( (i>0) && KEYcmp(KEYget(&val),KEYget(&st->a[i-1]))==-1){
        st->a[i]=st->a[i-1];
        i--;
    }
    st->a[i]=val;
}

int searchR(ST st, int l, int r, KEY k){
    int m= (l+r)/2;
    if(l>r)
        return -1;
    if(KEYcmp(k, KEYget(&st->a[m]))==0)
        return m;
    if(l==r)
        return -1;
    if(KEYcmp(k, KEYget(&st->a[m])) == -1)
        return searchR(st,l,m-1,k);
    else
        return searchR(st,m+1,r,k);
}

int STsearch(ST st, KEY k){
    return searchR(st,0,st->size-1, k);
}

void STdisplay(ST st, int index){
    ITEMstore(st->a[index]);
}

void Merge(ST A, ST B, int l, int q, int r) {
    int i, j, k;
    i = l;
    j = q+1;
    for (k = l; k <= r; k++)
        if (i > q)
            B->a[k]=A->a[j++];
        else if (j > r)
            B->a[k]=A->a[i++];
        else if (strcmp(A->a[i].id_elab, A->a[j].id_elab)<0 || strcmp(A->a[i].id_elab, A->a[j].id_elab) == 0 )
            B->a[k]=A->a[i++];
        else
            B->a[k]=A->a[j++];
    for ( k = l; k <= r; k++ )
        A->a[k]=B->a[k];
    return;
}

void MergeSortR(ST A, ST B, int l, int r) {
    int q;
    if (l >= r)
        return;
    q = (l + r) / 2;
    MergeSortR(A, B, l, q);
    MergeSortR(A, B, q + 1, r);
    Merge(A, B, l, q, r);
}

void STsort(ST st){
    ST st1 = STinit(st->size);
    int l=0, r=st->size-1;
    MergeSortR(st, st1, l, r);
    STfree(st1);
}