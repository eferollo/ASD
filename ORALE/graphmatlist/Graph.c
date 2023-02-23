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

static void insertE(Graph G, Edge e){
    int v=e.v, w=e.w, wt=e.wt;
    if(G->madj[v][w]==0) G->E++;
    G->madj[v][w]=wt;
    //G->madj[w][v]=wt;
}

void GRAPHinsertE(Graph G, int v, int w, int wt){
    insertE(G, EDGEcreate(v,w,wt));
}

link insertList(link h, int v, int wt){
    if(h==NULL)
        return NEW(v,wt,NULL);
    link x;
    for(x=h; x->next!=NULL; x=x->next);
    x->next=NEW(v,wt,NULL);
    return h;
}

Graph GRAPHload(FILE *fp){
    int V,v,w,wt;

    fscanf(fp,"%d ", &V);
    Graph G= GRAPHinit(V);

    while(fscanf(fp,"%d %d %d", &v, &w,&wt)!=EOF)
        GRAPHinsertE(G,v,w,wt);


    fclose(fp);

    /*for(int i=0; i<V; i++){
        for(int j=0; j<V; j++)
            printf("%d ", G->madj[i][j]);
        printf("\n");
    }*/
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

void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st){
    link t;
    int v,w=e.w;
    st[e.w]=e.v;
    pre[w]=(*time)++;
    for(t = G->ladj[w]; t != NULL; t=t->next){
        if(pre[t->v]==-1)
            dfsR(G, EDGEcreate(w,t->v,-1), time,pre,post,st);
        else{
            v=t->v;
            if(post[v]==-1)
                printf("%d  %d\n", v,w);
        }
    }
    post[w]=(*time)++;
}

void GRAPHdfs(Graph G){
    int v, time=0, *pre, *post, *st;
    pre=malloc(G->V*sizeof(int));
    post=malloc(G->V*sizeof(int));
    st=malloc(G->V*sizeof(int));

    for(v=0; v<G->V; v++){
        pre[v] = -1;
        post[v] = -1;
        st[v] = -1;
    }

    for(v=0; v<G->V; v++)
        if(pre[v] == -1)
            dfsR(G, EDGEcreate(v,v,-1), &time, pre,post,st);

    for(v=0; v<G->V; v++)
        printf("vertice %d : %d/%d\n", v,pre[v],post[v]);
}

void bfs(Graph G, Edge e, int *time, int *pre, int *st, int *dist){
    int v;
    Q q= Qinit();
    Qput(q,e);
    dist[e.v]=-1;

    while(!Qempty(q)){
        if(pre[(e=Qget(q)).w] == -1){
            pre[e.w] = (*time)++;
            st[e.w] = e.v;
            dist[e.w] = dist[e.v]+1;
            for(v=0; v<G->V; v++)
                if(G->madj[e.w][v] > 0)
                    if(pre[v] == -1)
                        Qput(q, EDGEcreate(e.w, v,-1));
        }
    }
}

void GRAPHbfs(Graph G, int id){
    int v, time=0, *pre, *st, *dist;
    pre=malloc(G->V * sizeof(int));
    st=malloc(G->V * sizeof(int));
    dist=malloc(G->V * sizeof(int));

    for(v=0; v<G->V; v++){
        pre[v] = -1;
        st[v] = -1;
        dist[v] = -1;
    }

    bfs(G, EDGEcreate(id,id,-1), &time, pre,st,dist);

    printf("BFS tree:\n");
    for(v=0; v<G->V; v++)
        if(st[v] != -1)
            printf("Il padre di %d è %d e la sua distanza da %d è %d\n", v, st[v], id, dist[v]);
}