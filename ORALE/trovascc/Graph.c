#include "Graph.h"

typedef struct node *link;

struct node{
    int v;
    int wt;
    link next;
};

struct graph{
    int V, E;
    int **madj;
    link *ladj;
};

static link NEW(int v, int wt, link next){
    link x =malloc(sizeof(*x));
    x->v=v;
    x->wt=wt;
    x->next=next;
    return x;
}

static int **MATRIXint(int r, int c, int val){
    int i,j;
    int **t=malloc(r*sizeof(int *));
    for(i=0; i<r; i++) t[i]=malloc(sizeof(int));
    for(i=0; i<r; i++)
        for(j=0; j<c; j++)
            t[i][j]=val;
    return t;
}

static Edge EDGEcreate(int v, int w, int wt){
    Edge e;
    e.v=v;
    e.w=w;
    e.wt=wt;
    return e;
}

Graph GRAPHinit(int V){
    Graph G=malloc(sizeof(*G));
    G->V=V;
    G->E=0;
    G->madj= MATRIXint(V,V,0);
    G->ladj=NULL;
    return G;
}

link insertList(link h, int v, int wt){
    if(h==NULL)
        return NEW(v,wt,NULL);
    link x;
    for(x=h; x->next!=NULL; x=x->next);     //in coda
    x->next=NEW(v,wt,NULL);
    //h=NEW(v,wt,h); //in testa
    return h;
}

static void insertE(Graph G, Edge e){
    int v=e.v, w=e.w, wt=e.wt;
    //matrice adiacenze
    if(G->madj[v][w]==0) G->E++;
    G->madj[v][w]=wt;
    //G->madj[w][v]=wt;               //non orientato

    G->ladj[v]=insertList(G->ladj[v],w,wt);
    //G->ladj[w]= insertList(G->ladj[w],v,wt);     //non orientato
    //G->E++;
}

void GRAPHinsertE(Graph G, int v, int w, int wt){
    insertE(G, EDGEcreate(v,w,wt));
}

Graph GRAPHload(FILE *fp){
    int V,v,w,wt;

    fscanf(fp,"%d ", &V);
    Graph G= GRAPHinit(V);
    G->ladj=calloc(G->V, sizeof(link));
    while(fscanf(fp,"%d %d %d", &v, &w,&wt)!=EOF)
        GRAPHinsertE(G,v,w,wt);
    fclose(fp);
    return G;
}

void madjToladj(Graph G){
    int v,w;
    G->ladj=calloc(G->V, sizeof(link));

    for(v=0; v<G->V; v++)
        for(w=0; w<G->V; w++)
            if(G->madj[v][w]>0)
                G->ladj[v]=insertList(G->ladj[v],w,G->madj[v][w]);

}

void dfsR2(Graph G, Edge e, int *pre){
    link t;
    int w=e.w;
    pre[w]=1;
    printf("%d ",w);
    for(t=G->ladj[w]; t!=NULL; t=t->next){
        if(pre[t->v]==-1)
            dfsR2(G, EDGEcreate(w,t->v,1),pre);
    }
}

void dfsR(Graph G, Edge e, int *pre, PQ pq){
    link t;
    int v, w=e.w;
    pre[w]=1;
    for(t=G->ladj[w]; t!=NULL; t=t->next){
        if(pre[t->v]==-1)
            dfsR(G, EDGEcreate(w,t->v,1), pre,pq);
    }
    PQpush(pq,w);
}

Graph GRAPHtranspose(Graph G){
    //soluzione rapida trasporre matrice e convertire matrice in lista
    Graph gr= GRAPHinit(G->V);
    int v,w;
    for(v=0; v<G->V; v++)
        for(w=0; w<G->V; w++)
            if(G->madj[w][v]!=0){
                gr->madj[v][w]=G->madj[w][v];
                gr->E++;
            }

    madjToladj(gr);
    return gr;
}

void findSCC(Graph G){
    int v, *pre;

    pre=malloc(G->V*sizeof(int));
    PQ pq=PQInit();

    for(v=0; v<G->V; v++)
        pre[v]=-1;

    Graph gr= GRAPHtranspose(G);
    for(v=0; v<G->V; v++)
        if(pre[v]==-1)
            dfsR(gr, EDGEcreate(v,v,1),pre,pq);

    //PQprint(pq);

    for(v=0; v<G->V; v++)
        pre[v]=-1;

    while(!PQempty(pq)){
        v= PQpop(pq);
        if(pre[v]==-1){
            dfsR2(G, EDGEcreate(v,v,1),pre);
            printf("\n");
        }
    }
}