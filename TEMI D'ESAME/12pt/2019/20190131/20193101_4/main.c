#include <stdio.h>
#include <stdlib.h>
#include "LIST.h"
int main() {
    list L1=LISTinit();
    list L2=LISTinit();

    FILE *fin,*fp;
    fin= fopen("input1.txt", "r");
    if(fin==NULL) exit(-1);
    fp= fopen("input2.txt","r");
    if(fp==NULL) exit(-2);
    int val;
    while(fscanf(fin,"%d", &val)!=EOF)
        insertList(L1,val);
    fclose(fin);
    while(fscanf(fp,"%d", &val)!=EOF)
        insertList(L2,val);
    fclose(fp);

    splice(L1,L2,1,2);
    return 0;
}