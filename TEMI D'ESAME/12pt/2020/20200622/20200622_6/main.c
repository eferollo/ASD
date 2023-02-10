#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int costo,valore,tipo,qta;
}item_t;

int check_t(item_t *v, int *sol, int k){
    int i,cnt=0;
    for(i=1; i<k; i++)
        if(v[sol[i]].tipo == v[sol[i-1]].tipo)
            cnt++;
    if(cnt==k-1)
        return 1;
    return 0;
}

int solve_r(item_t *v, int n, int k, int *sol, int pos, int tot_c, int tot_v, int *val, int start, int *set, int *stop){
    int i;
    if(pos==k){
        if(check_t(v,sol,k))
            *stop=1;
        return 0;
    }
    for(i=start; i<n; i++){
        if(!*stop){
            if((v[i].costo + *val) <= tot_c){
                *val=*val+v[i].costo;
                sol[pos]=set[i];
                solve_r(v,n,k,sol,pos+1,tot_c, tot_v,val,i+1,set,stop);
                *val=*val-v[i].costo;
            }
        }else
            return 0;
    }
}

void wrapper(item_t *v, int n){
    int *sol=malloc(sizeof(int));
    int i,j,stop=0,val;
    int *set=malloc(n * sizeof(int));
    for(i=0; i<n; i++) set[i]=i;

    for(i=2; i<n && stop==0; i++){
        val=0;
        sol= realloc(sol,i*sizeof(int));
        solve_r(v,n,i,sol,0,30,0,&val,0,set,&stop);
    }

    printf("Insieme soluzione:\n");
    for(j=0; j<i-1; j++)
        printf("%d %d %d %d\n", v[sol[j]].costo,v[sol[j]].valore, v[sol[j]].tipo, v[sol[j]].qta);
    free(sol);
    free(set);
}
int main() {
    FILE *fin;
    fin= fopen("input.txt","r");
    if(fin==NULL) exit(-1);

    int n,i;
    fscanf(fin,"%d",&n);
    item_t *v=malloc(n*sizeof(*v));
    for(i=0; i<n; i++)
        fscanf(fin,"%d %d %d %d", &v[i].costo, &v[i].valore, &v[i].tipo, &v[i].qta);

    wrapper(v,n);
    free(v);
    return 0;
}
