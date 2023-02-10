#include <stdio.h>
#include <stdlib.h>

void newMat(int **M, int r, int c, int val){
    int i,j;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            if(M[i][j]==val)
                M[i][j]=0;
        }
    }
}
int **subMat(int **M1,int r1,int c1,int **M2,int r2,int c2,int *dim){

}

int main() {
    FILE *fin;
    fin=fopen("input.txt","r");
    if(fin==NULL) exit(-1);
    int i,j,r1=4,c1=4, r2=3, c2=4;

    int **M1=malloc(r1 * sizeof(int *));
    for(i=0; i < r1; i++) M1[i]=malloc(c1 * sizeof (int));
    int **M2=malloc(r2 * sizeof(int *));
    for(i=0; i < r2; i++) M2[i]=malloc(c2 * sizeof (int));

    for(i=0; i < r1; i++)
        for(j=0; j < c1; j++)
            fscanf(fin,"%d ", &M1[i][j]);
    for(i=0; i < r2; i++)
        for(j=0; j < c2; j++)
            fscanf(fin,"%d ", &M2[i][j]);
    fclose(fin);

    int dim;
    int **M3= subMat(M1,r1,c1,M2,r2,c2,&dim);

    return 0;
}
