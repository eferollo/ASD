#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct list *LIST;

LIST LISTIinit();
void LISTInsert(LIST l, int key);
void f(LIST l, int *v, int n);

#endif
