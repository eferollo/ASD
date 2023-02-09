#ifndef DAILYQUOTATION_H
#define DAILYQUOTATION_H
#include <stdio.h>
#include <stdlib.h>

#include "DateTime.h"

typedef struct{
    Date date;
    Time time;
    float n_qi;
    int d_qi;
}Quotation;

Date Q_GETdate(Quotation q);
void Q_print(Quotation q);
float Q_GETval(Quotation q);

#endif
