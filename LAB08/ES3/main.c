#include <stdio.h>
#include <stdlib.h>
#define MAXT 21
#include "TitleSet.h"
#include "DailyQuotationSet.h"
#include "DateTime.h"

void menu();
void readFile(char *filename, Titles titles);

int main() {
    Titles titles=NULL;
    Title t;
    Quotation q;
    int loop=1, opt, s;
    float min=-1.0,max=-1.0;
    char filename[MAX], title[MAXT], date1[MAX], date2[MAX];
    while(loop){
        menu();
        scanf("%d", &opt);
        switch(opt){
            case 0:
                loop=0;
                if(!TitlesListEmpty(titles))
                    freeTitlesLIST(titles);
                break;
            case 1:
                printf("Inserisci nome del file: ");
                scanf("%s", filename);
                titles=titles_init();
                readFile(filename, titles);
                break;
            case 2:
                printTitles(titles);
                break;
            case 3:
                printf("Inserisci il titolo: ");
                scanf("%s", title);
                if(TitlesListSearch(titles, title) == NULL)
                    printf("\nNessun titolo trovato\n");
                else TITLEprint(TitlesListSearch(titles,title));
                break;
            case 4:
                printf("Inserisci il titolo: ");
                scanf("%s", title);
                t=TitlesListSearch(titles, title);
                if(t != NULL){
                    printf("Inserisci una data (aaaa/mm/gg): ");
                    scanf("%s", date1);
                    q= TITLEgetQ_byDate(t, newDate(date1));
                    Q_print(q);
                }else printf("\nNessun titolo trovato\n");
                break;
            case 5:
                printf("Inserisci il titolo: ");
                scanf("%s", title);
                t=TitlesListSearch(titles, title);
                if(t!=NULL){
                    printf("Inserisci la prima data (aaaa/mm/gg):");
                    scanf("%s",date1);
                    printf("Inserisci la seconda data (aaaa/mm/gg):");
                    scanf("%s",date2);
                    TITLEgetMinMaxDate(t, newDate(date1), newDate(date2), &min, &max);
                    printf("\nMIN: %.2f  MAX: %.2f", min, max);
                } else printf("\nNessun titolo trovato\n");
                break;
            case 6:
                printf("Inserisci il titolo: ");
                scanf("%s", title);
                t=TitlesListSearch(titles, title);
                if(t!=NULL)
                    printf("\nMIN: %.2f  MAX: %.2f", TITLEgetMin(t), TITLEgetMax(t));
                else printf("\nNessun titolo trovato\n");
                break;
            case 7:
                printf("Inserisci il titolo: ");
                scanf("%s", title);
                t=TitlesListSearch(titles, title);
                if(t!=NULL){
                    printf("Inserisci una soglia: ");
                    scanf("%d", &s);
                    TITLEtreeBalance(t,s);
                }else printf("\nNessun titolo trovato\n");
                break;
            default:
                printf("Scelta non valida\n");
                break;
        }
    }
    return 0;
}

void menu(){
    printf("\nSelezionare una scelta:\n"
           "\t1.Importa da file\n"
           "\t2.Stampa titoli\n"
           "\t3.Ricerca titolo\n"
           "\t4.Stampa Quotazione di un titolo\n"
           "\t5.Stampa quotazione min e max in un intervallo di date\n"
           "\t6.Stampa quotazione min e max totale\n"
           "\t7.Bilanciamento BST\n"
           "\t0.EXIT\n"
           "Scelta: ");
}

void readFile(char *filename, Titles titles){
    FILE *fin;
    fin= fopen(filename, "r");
    if(fin==NULL){
        printf("Error while opening file\n");
        return;
    }

    Title title;
    int n,i,j,nq,n_trans;
    char title_name[MAX], date[MAX], time[MAX];
    float val;

    fscanf(fin,"%d", &n);
    for(i=0; i<n; i++){
        fscanf(fin,"%s %d", title_name, &nq);
        title= TitlesListSearch(titles,title_name);
        if(title == NULL){
            title=TitleNEW(title_name);
            TitlesListIns(titles,title);
        }
        for(j=0; j<nq; j++){
            fscanf(fin,"%s%s%f%d", date, time, &val, &n_trans);
            TITLEInsTrans(title, newDate(date), newTime(time), val, n_trans);
        }
    }
    fclose(fin);
}