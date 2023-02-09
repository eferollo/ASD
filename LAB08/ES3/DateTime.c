#include "DateTime.h"

Date newDate(char *date){
    Date d;
    sscanf(date,"%d/%d/%d", &d.aaaa, &d.mm, &d.gg);
    return d;
}

Time newTime(char *time){
    Time t;
    sscanf(time,"%d:%d", &t.hh, &t.mm);
    return t;
}

int DATEcmp(Date d1, Date d2){
    if(d1.aaaa != d2.aaaa)
        return (d1.aaaa-d2.aaaa);
    if(d1.mm != d2.mm)
        return (d1.mm-d2.mm);
    if(d1.gg != d2.gg)
        return (d1.gg-d2.gg);
    return 0;
}

void printDATE(Date d){
    printf("%d/%02d/%02d ", d.aaaa,d.mm,d.gg);
}
