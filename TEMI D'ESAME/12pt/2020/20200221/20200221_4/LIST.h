#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct LIST *list;

list LISTInit();
void LISTadd(list L, int key);

void swap(list L, int k);
#endif
