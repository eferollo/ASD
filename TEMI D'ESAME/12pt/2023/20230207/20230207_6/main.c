#include <stdio.h>
#include <stdlib.h>

int jump(int **M, int a, int b, int n){
    int i;
    for(i=0; i<n; i++){

    }
}
int check(int **M, int m, int n, int *sol, int *val){
}

void sp_rec(int pos, int **M, int *sol, int *val, int n, int k, int m){
    int i,j;
    if(pos>=n){
        if(m==k){
            if(check(M,m,n,sol,val)){
                for(i=0; i<m; i++){
                    printf("{");
                    for(j=0; j<n; j++)
                        if(sol[j]==i){
                            printf("%d",val[j]);
                        }
                    printf("} ");

                }
                printf("\n");
            }
            }
        return;
    }

    for(i=0; i<m; i++){
        sol[pos]=i;
        sp_rec(pos+1,M,sol,val,n,k,m);
    }
    sol[pos]=m;
    sp_rec(pos+1,M,sol,val,n,k,m+1);
}

void powerset(int **M, int n){
    int *sol=malloc(n*sizeof(int));
    int *val=malloc(n*sizeof (int));
    int i;
    for(i=0; i<n; i++) val[i]=i;
    for(i=1; i<=n; i++)
        sp_rec(0,M,sol,val,n,i,0);
}
int main() {
    int i,j,N=7;
    int **M=malloc(N*sizeof(int *));
    for(i=0; i<N; i++) M[i]=malloc(N*sizeof(int));
    FILE *fin= fopen("input.txt","r");
    if(fin==NULL) exit(-1);
    for(i=0; i<N; i++)
        for(j=0; j<N; j++)
            fscanf(fin,"%d ", &M[i][j]);

    powerset(M,N);
    return 0;
}