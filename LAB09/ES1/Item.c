#include "Item.h"

Item ITEMload(char str[]){
    Item x;
    strcpy(x.node, str);
    return x;
}

Item ITEMsetvoid(){
    Item x;
    strcpy(x.node,"");;
    return x;
}

Key KEYget(Item *val){
    return val->node;
}

int KEYcmp(Key k1, Key k2){
    return strcmp(k1,k2);
}

void ITEMstore(Item val){
    printf("%s ", val.node);
}
