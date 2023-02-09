#include <stdio.h>
#include <stdlib.h>

void genmark(int *mark, int *disp, int n){
    int i;
    for(i=0; i<n; i++)
        mark[i]=disp[i];
}
void powerset_r(int pos, int *val, int *mark, int *sol, int n, int k, int start, int *sum, int r, int *stop){
    int i;
    if(pos==n){
        if(*sum==r){
            for(i=0; i<n; i++)
                printf("%d ", sol[i]);
            printf("sum: %d\n", *sum);
            *stop=1;
        }
        return;
    }
    for(i=start; i<k; i++){
        if(!*stop && mark[i]>0 && *sum+val[i]<=r){
            *sum+=val[i];
            sol[pos]=val[i];
            mark[i]--;
            powerset_r(pos+1, val, mark,sol,n,k,start,sum,r,stop);
            *sum-=val[i];
            start++;
            mark[i]++;
        }else
            return;
    }
}

void powerset(int *val, int *disp, int n, int r){
    int i,num=0;
    int *mark=malloc(n*sizeof(int));
    for(i=0; i<n; i++) num+=disp[i];
    int *sol=malloc(sizeof(int));
    int sum=0, stop=0;
    for(i=1; i<=num && stop==0; i++){
        genmark(mark,disp,n);
        sol=realloc(sol,i*sizeof(int));
        powerset_r(0,val,mark,sol,i,n,0,&sum,r,&stop);
    }
    free(sol);
    free(mark);
}

int main() {
    int val[]={1,10,25};
    int disp[]={10,3,2};
    powerset(val,disp,3,30);
    return 0;
}
