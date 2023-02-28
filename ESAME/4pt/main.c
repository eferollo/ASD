#include <stdio.h>
#include <stdlib.h>
#include "LIST.h"
int main() {
    FILE *fin;
    fin= fopen("input.txt","r");
    if(fin==NULL) exit(-1);

    LIST l=LISTinit();
    int key;
    while(fscanf(fin,"%d\n", &key)==1)
        LISTinsert(l,key);
    f(l,1,7);
    return 0;
}
