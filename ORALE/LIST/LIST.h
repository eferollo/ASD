#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct list *LIST;

LIST LISTinit();
void LISTinsert(LIST l, int val);
LIST merge(LIST l1, LIST l2);
void listReverse(LIST l);
void removeMinMax(LIST l, int min, int max);
void removeEven(LIST l);
void addMissing(LIST l);
LIST *listadiliste();
void LISTinsertCoda(LIST l, int val);
void intersection(LIST l1, LIST l2);
#endif
