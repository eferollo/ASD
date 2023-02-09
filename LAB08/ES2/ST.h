#ifndef ST_H_DEFINED
#define ST_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

typedef struct symboltable *ST;

ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
void STinsert(ST st, Item val);
int STsearch(ST st, KEY k);
void STdisplay(ST st, int index);
void STsort(ST st);

#endif
