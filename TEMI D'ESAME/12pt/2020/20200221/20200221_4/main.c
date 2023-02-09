#include <stdio.h>
#include <stdlib.h>
#include "LIST.h"
int main() {
    FILE *fin;
    fin=fopen("input.txt","r");
    if(fin==NULL) exit(-1);

    list L=LISTInit();
    int e;
    while(fscanf(fin,"%d ", &e)!=EOF)
        LISTadd(L,e);

    swap(L,0);

    return 0;
}
