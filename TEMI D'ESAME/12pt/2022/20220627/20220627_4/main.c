#include <stdio.h>
#include "nTREE.h"

int main() {
    nTREE t=init();
    FILE *fp;
    fp= fopen("input.txt","r");
    if(fp==NULL) exit(-1);
    char *str=malloc(sizeof(char));
    while(fscanf(fp, "%s", str)!=EOF){
        insertTREE(t,str);
    }
    printf("Res: %d\n", countIf(t));
    return 0;
}
