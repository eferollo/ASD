#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "ST.h"

int main(int argc, char **argv) {
    Graph G;
    ST st= STinit(1);
    int loop=1, opt, ind1, ind2, ind3;
    char node[MAX];
    FILE *fin;

    if(argc!=2){
        printf("#Usage %s <file>", argv[0]);
        exit(-1);
    }

    fin=fopen(argv[1],"r");
    if(fin==NULL)
        exit(printf("Error while opening file\n"));

    G= GRAPHload(fin,st);
    while(loop){
        printf("MENU:\n"
               "\t1. Visualizzare grafo\n"
               "\t2. Generare lista di adiacenza\n"
               "\t3. Verifica esistenza sottografo completo\n"
               "\t0. EXIT\n"
               "Inserisci opzione: ");
        scanf("%d", &opt);
        switch(opt){
            case 1:
                GRAPHstore(G,st);
                break;
            case 2:
                if(!GRAPHlist(G))
                    printf("Lista delle adiacenze creata\n");
                break;
            case 3:
                printf("Inserire il primo nodo: ");
                KEYscan(node);
                ind1= STsearch(st,node);
                printf("Inserire il secondo nodo: ");
                KEYscan(node);
                ind2= STsearch(st,node);
                printf("Inserire il terzo nodo: ");
                KEYscan(node);
                ind3= STsearch(st,node);
                if(ind1!=-1 && ind2!=-1 && ind3!=-1)
                    printf("Il sottografo%s è completo\n", GRAPHcheck(G,ind1,ind2,ind3) ? "" : " non");
                else
                    printf("Non è un sottografo\n");
                break;
            case 0:
                loop=0;
                break;
            default:
                printf("ERROR option\n");
        }
    }
    STfree(st);
    GRAPHfree(G);
    return 0;
}
