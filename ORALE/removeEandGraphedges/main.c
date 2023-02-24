#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main() {
    FILE *fp=fopen("Grafo.txt","r");
    if(fp==NULL) exit(-1);

    Graph G=GRAPHload(fp);
    //GRAPHdfs(G);
    edges(G);
    removeVertex(G, 1);
    return 0;
}