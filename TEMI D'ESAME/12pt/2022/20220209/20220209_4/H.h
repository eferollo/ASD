#ifndef H_H
#define H_H
#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
typedef struct minHeap *H;

H Hinit();
void newHeap(H h, FILE *fp);
void HuffHeapEncode(H h);
char *decode(H h, char *str);

#endif
