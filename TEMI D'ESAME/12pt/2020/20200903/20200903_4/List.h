#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct list *list_t;

list_t LISTinit();
void LISTinsert(list_t L, int posizione, int key);
#endif
