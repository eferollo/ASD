#include <stdio.h>
#include <stdlib.h>
#define MAXC 100
#define MAXE 5
#define MAXD 3
#define DD 10
#define DP 20
#define filename "elementi.txt"

typedef struct elem_s{
    int used;
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
    int level_p;
    float val_p;
}diags_t;

typedef struct elems_s{
    elem_t *c_e;
    int n_elem;
}elems_t;

elems_t *readElems();
diags_t *diags_init();
void Free(elems_t *ELEM, diags_t *DIAG);
void greedyP(elems_t *ELEM, diags_t *DIAG);
int findBest(elems_t *ELEM, int acrob, int dir, int change_dir, int level_d, int level_p, int first);
int check_acrob(diag_t d, elems_t *ELEM, int acrob, int i);

int main() {
    elems_t *ELEM=readElems();
    diags_t *DIAG=diags_init();
    greedyP(ELEM,DIAG);
    Free(ELEM,DIAG);
    return 0;
}

int findBest(elems_t *ELEM, int acrob, int dir, int change_dir, int level_d, int level_p, int first){
    int i;
    int best=-1;
    for(i=0; i<ELEM->n_elem; i++){
        if(!ELEM->c_e[i].used && (ELEM->c_e[i].input==dir) && !(first && ELEM->c_e[i].pre)
        && (level_d+ELEM->c_e[i].level <= DD) && (level_p+ELEM->c_e[i].level <= DP)){
            if(acrob==0 || ELEM->c_e[i].type==acrob || (acrob==3 && ELEM->c_e[i].type>0)){
                if(change_dir && ELEM->c_e[i].exit != dir)
                    return i;
                if(best<0 || (ELEM->c_e[i].val/(float)ELEM->c_e[i].level) > (ELEM->c_e[best].val/(float)ELEM->c_e[best].level))
                    best=i;
            }
        }
    }
    if(best>=0)
        ELEM->c_e[best].used=1;
    return best;
}

int check_acrob(diag_t d, elems_t *ELEM, int acrob, int i){
    int index=d.elem[i], back;
    if((acrob==1 || acrob==2) && ELEM->c_e[index].type==acrob)
        return 0;
    else if(acrob==3 && i>0 && ELEM->c_e[index].type!=0){
        back=d.elem[i - 1];
        if(ELEM->c_e[back].type != 0)
            return 0;
    }
    return acrob;
}

void greedyP(elems_t *ELEM, diags_t *DIAG){
    int i, j, level=0, acrob=0, acrob_p, dir=1, ch_elem, flag=1, last, bonus=1;

    for(i=0; i<MAXD; i++){
        for(int x=0; x<ELEM->n_elem; x++) ELEM->c_e[x].used=0;
        acrob++;
        for(j=0; j<MAXE; j++){
            ch_elem= findBest(ELEM,acrob,dir,0,level, level+DIAG->level_p, j==0);
            if(acrob && ch_elem<0)
                ch_elem= findBest(ELEM,0, dir, 1, level, level+DIAG->level_p, j==0);
            if(ch_elem==-1) break;
            dir=ELEM->c_e[ch_elem].exit;
            level += ELEM->c_e[ch_elem].level;
            DIAG->c_d[i].level += ELEM->c_e[ch_elem].level;
            DIAG->c_d[i].elem[j]=ch_elem;
            DIAG->c_d[i].n_elem++;
            DIAG->c_d[i].val += ELEM->c_e[ch_elem].val;
            acrob_p= check_acrob(DIAG->c_d[i],ELEM, acrob, j);
        }
        if(DIAG->c_d[i].n_elem>0 && acrob_p==0){
            DIAG->level_p+=level;
            DIAG->val_p+=DIAG->c_d[i].val;
            level=0;
            dir=1;
        }else{
            flag=0;
            break;
        }
    }

    if(flag){
        for (i=0; i<MAXD; i++) {
            last=DIAG->c_d[i].n_elem-1;
            if (ELEM->c_e[last].type > 0 && ELEM->c_e[DIAG->c_d[i].elem[last]].level >= 8) {
                if ((DIAG->c_d[bonus].val < DIAG->c_d[i].val) || bonus == -1)
                    bonus=i;
            }
        }
        if(bonus>-1) DIAG->val_p += 0.5 * DIAG->c_d[bonus].val;
        printf("--- Test Case #0 ---\nDD = %d DP = %d\nTOT = %.3f\n", DD,DP,DIAG->val_p);
        for(i=0;i<MAXD;i++){
            printf("DIAG #%d > %.3f %s\n", i+1, DIAG->c_d[i].val, ((bonus==i) ? "* 1.5 (BONUS)" : ""));
            for(j=0;j<DIAG->c_d[i].n_elem;j++)
                printf("%s \n", ELEM->c_e[DIAG->c_d[i].elem[j]].name);
        }
    }else
        printf("No solution found\n");
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
    DIAG->c_d=calloc(3,sizeof(diag_t));
    DIAG->level_p=0;
    DIAG->val_p=0.0;
    return DIAG;
}

void Free(elems_t *ELEM, diags_t *DIAG){
    free(ELEM->c_e);
    free(ELEM);
    free(DIAG->c_d);
    free(DIAG);
}

