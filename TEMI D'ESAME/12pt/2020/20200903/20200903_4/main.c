#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main() {

    list_t L=LISTinit();
    LISTinsert(L,0,10);
    LISTinsert(L,1,12);
    LISTinsert(L,2,11);
    LISTinsert(L,3,18);
    LISTinsert(L,8,7);
    LISTinsert(L,0,5);
    LISTinsert(L,5,11);
    LISTinsert(L,2,5);
    LISTinsert(L,0,25);

    return 0;
}
