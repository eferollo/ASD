#include "Graph.h"

struct graph{
    int V,E;
    int **madj;
    ST st;
};

static int **MATRIXint(int r, int c, int val){
    int i,j;
    int **t = malloc(r*sizeof (*t));
    for(i=0; i<r; i++) t[i]= malloc(c*sizeof (t));
    for(i=0;i<r;i++)
        for(j=0; j<c; j++)
            t[i][j]=val;
    return t;
}

Graph GRAPHinit(int V){
    Graph G = malloc(sizeof (*G));
    G->V=V;
    G->E=0;
    G->madj= MATRIXint(V,V,-1);
    G->st= STinit(V);
    return G;
}

static Edge EDGEcreate(int v, int w, int wt){
    Edge e;
    e.v=v;
    e.w=w;
    e.wt=wt;
    return e;
}

Graph GRAPHload(FILE *fin){
    char node1[MAX], node2[MAX];
    int i,V,id1,id2,wt;
    Graph G;
    fscanf(fin,"%d", &V);
    G= GRAPHinit(V);
    for(i=0; i<V; i++){
        fscanf(fin,"%s", node1);
        STinsert(G->st, ITEMload(node1));
    }
    while(fscanf(fin,"%s %s %d", node1, node2, &wt)!=EOF){
        id1= STsearch(G->st, node1);
        id2= STsearch(G->st, node2);
        if(id1>=0 && id2 >=0)
            GRAPHinsertE(G, EDGEcreate(id1,id2,wt));
    }
    return G;
}

void GRAPHinsertE(Graph G, Edge e){
    int v= e.v, w=e.w, wt=e.wt;
    G->madj[v][w] = wt;
    G->E++;
}

void GRAPHremoveE(Graph G, Edge e){
    int v= e.v, w=e.w;
    if(G->madj[v][w]!=-1)
        G->E--;
    G->madj[v][w] = -1;
}

void GRAPHstore(Graph G){
    int i,j;
    for(i=0; i<G->V; i++){
        STdisplay(G->st, i);
        for(j=0; j<G->V; j++)
            if(G->madj[i][j]!=-1){
                printf("\n\t");
                STdisplay(G->st,j);
                printf(" %d", G->madj[i][j]);
            }
        printf("\n\n");
    }
}

void EDGEstore(Graph G, Edge e){
    STdisplay(G->st, e.v);
    STdisplay(G->st,e.w);
    printf("%d\n", e.wt);
}

int GRAPHgetV(Graph G){
    return G->V;
}

ST GRAPHgetST(Graph G){
    return G->st;
}

void TSdfsR(Graph G, int v, int *ts, int *pre, int *time, int *type){
    int w;
    pre[v] = 0;
    for(w=0; w<G->V; w++){
        if(G->madj[w][v] != -1){
            if(pre[w] == -1)
                TSdfsR(G, w, ts, pre, time,type);
            else if(ts[w] == -1)
                *type=0;
        }
    }
    ts[(*time)++]=v;
}

int *DAGrts(Graph G, int *type){
    int *pre, *ts, v, time=0;
    pre=calloc(G->V, sizeof(int));
    ts=calloc(G->V, sizeof(int));
    for(v=0; v<G->V; v++){
        pre[v]=-1;
        ts[v]=-1;
    }
    for(v=0; v<G->V; v++)
        if(pre[v]==-1)
            TSdfsR(G, v, ts, pre, &time, type);
    return ts;
}

void GRAPHedges(Graph G, Edge *a){
    int v, w, E=0;
    if(G->E<=0) return;
    for(v=0; v<G->V; v++)
        for(w=0; w<G->V; w++)
            if(G->madj[v][w]!=-1)
                a[E++]= EDGEcreate(v,w,G->madj[v][w]);
}

void comb_sempl(int pos, Graph G, Edge *e, int *sol, int *bestsol, int n, int k, int start, int *end, int *bwt){
    int i, dag, swt=0;
    if(pos>=k){
        for(i=0; i<k; i++) GRAPHremoveE(G,e[sol[i]]);
        for(i=0; i<k; i++) swt += e[sol[i]].wt;
        DAGrts(G,&dag);
        if(!dag){
            *end=1;
            if(swt>*bwt){
                *bwt=swt;
                for(i=0;i<k;i++) bestsol[i]=sol[i];
            }
        }
        for(i=0;i<k;i++)
            GRAPHinsertE(G,e[sol[i]]);
        return;
    }
    for(i=start; i<n; i++){
        sol[pos]=i;
        comb_sempl(pos+1,G,e, sol,bestsol,n,k,i+1,end,bwt);
    }
}

void createDAG(Graph G){
    int i,j, max=G->E-(G->V-1), end=0, wt=0;
    printf("\tIl numero massimo di archi rimovibili è: %d\n", max);
    int *sol=malloc(sizeof(int));
    int *bestsol=calloc(G->E,sizeof (int));
    Edge *e = malloc(G->E* sizeof(Edge));
    GRAPHedges(G,e);
    for(i=1; i<=max && !end; i++){
        sol=realloc(sol,i*sizeof (int));
        comb_sempl(0,G,e, sol,bestsol,G->E,i,0,&end,&wt);
    }
    printf("\tArchi rimossi:\n\t");
    for(j=0; j<i-1; j++)
        EDGEstore(G,e[bestsol[j]]);
    if(end)
        for(j=0;j<i-1;j++)
            GRAPHremoveE(G, e[bestsol[j]]);
}

void GRAPHmaxDist(Graph G, int *ts){
    int i,j,x,v,w;
    int *len=malloc(G->V * sizeof (int));
    for(i=0; i<G->V; i++){
        v=ts[i];
        for(j=0;j<G->V;j++)
            len[j]=-1;
        len[v]=0;
        for(j=i; j<G->V; j++){
            w=ts[j];
            if(len[w] == -1)
                continue;
            for(x=0; x<G->V; x++){
                if(G->madj[w][x] != -1)
                    if(len[x] == -1 || len[w] + G->madj[w][x] > len[x])
                        len[x]= len[w] + G->madj[w][x];
            }
        }
        for(j=0; j<G->V; j++){
            if(j==v)
                continue;
            STdisplay(G->st, v);
            STdisplay(G->st, j);
            printf(" distanza: %d\n", len[j] >= 0 ? len[j] : 0);
        }
        printf("\n");
    }
    free(len);
}

void GRAPHfree(Graph G){
    int i;
    STfree(G->st);
    for(i=0; i<G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    free(G);
}

