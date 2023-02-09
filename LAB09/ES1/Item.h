#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 31

typedef struct{
    char node[MAX];
}Item;

typedef char *Key;

Item ITEMload(char str[]);
void ITEMstore(Item val);
Item ITEMsetvoid();
Key KEYget(Item *val);
int KEYcmp(Key k1, Key k2);

#endif
