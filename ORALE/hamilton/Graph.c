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
    G->ladj[w]= insertL(G->ladj[w],v,wt);
    G->E=G->E+2;
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

void dfsR(Graph G, Edge e, int *pre, int *path, int visit,int pos){
    int v,w=e.w;
    pre[w]=1;
    path[pos]=w;
    visit++;
    link t;
    for(t=G->ladj[w]; t!=NULL; t=t->next){
        if(pre[t->v]==-1)
            dfsR(G, EDGEcreate(w,t->v,1), pre,path,visit,pos+1);
    }
    if(visit==G->V){
        for(v=0; v<G->V; v++){
            printf("%d ",path[v]);
        }
        printf("\n");
    }
    pre[w]=-1;
    path[pos]=-1;
}

void hamiltonPath(Graph G){
    int v, *pre,*path;
    pre=malloc(G->V*sizeof(int));
    path=malloc(G->V*sizeof(int));
    for(v=0; v<G->V; v++){
        pre[v]=-1;
        path[v]=-1;
    }

    for(v=0; v<G->V; v++)
        if(pre[v]==-1)
            dfsR(G, EDGEcreate(v,v,1),pre,path,0,0);
}