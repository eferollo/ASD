#include "Title.h"

struct title_s{
    Quotations Q;
    Key name;
    float min, max;
};

Title TitleNEW(char *name){
    Title t=calloc(1,sizeof(*t));
    t->name=(Key) strdup(name);
    t->max=-1.0;
    t->min=-1.0;
    t->Q=BSTinit();
    return t;
}

int TITLEcmp(Key k1, Key k2){
    return strcmp(k1,k2);
}

Key TITLEgetKey(Title t){
    return t->name;
}

void TITLEInsTrans(Title t, Date date, Time time, float val, int nq){
    BSTinsert(t->Q,date,time, val,nq);
    float min=-1.0, max=-1.0;
    BSTgetMinMax(t->Q,&min,&max);
    t->min=min;
    t->max=max;
}

void TITLEprint(Title t){
    printf("\n%s MIN: %.2f  MAX: %.2f\n", (char *) t->name, t->min, t->max);
    BSTprint(t->Q);
}

Quotation TITLEgetQ_byDate(Title t, Date d){
    if(t->Q==NULL)
        return Q_setNull();
    return BSTquotationSaearh(t->Q,d);
}

float TITLEgetMin(Title t){
    return t->min;
}

float TITLEgetMax(Title t){
    return t->max;
}

void TITLEgetMinMaxDate(Title t, Date d1, Date d2, float *min, float *max){
    if(DATEcmp(d1,d2) < 0)
        BSTquotationMinMaxDate(t->Q,d1,d2,min,max);
    else if(DATEcmp(d1,d2) > 0)
        BSTquotationMinMaxDate(t->Q,d2,d1,min,max);
    else *min = *max = Q_GETval(BSTquotationSaearh(t->Q, d1));
}

void TITLEtreeBalance(Title t, int s){
    if(t->Q==NULL)
        return;
    BSTbalance(t->Q,s);
}

void freeTITLE(Title t){
    BSTfree(t->Q);
    free(t);
}