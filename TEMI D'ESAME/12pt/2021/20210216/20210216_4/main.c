#include <stdio.h>
#include <stdlib.h>
#include "LIST.h"

int main() {
    FILE *fp;
    fp=fopen("input.txt","r");
    if(fp==NULL) exit(-1);
    int i,len,key,n;

    LIST l=LISTinit();
    fscanf(fp,"%d", &len);

    for(i=0; i<len; i++){
        fscanf(fp,"%d\n", &key);
        LISTinsert(l,key);
    }
    fclose(fp);

    LIST *vett;
    vett=split(l, &n);
    return 0;
}
