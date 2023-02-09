#include <stdio.h>
#include <stdlib.h>
#define MAXC 100
#define MAXE 5
#define MAXD 3
#define DD 10
#define DP 20
#define filename "elementi.txt"

typedef struct elem_s{
    char name[MAXC];
    int type;
    int input;
    int exit;
    int pre;
    int final;
    int level;
    float val;
}elem_t;

typedef struct diag_s{
    int elem[MAXE];
    int n_elem;
    int level;
    float val;
}diag_t;

typedef struct diags_s{
    diag_t *c_d;
    int n_diag, max_diag;
}diags_t;

typedef struct elems_s{
    elem_t *c_e;
    int n_elem;
}elems_t;

void findDiagAlg(elems_t *ELEM, diags_t *DIAG);
elems_t *readElems();
diags_t *diags_init();
void disp_sempl(int pos, elems_t *ELEM, diags_t *DIAG, int *diagonal, int level, int dir, int final, int type);
int check(elems_t *ELEM, diags_t *DIAG, int *sol, int nd, float *bval, int *c_bonus);
void comb_ripet(elems_t *ELEM, diags_t *DIAG, int *sol, int *bestsol, float *bestval, int *nd, int *bonus, int pos, int level, int index);
void Free(elems_t *ELEM, diags_t *DIAG);

int main() {
    elems_t *ELEM=readElems();
    diags_t *DIAG=diags_init();
    findDiagAlg(ELEM,DIAG);
    Free(ELEM,DIAG);
    return 0;
}

elems_t *readElems(){
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp==NULL) exit(-1);
    int i;
    elems_t *ELEM=(elems_t *)malloc(1*sizeof(elems_t));
    fscanf(fp,"%d", &ELEM->n_elem);
    ELEM->c_e=(elem_t *)malloc(ELEM->n_elem*sizeof(elem_t));
    for(i=0; i<ELEM->n_elem; i++)
        fscanf(fp,"%s%d%d%d%d%d%f%d", ELEM->c_e[i].name, &ELEM->c_e[i].type, &ELEM->c_e[i].input, &ELEM->c_e[i].exit,
               &ELEM->c_e[i].pre, &ELEM->c_e[i].final, &ELEM->c_e[i].val, &ELEM->c_e[i].level);
    fclose(fp);
    return ELEM;
}

diags_t *diags_init(){
    diags_t *DIAG=(diags_t *)malloc(1*sizeof(diags_t));
    DIAG->c_d=calloc(1,sizeof(diag_t));
    DIAG->n_diag=0;
    DIAG->max_diag=1;
    return DIAG;
}

void disp_sempl(int pos, elems_t *ELEM, diags_t *DIAG, int *diagonal, int level, int dir, int final, int type){
    int i;
    if(pos >0 && type>0){
        if(DIAG->n_diag==DIAG->max_diag){
            DIAG->max_diag++;
            DIAG->c_d=realloc(DIAG->c_d, DIAG->max_diag*sizeof (diag_t));
        }
        DIAG->c_d[DIAG->n_diag].level=level;
        DIAG->c_d[DIAG->n_diag].n_elem=pos;
        DIAG->c_d[DIAG->n_diag].val=0.0;
        for(i=0;i<pos;i++){
            DIAG->c_d[DIAG->n_diag].val += ELEM->c_e[diagonal[i]].val;
            DIAG->c_d[DIAG->n_diag].elem[i]=diagonal[i];
        }
        DIAG->n_diag++;
    }
    if(pos>=MAXE || final)
        return;
    for(i=0; i<ELEM->n_elem; i++){
        if(level+ELEM->c_e[i].level>DD) continue;
        if(dir != ELEM->c_e[i].input) continue;
        if(pos==0 && ELEM->c_e[i].pre) continue;
        diagonal[pos]=i;
        disp_sempl(pos+1,ELEM,DIAG,diagonal,level+ELEM->c_e[i].level, ELEM->c_e[i].exit, ELEM->c_e[i].final, ELEM->c_e[i].type);
    }
}

int check(elems_t *ELEM, diags_t *DIAG, int *sol, int nd, float *bval, int *c_bonus){
    int i,seq,j, forward, back,bonus=-1;
    for(i=0; i<nd; i++){
        seq=0;
        for(j=0; j<DIAG->c_d[sol[i]].n_elem; j++){
            if(ELEM->c_e[DIAG->c_d[sol[i]].elem[j]].type == 2){
                forward=1;
                seq++;
            }else if(ELEM->c_e[DIAG->c_d[sol[i]].elem[j]].type == 1){
                back=1;
                seq++;
            }else
                seq=0;
            if(j==(DIAG->c_d[sol[i]].n_elem-1) && ELEM->c_e[DIAG->c_d[sol[i]].elem[j]].level>=8)
                if(bonus == -1 || (DIAG->c_d[sol[bonus]].val<DIAG->c_d[sol[i]].val))
                    bonus = i;
        }
    }
    if(forward && back && seq>=2){
        for(i=0; i<nd; i++)
            (*bval) += DIAG->c_d[sol[i]].val * ((i==bonus) ? 1.50 : 1.00);
        *c_bonus=bonus;
        return 1;
    }
    return 0;
}

void comb_ripet(elems_t *ELEM, diags_t *DIAG, int *sol, int *bestsol, float *bestval, int *nd, int *bonus, int pos, int level, int index){
    int i, bonus0;
    float val=0.0;
    if(pos==MAXD){
        if(check(ELEM,DIAG,sol,pos,&val,&bonus0))
            if(val > *bestval){
                *nd=pos;
                *bestval=val;
                *bonus=bonus0;
                for(i=0;i<pos; i++) bestsol[i]=sol[i];
            }
        return;
    }
    for(i=index; i<DIAG->max_diag; i++){
        if(level+DIAG->c_d[i].level>DP) continue;
        sol[pos]=i;
        comb_ripet(ELEM,DIAG,sol,bestsol,bestval,nd, bonus,pos+1, level+DIAG->c_d[i].level, i);
    }
}

void findDiagAlg(elems_t *ELEM, diags_t *DIAG){
    int *diagonal=calloc(MAXE, sizeof(int));
    disp_sempl(0,ELEM,DIAG,diagonal,0,1,0,0);
    int bonus, nd=0, sol[MAXD], bestsol[MAXD],i,j;
    float bestval= -1.0;
    comb_ripet(ELEM,DIAG,sol,bestsol,&bestval,&nd, &bonus,0,0,0);
    printf("--- Test Case #0 ---\nDD = %d DP = %d\nTOT = %.3f\n", DD,DP,bestval);
    for(i=0;i<nd;i++){
        printf("DIAG #%d > %.3f %s\n", i+1, DIAG->c_d[bestsol[i]].val, ((bonus==i) ? "* 1.5 (BONUS)" : ""));
        for(j=0;j<DIAG->c_d[bestsol[i]].n_elem;j++)
            printf("%s \n", ELEM->c_e[DIAG->c_d[bestsol[i]].elem[j]].name);
    }
    printf("\nSono possibili %d diagonali\n", DIAG->n_diag);
    free(diagonal);
}

void Free(elems_t *ELEM, diags_t *DIAG){
    free(ELEM->c_e);
    free(ELEM);
    free(DIAG->c_d);
    free(DIAG);
}

