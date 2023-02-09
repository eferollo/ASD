#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

static int **MATRIXint(int r, int c, int val);
static link NEW(int v, int wt, link next);
static Edge EDGEcreate(int v, int w, int wt);
static void insertE(Graph G, Edge e);

static link NEW(int v, int wt, link next){
    link x=malloc(sizeof(*x));
    x->v=v;
    x->wt=wt;
    x->next=next;
    return x;
}

static int **MATRIXint(int r, int c, int val){
    int i,j;
    int **t=malloc(r*sizeof (int *));
    for(i=0; i<r; i++) t[i]=malloc(c*sizeof (int));
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
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
    Graph G = malloc(sizeof(*G));
    G->V=V;
    G->E=0;
    G->madj= MATRIXint(V,V,0);
    G->ladj=NULL;
    return G;
}

void GRAPHfree(Graph G){
    int i;
    link t, next;
    for(i=0; i<G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    if(G->ladj!=NULL){
        for(i=0;i<G->V; i++)
            for(t=G->ladj[i]; t!=NULL; t=next){
                next=t->next;
                free(t);
            }
        free(G->ladj);
    }
    free(G);
}

void GRAPHinsertE(Graph G, int ind1, int ind2, int wt){
    insertE(G, EDGEcreate(ind1,ind2,wt));
}

static void insertE(Graph G, Edge e){
    int v=e.v, w=e.w, wt=e.wt;
    if(G->madj[v][w]==0) G->E++;
    G->madj[v][w]=wt;
    G->madj[w][v]=wt;
}

Graph GRAPHload(FILE *fin, ST st){
    int wt, ind1, ind2;
    Item x;
    char elab1[MAX], elab2[MAX], rete1[MAX], rete2[MAX];
    Graph G;

    while(fscanf(fin,"%s %s %s %s %d", elab1,rete1,elab2,rete2,&wt) != EOF){
        x= ITEMload(elab1,rete1);
        ind1= STsearch(st, KEYget(&x));
        if(ind1==-1)
            STinsert(st,x);
        x=ITEMload(elab2,rete2);
        ind2= STsearch(st, KEYget(&x));
        if(ind2==-1)
            STinsert(st,x);
    }
    rewind(fin);
    G= GRAPHinit(STcount(st));

    if(G==NULL) return NULL;
    while(fscanf(fin,"%s %s %s %s %d", elab1,rete1,elab2,rete2,&wt) != EOF){
        x= ITEMload(elab1,rete1);
        ind1= STsearch(st, KEYget(&x));
        x=ITEMload(elab2,rete2);
        ind2= STsearch(st, KEYget(&x));
        if(ind1 != ind2 && ind1 >= 0 && ind2 >= 0)
            GRAPHinsertE(G,ind1,ind2,wt);
    }
    fclose(fin);
    return G;
}

void GRAPHstore(Graph G, ST st){
    int i,j;
    STsort(st);
    for(i=0; i<G->V; i++){
        STdisplay(st,i);
        for(j=0;j<G->V;j++){
            if(G->madj[i][j]){
                printf("\t");
                STdisplay(st,j);
            }
        }
        printf("\n");
    }
}

int GRAPHlist(Graph G){
    int v,w;
    if(G->ladj!=NULL)
        return 0;
    if(G->madj==NULL)
        return -1;
    G->ladj = calloc(G->V,sizeof(link));

    for(v=0; v<G->V; v++)
        for(w=0; w<G->V; w++)
            if(G->madj[v][w]){
                G->ladj[v]= NEW(w, G->madj[v][w], G->ladj[v]);
                G->ladj[w]= NEW(v, G->madj[v][w], G->ladj[w]);
            }
    return 0;
}

int GRAPHcheck(Graph G, int a, int b, int c){
    if(G==NULL) return 0;
    if(G->madj == NULL) return 0;
    if(G->madj[a][b]>0)
        if(G->madj[a][c]>0)
            if(G->madj[b][c]>0)
                return 1;
    return 0;
}