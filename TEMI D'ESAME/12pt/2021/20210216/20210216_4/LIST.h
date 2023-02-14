#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct list *LIST;

LIST LISTinit();
void LISTinsert(LIST l, int key);
LIST *split(LIST l, int *n);

#endif
