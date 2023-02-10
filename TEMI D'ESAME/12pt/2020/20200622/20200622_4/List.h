#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>
typedef struct list *list_t;

list_t LISTInit();
list_t prodCart(int *v1, int d1, int *v2, int d2);
void print(list_t list);
#endif
