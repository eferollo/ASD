#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Tree.h"
int main() {
    T t=TREEInit();
    FILE *fp;
    fp= fopen("input.txt","r");
    if(fp==NULL) exit(-1);

    int n;
    int vett[]={10,1,-2,5,6,INT_MIN,1,5,-9,4,3,1,7,5,12};
    insertTREE(t,vett,15);
    n = f(t);
    printf("Longest path: %d\n", n);
    fclose(fp);
    return 0;
}
