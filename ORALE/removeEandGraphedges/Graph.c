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

void GRAPHedges(Graph G, Edge *a){
    int v,w,E=0;
    for(v=0; v<G->V;v++){
        for(w=0; w<G->V; w++)
            if(G->madj[v][w]!=0)
                a[E++]= EDGEcreate(v,w,G->madj[v][w]);
    }
}

void edges(Graph G){
    int v;
    Edge *a=malloc(G->V*sizeof(Edge));
    GRAPHedges(G,a);
    for(v=0; v<G->V; v++)
        printf("%d %d\n", a[v].v, a[v].w);
}

void removeVertex(Graph G, int v){
    int w;
    for(w=0; w<G->V; w++)
        if(G->madj[v][w]!=0) {
            G->madj[v][w] = 0;
            //G->madj[w][v] = 0;       //non orientato
        }


    // lista adiacenze
    link t,x;
    for(t=G->ladj[v]; t!=NULL; t=t->next){
        link p;
        w=t->v;
        for(p=G->ladj[w], x=NULL; p!=NULL; x=p, p=p->next){
            if(p->v==v){
                if(p==G->ladj[w])
                    G->ladj[w]=p->next;
                else
                    x->next=p->next;
                free(p);
                break;
            }
        }
    }

    t=G->ladj[v];
    while(t!=NULL){
        G->ladj[v]=G->ladj[v]->next;
        free(t);
        t=G->ladj[v];
    }

}