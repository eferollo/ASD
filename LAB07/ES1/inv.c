#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inv.h"

void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp,"%d %d %d %d %d %d", &statp->hp, &statp->mp, &statp->atk, &statp->def, &statp->mag, &statp->spr);
}

void stat_print(FILE *fp, stat_t *statp, int soglia){
    if(statp==NULL)
        return;
    if(soglia)
        fprintf(fp,"\tHP = %d, MP = %d, ATK = %d, DEF = %d, MAG = %d, SPR = %d\n", statp->hp > 0 ? statp->hp : MIN_STAT,
                statp->mp > 0 ? statp->mp : MIN_STAT, statp->atk > 0 ? statp->atk : MIN_STAT,
                statp->def > 0 ? statp->def : MIN_STAT, statp->mag > 0 ? statp->mag : MIN_STAT,
                statp->spr > 0 ? statp->spr : MIN_STAT);
    else
        fprintf(fp,"\tHP = %d, MP = %d, ATK = %d, DEF = %d, MAG = %d, SPR = %d\n", statp->hp, statp->mp, statp->atk, statp->def, statp->mag, statp->spr);
}
void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp,"%s %s", invp->nome, invp->tipo);
    stat_read(fp,&invp->stat);
}
void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp,"\t%s %s\n", invp->nome, invp->tipo);
    stat_print(fp,&invp->stat,0);
}

stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}

stat_t statOp(stat_t pg_s, stat_t eq_s, int opt){
    if(opt==0){
        pg_s.hp += eq_s.hp;
        pg_s.mp += eq_s.mp;
        pg_s.atk += eq_s.atk;
        pg_s.def += eq_s.def;
        pg_s.mag += eq_s.mag;
        pg_s.spr += eq_s.spr;
    }else{
        pg_s.hp -= eq_s.hp;
        pg_s.mp -= eq_s.mp;
        pg_s.atk -= eq_s.atk;
        pg_s.def -= eq_s.def;
        pg_s.mag -= eq_s.mag;
        pg_s.spr -= eq_s.spr;
    }
    return pg_s;
}