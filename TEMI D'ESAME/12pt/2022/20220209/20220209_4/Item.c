#include "Item.h"

Item ITEMload(char c, int f){
    Item x;
    x.c=c;
    x.freq=f;
    return x;
}

Item ITEMsetvoid(){
    Item x;
    x.c='!';
    x.freq=-1;
    return x;
}

void ITEMstore(Item val){
    printf("%c: %d", val.c, val.freq);
}

Key KEYget(Item val){
    return val.freq;
}

int KEYcmp(Key k1, Key k2){
    return (k1>k2);
}