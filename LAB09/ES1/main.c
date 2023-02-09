#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#define filename "grafo3.txt"

int main() {
    FILE *fin;
    fin= fopen(filename,"r");
    if(fin==NULL) exit(printf("Error while opening file"));

    int isDag=1, *ts, i;
    Graph G= GRAPHload(fin);
    GRAPHstore(G);
    ts=DAGrts(G,&isDag);

    if(!isDag){
        printf("Il grafo letto da file non è un DAG\n\n");
        printf("Creazione DAG:\n");
        createDAG(G);
        printf("\nDAG ottenuto:\n");
        GRAPHstore(G);
    }else printf("Il grafo letto da file è un DAG\n");

    printf("Ordinamento topologico DAG\n");
    int v= GRAPHgetV(G);
    for(i=0; i<v; i++)
        STdisplay(GRAPHgetST(G), ts[i]);

    printf("\n\nDistanze massime da ogni nodo\n");
    GRAPHmaxDist(G,ts);

    free(ts);
    GRAPHfree(G);
    return 0;
}
