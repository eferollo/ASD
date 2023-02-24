#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
int main() {
    FILE *fp= fopen("grafo.txt","r");
    if(fp==NULL) exit(-1);

    Graph G=GRAPHload(fp);
    findCycles(G,5);
    return 0;
}
