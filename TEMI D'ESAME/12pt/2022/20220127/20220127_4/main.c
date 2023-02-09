#include <stdio.h>
#include "BST.h"
int main() {
    FILE *fin;
    fin=fopen("input.txt","r");
    if(fin==NULL) exit(-1);

    BST t=BSTinit();
    int val;

    while(fscanf(fin,"%d", &val)!=EOF)
        BSTinsert(t,val);

    if(f(t)) printf("E' un BST\n");
    else printf("Non è un BST\n");

    return 0;
}
