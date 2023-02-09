#include <stdio.h>
#include <stdlib.h>

void buildAndPrint(int *V, int N, int **M, int r, int c){
    int i,j, k=0, pos, n, times=0;
    for(i=0; i<r; i++){
        pos=0;
        n=0;
        while(pos!=c){
            for(j=n; times<V[k] ; j++, pos++, times++)
                M[i][j]=V[k+1];
            times=0;
            n=j;
            k=k+2;
        }
    }
    for(i=0; i<r; i++){
        for(j=0;j<c;j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }
}

int main() {
    int V[]={2, 1, 2, 17, 1, 3, 4, 8, 1, 6, 3, 7, 2, 5};
    int r=3, c=5, i;
    int **M=malloc(r*sizeof(int *));
    for(i=0; i<r; i++) M[i]=malloc(c*sizeof (int));
    buildAndPrint(V,14, M, r,c);
    return 0;
}
