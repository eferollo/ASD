#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct edge{
    int v;
    int w;
    int wt;
}Edge;

void print(Edge *e, int V){
    int i;
    for(i=0; i<V; i++)
        printf("(%d %d) ", e[i].v, e[i].w);
}

int isST(int *mark, Edge *sol, int V){
    int i;
    mark=calloc(V,sizeof (int));
    for(i=0; i<V; i++){
        mark[sol[i].w]=1;
        mark[sol[i].v]=1;
    }
    for(i=0; i<V; i++)
        if(mark[i]==0)
            return 0;
    return 1;
}

void powerset_r(int pos, Edge *edges, Edge *sol, Edge *bestsol, int E, int V, int start, int *mark, int *bw){
    int i;
    if(pos==V){
        int weight=0;
        if(!isST(mark,sol,V))
            return;
        for(i=0; i<V; i++)
            weight+=sol[i].wt;
        if(weight<*bw){
            *bw=weight;
            for(i=0; i<V; i++) bestsol[i]=sol[i];
        }
        print(sol,V);
        printf("MST = %d\n", weight);
        return;
    }
    for(i=start; i<E; i++){
        sol[pos].v=edges[i].v;
        sol[pos].w=edges[i].w;
        sol[pos].wt=edges[i].wt;
        powerset_r(pos+1,edges,sol,bestsol,E,V,i+1,mark,bw);
    }
}

void powerset(Edge *edges, int E, int V){
    Edge *sol=malloc(V*sizeof(*sol));
    int *mark=calloc(V,sizeof(int));
    Edge *bestsol=malloc(V*sizeof(*sol));
    int bw=INT_MAX;
    printf("Alberi ricoprenti\n");
    powerset_r(0,edges,sol,bestsol,E,V,0,mark,&bw);
    printf("\nAlbero ricoprente minimo: MST = %d\n", bw);
    print(bestsol,V);
    free(sol);
    free(bestsol);
    free(mark);
}

int main() {
    Edge *edges;
    FILE *fp;
    fp=fopen("grafo4.txt","r");
    if(fp==NULL) exit(-1);
    int nE, nV,i;
    fscanf(fp,"%d %d", &nV, &nE);
    edges=malloc(nE*sizeof(*edges));
    for(i=0; i<nE; i++)
        fscanf(fp,"%d %d %d", &edges[i].v, &edges[i].w, &edges[i].wt);
    powerset(edges,nE,nV);
    free(edges);
    return 0;
}
