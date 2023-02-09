#include <stdio.h>
#include <stdlib.h>

void findfill(int *mark, int dim, int *I, int val){
    int i;
    for(i=0; i<dim; i++)
        if(I[i]==val)
            mark[i]=1;
}

void powerset_r(int pos, int *I, int *sol, int target, int n,int k, int start, int value, int *mark, int *stop){
    int i;
    if(pos==n){
        if(value==target){
            for(i=0; i<pos; i++){
                findfill(mark,k,I,sol[i]);
                if(i==0) printf("(");
                printf("%d",sol[i]);
                if(i==pos-1){
                    printf(")\n");
                    *stop=1;
                    break;
                }
                printf("+");
            }
        }
        return;
    }
    for(i=start; i<k; i++){
        if(value+I[i]<=target && !mark[i]){
            sol[pos]=I[i];
            value=value+I[i];
            powerset_r(pos+1,I,sol,target,n,k,i+1,value,mark,stop);
            value=value-I[i];
        }
    }
}

void powerset(int *I, int *S, int dimI, int dimS){
    int *sol=malloc(sizeof(int));
    int n,j, stop=0;
    int mark[dimI];
    for(j=0; j<dimI; j++)
        mark[j]=0;
    for(j=0; j<dimS; j++){
        stop=0;
        for(n=1; n<dimI && !stop; n++){
            sol=realloc(sol,n*sizeof(int));
            powerset_r(0,I,sol, S[j],n,dimI,0,0,mark,&stop);
        }
    }
    free(sol);
}
int main() {
    int I[6]={1,2,3,4,5,6};
    int S[3]={1,7,7};
    powerset(I,S,6,3);
    return 0;
}