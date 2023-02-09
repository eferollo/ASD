#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int f[4];
    int i;
}sol_t;

void powerset_r(int pos, int *ij, int *sol, int n, int k, int start, int **mat, int *index){
    int i;
    if(pos==n){
        for(i=0; i<n; i++){
            mat[*index][i]=sol[i];
        }
        for(; i<4; i++)
            mat[*index][i]=-1;
        *index=*index+1;
        return;
    }
    for(i=start; i<k; i++){
        sol[pos]=ij[i];
        powerset_r(pos+1,ij,sol,n,k,i+1,mat,index);
    }
}

void powerset(int *ij, int k, int *sol){

    int M[4][4]={1,1,0,1,
                 1,1,0,1,
                 0,0,1,0,
                 1,1,0,1};

    int n,i,j,x=0;
    int **mat=malloc(20*sizeof(int*));
    for(i=0; i<50; i++)
        mat[i]=malloc(4*sizeof (int));
    for(n=k; n>=1; n--){
        powerset_r(0, ij, sol,n, k, 0,mat,&x);
    }

    for(i=0; i<20; i++){
        for(j=0; j<4; j++)
            printf("%d ", mat[i][j]);
        printf("    %d\n",i);
    }

    int a,b,stop=0;
    sol_t *res=malloc(15*sizeof(*res));
    for(k=0; k<15; k++)
        res[k].i=-1;
    int z=-1;
    for(i=0; i<15; i++){
        for(j=0; j<4 && mat[i][j+1]!=-1; j++){
            a=mat[i][j];
            b=mat[i][(j+1)%3];
            if(M[a][b]==0)
                stop=1;
        }
        if(!stop){
            z++;
            for(k=0; k<4;k++){
                res[z].f[k]=mat[i][k];
            }
            res[z].i=i;
        }
        stop=0;
    }

    int cnt=0;
    int cnt_1=0;


    for(k=z; k>=0 ; k--){
        for(j=0; j<k ; j++){
            for(i=0; i<4; i++){
                for(x=0; x<4; x++){
                    if(res[k].f[i]==res[j].f[x] && res[j].f[x]!=-1)
                        cnt++;
                }
                if(res[k].f[i]!=-1)
                    cnt_1++;
            }
        }
        if(cnt_1!=cnt)
            printf("Amici %d", res[k].i);
        cnt=0;

    }

}
int main() {
    int *sol=malloc(4*sizeof(int));
    int ij[]={0,1,2,3};
    powerset(ij,4,sol);
    return 0;
}
