#ifndef TITLE_H
#define TITLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256
#include "DailyQuotationSet.h"

typedef struct title_s *Title;
typedef char *Key;

int TITLEcmp(Key k1, Key k2);
Title TitleNEW(char *name);
Key TITLEgetKey(Title t);
void TITLEInsTrans(Title t, Date date, Time time, float val, int nq);
Quotation TITLEgetQ_byDate(Title t, Date d);
float TITLEgetMin(Title t);
float TITLEgetMax(Title t);
void TITLEgetMinMaxDate(Title t, Date d1, Date d2, float *min, float *max);
void TITLEtreeBalance(Title t, int s);
void TITLEprint(Title t);
void freeTITLE(Title t);

#endif
