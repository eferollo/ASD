#ifndef DATETIME_H
#define DATETIME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int aaaa, mm, gg;
}Date;

typedef struct{
    int hh, mm;
}Time;

Date newDate(char *date);
Time newTime(char *time);
int DATEcmp(Date d1, Date d2);
void printDATE(Date d);

#endif
