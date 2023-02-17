#include <stdio.h>
#include "nTREE.h"
int main() {
    nTREE t=init();
    int n1=0,n2=0,n3=0;

    countIf(t,&n1,&n2,&n3);
    printf("Nodi:\n"
           "\tGrado 1: %d\n"
           "\tGrado 2: %d\n"
           "\tGrado 3: %d\n",n1,n2,n3);
    return 0;
}
