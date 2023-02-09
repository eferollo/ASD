#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 31

typedef struct{
    char id_elab[MAX];
    char id_rete[MAX];
}Item;

typedef char *KEY;

Item ITEMload(char str1[], char str2[]);
void ITEMstore(Item val);
Item ITEMsetvoid();
KEY KEYget(Item *val);
int KEYcmp(KEY k1, KEY k2);
void KEYscan(char node[MAX]);

#endif
