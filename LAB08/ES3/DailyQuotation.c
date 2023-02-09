#include "DailyQuotation.h"

Date Q_GETdate(Quotation q){
    return q.date;
}

float Q_GETval(Quotation q){
    if(q.d_qi != 0)
        return q.n_qi/(float)q.d_qi;
    return -1.0;
}

void Q_print(Quotation q){
    if(q.date.aaaa!=0){
        printDATE(q.date);
        printf("VAL: %.2f\n", Q_GETval(q));
    }else printf("Nessuna quotazione per la data inserita\n");
}

Quotation Q_setNull(){
    Quotation q;
    q.date= newDate("00/00/00");
    q.time= newTime("00:00");
    q.d_qi=0;
    q.n_qi=0.0;
    return q;
}


