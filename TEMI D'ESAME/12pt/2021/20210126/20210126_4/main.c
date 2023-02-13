#include <stdio.h>
#include <stdlib.h>
#include "LIST.h"

int main() {
    LIST l=LISTIinit();
    int k;
    FILE *fp;
    fp=fopen("input.txt","r");
    if(fp==NULL) exit(-1);

    while(fscanf(fp,"%d\n", &k)!=EOF)
        LISTInsert(l,k);
    fclose(fp);
    int v[]={1,2,3};
    f(l,v,3);
    return 0;
}
