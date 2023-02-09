#include "DailyQuotationSet.h"

typedef struct BSTnode *link;

struct BSTnode{
    Quotation q;
    link l, r;
    int nq;
};

struct quotations_s{
    link root;
    int cnt;
};

Quotations BSTinit(){
    Quotations bst= calloc(1,sizeof (*bst));
    return bst;
}

static link NEW(Date d, Time t, float val, int nq, link l, link r){
    link x = calloc(1,sizeof(*x));
    x->q.date=d;
    x->q.time=t;
    x->q.n_qi=val*nq;
    x->q.d_qi=nq;
    x->l=l;
    x->r=r;
    x->nq=1;
    return x;
}

static link insertR(link h, Date d, Time t, float val, int nq){
    if(h == NULL)
        return NEW(d,t,val,nq,NULL,NULL);
    if(DATEcmp(d, Q_GETdate(h->q)) > 0)
        h->r= insertR(h->r, d,t,val,nq);
    else if(DATEcmp(d, Q_GETdate(h->q)) < 0)
        h->l= insertR(h->l, d, t,val,nq);
    else{
        h->q.n_qi += (nq*val);
        h->q.d_qi += nq;
    }
    if(h!=NULL)
        h->nq++;
    return h;
}

void BSTinsert(Quotations bst, Date d, Time t, float val, int nq){
    bst->root= insertR(bst->root,d,t,val,nq);
    if(bst->root!=NULL)
        bst->cnt++;
}

int BSTempty(Quotations bst){
    if(bst==NULL || bst->root == 0)
        return 1;
    return 0;
}

static void treeMinMax(link h, float *min, float *max){
    float val= Q_GETval(h->q);
    if(h==NULL)
        return;
    if(*min<0 || *min>val)
        *min=val;
    if(*max<0 || *max<val)
        *max=val;
    if(h->r)
        treeMinMax(h->r,min,max);
    if(h->l)
        treeMinMax(h->l,min,max);
}

void BSTgetMinMax(Quotations bst, float *min, float *max){
    if(BSTempty(bst))
        return;
    treeMinMax(bst->root,min,max);
}
static void treePrintR(link h){
    if(h==NULL)
        return;
    treePrintR(h->l);
    Q_print(h->q);
    treePrintR(h->r);
}

static Quotation searchR(link h, Date d){
    if(h==NULL)
        return Q_setNull();
    if(DATEcmp(d, Q_GETdate(h->q))==0)
        return h->q;
    else if(DATEcmp(d, Q_GETdate(h->q))<0)
        return searchR(h,d);
    else
        return searchR(h->r,d);
}

Quotation BSTquotationSaearh(Quotations bst, Date d){
    return searchR(bst->root, d);
}

void BSTprint(Quotations bst){
    if(BSTempty(bst))
        return;
    treePrintR(bst->root);
}

static void treeMinMaxDate(link h, Date d1, Date d2, float *min, float *max){
    float val;
    if(h==NULL)
        return;
    if(DATEcmp(d1, Q_GETdate(h->q))<0)
        treeMinMaxDate(h->l,d1,d2,min,max);
    if(DATEcmp(d2, Q_GETdate(h->q))>0)
        treeMinMaxDate(h->r,d1,d2,min,max);
    if(DATEcmp(d1, Q_GETdate(h->q))<=0 && DATEcmp(d2, Q_GETdate(h->q))>=0){
        val= Q_GETval(h->q);
        if(*min<0 || *min>val)
            *min=val;
        if(*max<0 || *max<val)
            *max=val;
    }
}

void BSTquotationMinMaxDate(Quotations bst, Date d1, Date d2, float *min, float *max){
    if(BSTempty(bst))
        return;
    treeMinMaxDate(bst->root,d1,d2,min,max);
}

static int treeHeight(link h, int d, int *max){
    int l,r;
    if(h==NULL)
        return 0;
    if(h->l == NULL && h->r == NULL){
        if(d>*max)
            *max=d;
        return 1;
    }
    l = treeHeight(h->l, d+1, max);
    r = treeHeight(h->r, d+1, max);
    if(h->l == NULL)
        return l+1;
    if(h->r == NULL)
        return r+1;
    if(l<r)
        return l+1;
    else return r+1;
}

link rotR(link h){
    link x=h->l;
    h->l = x->r;
    x->r=h;
    x->nq=h->nq;
    if(h->l)
        h->nq=h->l->nq;
    else if(h->r)
        h->nq=h->r->nq;
    else h->nq=1;
    return x;
}

link rotL(link h){
    link x=h->r;
    h->r = x->l;
    x->l=h;
    x->nq=h->nq;
    if(h->l)
        h->nq=h->l->nq;
    else if(h->r)
        h->nq=h->r->nq;
    else h->nq=1;
    return x;
}

static link partR(link h, int r){
    int t;
    if(h->l)
        t=h->l->nq;
    else t=0;
    if(h==NULL)
        return NULL;
    if(t>r){
        h->l= partR(h->l,r);
        h=rotR(h);
    }
    if(t<r){
        h->r= partR(h->r, r-t-1);
        h=rotL(h);
    }
    return h;
}

static link balanceR(link h){
    if(h==NULL)
        return NULL;
    int r=(h->nq+1)/2-1;
    h= partR(h,r);
    h->l= balanceR(h->l);
    h->r= balanceR(h->r);
    return h;
}

static void treeBalance(Quotations bst){
    bst->root= balanceR(bst->root);
}

void BSTbalance(Quotations bst, int s){
    if(BSTempty(bst))
        return;
    int min,max=-1;
    min = treeHeight(bst->root, 1,&max);
    if(bst->root && (bst->root->l == NULL || bst->root->r ==NULL))
        min=0;
    printf("START:\n\tSotto albero sinistro = %d \n\tSotto albero destro = %d\n", min, max);
    if(min == 0 || (max/min) > s){
        treeBalance(bst);
        max=-1;
        min = treeHeight(bst->root, 1, &max);
        printf("\nBILANCIAMENTO:\n\tSotto albero sinistro = %d \n\tSotto albero destro = %d\n", min, max);
    }
}

static void treeFree(link h){
    if(h==NULL)
        return;
    treeFree(h->l);
    treeFree(h->r);
    free(h);
}

void BSTfree(Quotations bst){
    if(BSTempty(bst))
        return;
    treeFree(bst->root);
    free(bst);
}