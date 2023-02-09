#ifndef DAILYQUOTATIONSET_H
#define DAILYQUOTATIONSET_H
#include <stdio.h>
#include <stdlib.h>
#include "DateTime.h"
#include "DailyQuotation.h"

typedef struct quotations_s *Quotations;

Quotations BSTinit();
Quotation Q_setNull();
void BSTfree(Quotations bst);
void BSTinsert(Quotations bst, Date d, Time t, float val, int nq);
void BSTgetMinMax(Quotations bst, float *min, float *max);
Quotation BSTquotationSaearh(Quotations bst, Date d);
void BSTquotationMinMaxDate(Quotations bst, Date d1, Date d2, float *min, float *max);
void BSTprint(Quotations bst);
int BSTempty(Quotations bst);
void BSTbalance(Quotations bst, int s);

#endif
