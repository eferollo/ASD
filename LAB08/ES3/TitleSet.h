#ifndef TITLESET_H
#define TITLESET_H
#include <stdio.h>
#include <stdlib.h>

#include "Title.h"

typedef struct titles_s *Titles;

Titles titles_init();
void TitlesListIns(Titles titles, Title t);
Title TitlesListSearch(Titles t, char *name);
int TitlesListEmpty(Titles titles);
void printTitles(Titles titles);
void freeTitlesLIST(Titles titles);

#endif
