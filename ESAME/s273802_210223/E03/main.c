#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct{
    int val;
    int time;
} prods_t;

int check(int *sol, prods_t *prods, int dim, int T, int V, int *bestval){
    int t_tot=0, val_tot=0, i;
    for(i=0; i<dim; i++){
        val_tot+=prods[sol[i]].val;
        t_tot+=prods[sol[i]].time;
    }
    int res=abs(V-val_tot);
    if(t_tot > T)
        return 0;
    else{
        if(res<(*bestval))
            *bestval=res;
    }
    return 1;
}

void comb_ripet(int pos, prods_t *prods, int *val, int *sol, int n , int k, int start, int T, int V, int *bestval, int *best_sol, int max){
    int i;
    if(pos==k){
        if(check(sol,prods, k, T,V, &(*bestval))){
            for(i=0; i<k; i++)
                best_sol[i]=sol[i];
        }
        return;
    }
    for(i=start; i<n; i++){
        sol[pos]=val[i];
        comb_ripet(pos+1, prods,val,sol,n,k,start,T,V,bestval,best_sol,max);
        start++;
    }
}

void wrapper(int P, int T, int V, prods_t *prods){
    int i,bestval=INT_MAX, max=10;
    int *val=malloc(P*sizeof(int));
    int *sol=malloc(max*sizeof(int));
    int *bestsol=malloc(max*sizeof(int));

    for(i=0; i<P; i++) val[i]=i;
    for(i=0; i<max; i++){
        bestsol[i]=-1;
        sol[i]=-1;
    }

    for(i=1; i<max; i++){
        comb_ripet(0,prods,val,sol,P,i,0,T,V,&bestval,bestsol, max);
    }

    //output leggibile
    int *occ_prods=calloc(P,sizeof(int));
    for(i=0; i<max; i++)
        if(bestsol[i]!=-1)
            occ_prods[bestsol[i]]++;
    for(i=0; i<P; i++)
        if(occ_prods[i]!=0)
            printf("Pezzo %d quantità: %d\n", i, occ_prods[i]);

}

int main() {
    prods_t *prods;
    FILE *fp;
    fp=fopen("input.txt","r");
    if(fp==NULL) exit(-1);
    int i,n;
    fscanf(fp,"%d", &n);
    prods=malloc(n*sizeof(*prods));
    for(i=0; i<n; i++)
        fscanf(fp,"%d %d", &prods[i].val, &prods[i].time);

    wrapper(n,50,200, prods);
    return 0;
}
