#ifndef ST_H
#define ST_H

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

typedef struct symboltable *ST;

ST STinit(int maxN);
void STfree(ST st);
void STinsert(ST st, Item val);
int STsearch(ST st, Key k);
void STdisplay(ST st, int index);
#endif
