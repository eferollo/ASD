#include <stdio.h>
#include <stdlib.h>
#define filename "att2.txt"

typedef struct{
    int s,f;
}att;

att *readFile(int *N);
void MergeSort(att *A, int N);
void MergeSortR(att *A, att *B, int l, int r);
void Merge(att *A, att *B, int l, int q, int r);
int check_inc(att i, att j);
void printSol(int *best_sol, int n, att *v, int d_max);
void check_sol(int *sol, int *best_sol, att *v, int k, int *d_max);
void powerset(int pos, att *v, int *sol, int k, int *best_sol, int *d_max);
void attSel(int N, att *v);
void attSelDP(int N, att *v);
void printSolDP(int index, att *v, int *best_sol, int *sol, int *d);

int main() {
    int n;
    att *v=readFile(&n);
    MergeSort(v, n);
    for(int i=0; i<n; i++) printf("%d %d\n", v[i].s, v[i].f);
    printf("\nSoluzione tramite powerset\n");
    attSel(n, v);
    printf("\n\nSoluzione tramite programmazione dinamica\n");
    attSelDP(n,v);
    free(v);
    return 0;
}

int check_inc(att i, att j){
    if(i.s<j.f && j.s<i.f)
        return 1;
    return 0;
}

int max(int a, int b){
    if(a>b)
        return a;
    return b;
}

void printSolDP(int index, att *v, int *best_sol, int *sol, int *d){

    if (index == -1)
        return;

    if (v[index].f - v[index].s + best_sol[sol[index]] >= best_sol[index - 1]) {
        printSolDP(sol[index] - ((index == 0) ? 1 : 0), v, best_sol, sol, d);
        *d+=v[index].f-v[index].s;
        printf("(%d,%d) ", v[index].s, v[index].f);
    }
    else
        printSolDP(index - 1, v, best_sol, sol, d);

}

void attSelDP(int N, att *v){
    int i,j, *sol, *best_sol;
    sol=(int *)calloc(N, sizeof(int));
    best_sol=(int *)calloc(N,sizeof(int));
    for(i=1; i<N; i++)
        for(j=0; j<i; j++)
            if(check_inc(v[i],v[j])==0)
                sol[i]=j;

    for(i=0; i<N; i++)
        best_sol[i] =max(v[i].f-v[i].s+best_sol[sol[i]], best_sol[i-1]);
    int d_max=0;
    printSolDP(N - 1, v, best_sol, sol, &d_max);
    printf("max durata = %d\n", d_max);

    free(sol);
    free(best_sol);
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

void Merge(att *A, att *B, int l, int q, int r){
    int i,j,k;
    i=l;
    j=q+1;
    for(k=l; k<=r; k++)
        if(i > q)
            B[k]=A[j++];
        else if(j > r)
            B[k]=A[i++];
        else if(A[i].f <= A[j].f)
            B[k]=A[i++];
        else
            B[k]=A[j++];
    for(k=l; k<=r; k++)
        A[k]=B[k];
    return;
}

void MergeSortR(att *A, att *B, int l, int r){
    int q;
    if(l>=r)
        return;
    q = (l+r)/2;
    MergeSortR(A,B,l,q);
    MergeSortR(A,B,q+1,r);
    Merge(A,B,l,q,r);
}

void MergeSort(att *A, int N){
    int l=0, r=N-1;
    att *B=(att *)malloc(N* sizeof(att));
    MergeSortR(A,B,l,r);
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
