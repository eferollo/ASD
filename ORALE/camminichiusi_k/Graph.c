#include "Graph.h"

typedef struct node *link;
struct node{
    int v,wt;
    link next;
};

struct graph{
    int V,E;
    link *ladj;
};

Graph GRAPHinit(int V){
    Graph G=malloc(sizeof(*G));
    G->V=V;
    G->E=0;
    G->ladj= malloc(V*sizeof(link));
    return G;
}

Edge EDGEcreate(int v, int w, int wt){
    Edge e;
    e.v=v;
    e.w=w;
    e.wt=wt;
    return e;
}


link newNode(int v, int wt, link next){
    link x=malloc(sizeof(*x));
    x->next=next;
    x->v=v;
    x->wt=wt;
    return x;
}

link insertL(link h, int v, int wt){
    if(h==NULL)
        return newNode(v,wt,NULL);
    link t;
    for(t=h; t->next!=NULL; t=t->next);
    t->next= newNode(v,wt,NULL);
    return h;
}

void insertE(Graph G, Edge e){
    int v=e.v, w=e.w, wt=e.wt;
    G->ladj[v]= insertL(G->ladj[v],w,wt);
    G->E++;
}

void GRAPHinsertE(Graph G, int v, int w, int wt){
    insertE(G, EDGEcreate(v,w,wt));
}

Graph GRAPHload(FILE *fp){

    int V,v,w,wt;
    fscanf(fp,"%d ", &V);
    Graph G= GRAPHinit(V);

    while(fscanf(fp,"%d %d %d", &v,&w,&wt)!=EOF)
        GRAPHinsertE(G, v,w,wt);
    return G;
}

void dfsR(Graph G, Edge e, int *pre, int end, int k, int dist, int *cnt){
    int v,w=e.w;
    pre[w]=1;
    dist++;
    link t;
    for(t=G->ladj[w]; t!=NULL; t=t->next){
        if(pre[t->v]==-1)
            dfsR(G, EDGEcreate(w,t->v,1), pre,end,k,dist,cnt);
        else{
            v=t->v;
            if(v==end && dist==k){
                (*cnt)++;
            }
        }
    }
    pre[w]=-1;
}

void findCycles(Graph G, int k){
    int *pre,v;

    pre=malloc(G->V*sizeof(int));
    for(v=0; v<G->V; v++) pre[v]=-1;

    int cnt=0;
    dfsR(G, EDGEcreate(0,0,1),pre,0,k,0,&cnt);

    printf("Cicli lunghezza %d = %d\n",k,cnt);

}