#include "ST.h"

struct symboltable{
    Item *a;
    int N, M;
};

ST STtnit(int maxN, float alpha){
    int i;
    ST st=malloc(sizeof(*st));
    st->N=0;
    st->M=20; //sizeset maxn,alpha
    if(st->M != -1){
        st->a=malloc(st->M*sizeof (Item));
        //for(i=0; i<st->M; i++)
            //st->a[i]=ITEMsetvoid();
    }
    return st;
}

void STinsertLinear(ST st, Item item){
    /*
    int i=hash(Keyget(&item),st->M);
    while (full(st, i))
        i = (i+1)%st->M;
    st->a[i] = item;
    st->N++;
     */
}

Item STsearch(ST st, int key) {
    /*
    int i = hash(k, st->M);
    while (full(st, i))
        if (KEYcmp(k, KEYget(&st->a[i]))==0)
            return st->a[i];
        else
            i = (i+1)%st->M;
    return ITEMsetNull();
     */
}


void STinsertQuadratic(ST st, Item item){
    /*
    int i = 0, start = hash(KEYget(&item), st->M), index=start;
    while (full(st, index)) {
        i++;
        index = (start + c1*i + c2*i*i)%st->M;
    }
    st->a[index] = item;
    st->N++;
     */
}

Item STsearchQuadratic(ST st, int k) {
    /*
    int i=0, start = hash(k, st->M), index = start;
    while (full(st, index))
        if (KEYcmp(k, KEYget(&st->a[index]))==0)
            return st->a[index];
        else {
            i++;
            index = (start + c1*i + c2*i*i)%st->M;
        }
    return ITEMsetNull();
     */
}

void STinsertDoubleHashing(ST st, Item item) {
    /*
    int i = hash1(KEYget(&item), st->M);
    int j = hash2(KEYget(&item), st->M);
    while (full(st, i))
        i = (i+j)%st->M;
    st->a[i] = item;
    st->N++;
    */
}

Item STsearchDoubleHashing(ST st, int k) {
    /*
    int i = hash1(k, st->M);
    int j = hash2(k, st->M);
    while (full(st, i))
        if (KEYcmp(k, KEYget(&st->a[i]))==0)
            return st->a[i];
        else
            i = (i+j)%st->M;
    return ITEMsetNull();
     */
}

void STinsertLinearCHAINING(ST st, Item val) {
    /*
    int i;
    i = hash(KEYget(&val), st->M);
    st->heads[i] = NEW(val, st->heads[i]);
     */
}

/*
Item STsearch(ST st, Key k) {
    return searchR(st->heads[hash(k, st->M)], k, st->z);
}
Item searchR(link t, Key k, link z) {
    if (t == z) return ITEMsetNull();
    if ((KEYcmp(KEYget(&t->item), k))==0) return t->item;
    return searchR(t->next, k, z);
}
 */
