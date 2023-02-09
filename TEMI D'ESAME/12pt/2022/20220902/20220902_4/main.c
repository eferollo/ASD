#include <stdio.h>
#include "nTREE.h"
int main() {
    nTREE t=init();
    FILE *fp;
    fp= fopen("input.txt","r");
    if(fp==NULL) exit(-1);
    int c;
    while(fscanf(fp, "%d", &c)!=EOF){
        insertTREE(t,c);
    }
    int n1=0,n2=0,n3=0;
    countIf(t,&n1,&n2,&n3);
    printf("Nodi:\n"
           "\tGrado 1: %d\n"
           "\tGrado 2: %d\n"
           "\tGrado 3: %d\n",n1,n2,n3);
    return 0;
}
