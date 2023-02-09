#include <stdio.h>
#include <stdlib.h>

void f(int **M, int r, int c){
    int i, j, r1,c1, pi=0, pj=0;
    r1=r/2;
    c1=c/2;
    int maxr=(r%2==0)?r1:(r1+1);
    int maxc=(c%2==0)?c1:(c1+1);

    int **M1=malloc(maxr*sizeof (int *));
    for(i=0; i<maxr; i++) M1[i]=malloc(maxc*sizeof(int));

    for(i=0; i<r; i++){
        if(i%2==0){
            for(j=0; j<c; j++){
                if(j%2==0){
                    M1[pi][pj]=M[i][j];
                    pj++;
                }
            }
            pj=0;
            pi++;
        }
    }

    for(i=0; i<maxr; i++){
        for(j=0; j<maxc; j++)
            printf("%d ", M1[i][j]);
        printf("\n");
    }

    for(i=0; i<maxr; i++)
        free(M1[i]);
    free(M1);
}

int main() {
    int i,j,r,c;
    FILE *fin=fopen("input.txt", "r");
    if(fin == NULL) exit(-1);
    fscanf(fin, "%d %d", &r, &c);

    int **M=malloc(r*sizeof(int *));
    for(i=0; i<r; i++) M[i]=malloc(c*sizeof(int));

    for(i=0; i<r; i++)
        for(j=0; j<c; j++)
            fscanf(fin,"%d", &M[i][j]);

    f(M,r,c);

    for(i=0; i<r; i++)
        free(M[i]);
    free(M);
    return 0;
}
