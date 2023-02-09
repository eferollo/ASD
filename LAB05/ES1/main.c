#include <stdio.h>
#include <stdlib.h>
#define filename "att.txt"

typedef struct{
    int s,f;
}att;

att *readFile(int *N);
int check_inc(att i, att j);
void printSol(int *best_sol, int n, att *v, int d_max);
void check_sol(int *sol, int *best_sol, att *v, int k, int *d_max);
void powerset(int pos, att *v, int *sol, int k, int *best_sol, int *d_max);
void attSel(int N, att *v);

int main() {
    int n;
    att *v=readFile(&n);
    attSel(n, v);
    free(v);
    return 0;
}

int check_inc(att i, att j){
    if(i.s<j.f && j.s<i.f)
        return 1;
    return 0;
}

void check_sol(int *sol, int *best_sol, att *v, int k, int *d_max){
    int i,j, max=0;
    for(i=0; i<k; i++)
        if(sol[i]==1)
            for(j=i+1; j<k; j++)
                if(sol[j]==1)
                    if(check_inc(v[i],v[j]))
                        return;
    for(i=0; i<k; i++)
        if(sol[i]==1)
            max+=(v[i].f-v[i].s);
    if(max>*d_max){
        *d_max=max;
        for(i=0;i<k;i++)
            best_sol[i]=sol[i];
    }
}

void powerset(int pos, att *v, int *sol, int k, int *best_sol, int *d_max){
    if(pos >= k){
        check_sol(sol, best_sol, v, k, d_max);
        return;
    }
    sol[pos]=0;
    powerset(pos+1,v,sol,k,best_sol,d_max);
    sol[pos]=1;
    powerset(pos+1,v,sol,k,best_sol,d_max);
}

void printSol(int *best_sol, int n, att *v, int d_max){
    int i;
    for(i=0;i<n;i++)
        if(best_sol[i]==1)
            printf("(%d,%d) ", v[i].s, v[i].f);
    printf("max durata = %d", d_max);
}

void attSel(int N, att *v){
    int d_max=0;
    int *sol=(int *)malloc(63*sizeof(int));
    int *best_sol=(int *)malloc(N*sizeof(int));
    powerset(0,v,sol,N,best_sol,&d_max);
    printSol(best_sol, N, v, d_max);
    free(sol);
    free(best_sol);
}

att *readFile(int *N){
    FILE *fp = fopen(filename, "r");
    if(fp==NULL){
        printf("Error while opening file\n");
        exit(-1);
    }
    int n,i;
    fscanf(fp,"%d", &n);
    *N=n;
    att *v=(att *)malloc(n*sizeof(att));
    for(i=0;i<n;i++)
        fscanf(fp,"%d%d", &v[i].s, &v[i].f);
    fclose(fp);
    return v;
}

