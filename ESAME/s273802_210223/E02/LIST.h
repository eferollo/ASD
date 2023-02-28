#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct list *LIST;
LIST LISTinit();
void LISTinsert(LIST l, int key);
void f(LIST l, int a, int b);
#endif
