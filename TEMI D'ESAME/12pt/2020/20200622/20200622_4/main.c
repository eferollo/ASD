#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main() {
    int v1[]={1,2,3};
    int v2[]={3,4,5,6};

    list_t list= prodCart(v1,3,v2,4);
    print(list);
    return 0;
}
