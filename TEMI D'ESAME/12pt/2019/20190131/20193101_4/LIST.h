#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct list *list;

list LISTinit();
void insertList(list L, int key);
void splice(list L1, list L2, int start, int num);
#endif
