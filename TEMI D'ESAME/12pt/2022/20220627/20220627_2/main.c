#include <stdio.h>
#include <stdlib.h>
#define D 2
#define R 3
#define C 3

void flatten(int ***M){
    int i,j,cnt,add=0;
    int **M1=malloc(D*R*sizeof(int *));
    for(i=0; i<D*R; i++)
        M1[i]=malloc(D*C*sizeof(int));

    for(i=0; i<D*R; i++){
        cnt=0;
        if(i%D==1 && i!=1)
            add=D;
        for(j=0; j<D*C; j++){
            if(cnt>=R ){
                M1[i][j]=M[add][i%R][j%C];
                cnt++;
            }
            if(cnt<R){
                M1[i][j]=M[add][i%R][j%C];
                cnt++;
            }
        }
    }

    for(i=0; i<D*R; i++){
        for(j=0; j<D*C; j++){
            printf("%d ", M1[i][j]);
        }
        printf("\n");
    }
}


int main() {
    int ***M,i,j,k;
    M=malloc(D*D*sizeof(int **));
    for(i=0; i<D*D ;i++){
        M[i]=malloc(R*sizeof(int));
        for(j=0; j<R; j++){
            M[i][j]=malloc(C*sizeof(int *));
        }
    }
    FILE *fp;
    fp= fopen("input.txt","r");
    for(i=0; i<D*D; i++)
        for(j=0; j<R; j++)
            for(k=0; k<C; k++)
                fscanf(fp,"%d", &M[i][j][k]);

    flatten(M);
    return 0;
}
