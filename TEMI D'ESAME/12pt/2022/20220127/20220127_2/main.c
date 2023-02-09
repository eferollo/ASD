#include <stdio.h>
#include <stdlib.h>
#define filename "input.txt"
#define R 3
#define C 3

typedef struct{
    int i,j;
}nulls_t;

int check(int i, int j, nulls_t *n, int cnt){
    int k;
    for(k=0; k<cnt; k++){
        if(i==n[k].i && j==n[k].j)
            return 1;
    }
    return 0;
}

void insert(int val, int **M1, int r, int c){
    int i,j;
    for(i=0; i<r; i++)
        for(j=0; j<c; j++)
            if(M1[i][j]==0){
                M1[i][j]=val;
                return;
            }
}

void f(int **M, int r, int c, int *r0, int *c0, int ***M0){
    int i,j,k, cnt=0, null=0;
    nulls_t *n=malloc(200*sizeof(nulls_t));

    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            if(M[i][j]==0){
                n[cnt].i=i;
                n[cnt].j=j;
                cnt++;
                null++;
                for(k=0; k<c; k++){
                    if(k!=j){
                        n[cnt].i=i;
                        n[cnt].j=k;
                        cnt++;
                    }
                }
                for(k=0; k<r; k++){
                    if(k!=i){
                        n[cnt].i=k;
                        n[cnt].j=j;
                        cnt++;
                    }
                }
            }
        }
    }

    int r1=r-null, c1=c-null;
    int **M1=calloc(0,r1*sizeof (int *));
    for(i=0; i<2; i++) M1[i]=calloc(0,c1*sizeof (int));

    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            if(!check(i,j,n,cnt)){
                insert(M[i][j], M1, r1, c1);
            }
        }
    }
    *M0=M1;
    *r0=r1;
    *c0=c1;
}

int main() {
    int **M, i,j, r,c;
    FILE *fin;
    fin= fopen(filename,"r");
    if(fin==NULL) exit(-1);

    M=malloc(R*sizeof (int *));
    for(i=0; i<R; i++) M[i]=malloc(C*sizeof (int));
    for(i=0; i<R; i++)
        for(j=0; j<C; j++)
            fscanf(fin,"%d", &M[i][j]);
    int **M1;
    f(M,R,C,&r,&c, &M1);

    for(i=0; i<r; i++){
        for(j=0; j<c; j++)
            printf("%d ", M1[i][j]);
        printf("\n");
    }
    return 0;
}
