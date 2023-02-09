#ifndef ITEM_H
#define ITEM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item{
    char c;
    int freq;
    struct item *l;
    struct item *r;
}Item;

typedef int Key;

Item ITEMsetvoid();
Item ITEMload(char c, int f);
void ITEMstore(Item val);
Key KEYget(Item val);
int KEYcmp(Key k1, Key k2);
#endif
