#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int i,j
}sol_t;

void print(int **M, int r, int c){
    int i,j;
    for(i=0; i<r;i++){
        for(j=0; j<c; j++){
            printf("%d ",M[i][j]);
        }
        printf("\n");
    }
}

void change(int **M, int r, int c){
    int i,j,k=0;
    sol_t *coppia=malloc(r*c*sizeof(*coppia));

    for(i=0; i<r;i++){
        for(j=0; j<c; j++){
            if(M[i][j]%3==0){
                coppia[k].i=i;
                coppia[k].j=j;
                k++;
            }
        }
    }

    for(j=0; j<k-1; j++){
        for(i=0; i<c; i++)
            M[coppia[j].i][i]=3;
        for(i=0; i<r; i++)
            M[i][coppia[j].j]=3;
    }
    free(coppia);
}

int main() {
    int i,j,r=3,c=4;
    int **M=malloc(r*sizeof(int));
    for(i=0; i<r; i++) M[i]=malloc(c*sizeof(int));
    FILE *fin= fopen("input.txt","r");
    if(fin==NULL) exit(-1);
    for(i=0; i<r; i++)
        for(j=0; j<c; j++)
            fscanf(fin,"%d ", &M[i][j]);

    change(M,r,c);
    print(M,r,c);
    fclose(fin);

    return 0;
}
