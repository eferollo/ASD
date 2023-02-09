#include <stdio.h>
#include <stdlib.h>

void genMat(int n){
    int i,j;
    int **m=malloc(n*sizeof(int *));
    for(i=0; i<n; i++) m[i]=malloc(n*sizeof(int));

    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            m[i][j]=abs(j-i);


    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
}

int main() {
    genMat(5);
    return 0;
}
