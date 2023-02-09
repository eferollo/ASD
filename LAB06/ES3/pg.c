#include <stdio.h>
#include <stdlib.h>

#include "pg.h"

int pg_read(FILE *fp, pg_t *pgp){
    if(fscanf(fp,"%s %s %s", pgp->cod, pgp->nome, pgp->classe)==EOF)
        return 0;
    stat_read(fp,&pgp->b_stat);
    pgp->eq_stat = pgp->b_stat;
    pgp->equip=equipArray_init();
    return 1;
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    if(pgp==NULL)
        return;
    fprintf(fp,"%s %s %s\n \tSTAT BASE: ", pgp->cod, pgp->nome, pgp->classe);
    stat_print(fp,&pgp->b_stat, 0);
    if(equipArray_inUse(pgp->equip)>0){
        fprintf(fp," \tSTAT EQ: ");
        stat_print(fp,&pgp->eq_stat, 1);
        if(pgp->equip!=NULL)
            equipArray_print(fp,pgp->equip,invArray);
    }
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    int equip_i, opt,index;
    inv_t *inv;
    stat_t stat_eq;
    index=equipArray_update(pgp->equip, invArray, &opt);
    if(opt==1 || opt==0){
        equip_i= equipArray_getEquipByIndex(pgp->equip,index);
        inv= invArray_getByIndex(invArray, equip_i);
        stat_eq= inv_getStat(inv);
        pgp->eq_stat= statOp(pgp->eq_stat,stat_eq,opt);
    }
}
void pg_clean(pg_t *pgp){
    if(pgp->equip!=NULL)
        equipArray_free(pgp->equip);
}