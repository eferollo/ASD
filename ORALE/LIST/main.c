#include <stdio.h>
#include <stdlib.h>
#include "LIST.h"

int main() {
    int i;
    int v1[]={1,2,2,3,4,5};
    int v2[]={3,4,4,12,18,22};
    LIST l1=LISTinit();
    LIST l2=LISTinit();
    for(i=0; i<6; i++){
        LISTinsert(l1,v1[i]);
        LISTinsert(l2,v2[i]);
    }

    LIST l3=merge(l1,l2);
    //listReverse(l3);
    //removeMinMax(l3,3,11);
    //removeEven(l3);

    int v3[]={1,4,10};
    LIST l4=LISTinit();
    for(i=0; i<3; i++) LISTinsert(l4,v3[i]);
    //addMissing(l4);
    //LIST *lists=listadiliste();
    int v4[]={3,4,1,2};
    int v5[]={2,4};
    LIST l5=LISTinit();
    LIST l6=LISTinit();
    for(i=0; i<4; i++) LISTinsertCoda(l5,v4[i]);
    for(i=0; i<2; i++) LISTinsertCoda(l6,v5[i]);
    intersection(l5,l6);
    return 0;
}
