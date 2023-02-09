#include <stdio.h>
#include <stdlib.h>

int minmaxdiff(int A[][3], int n, int m){
    int i,j, res, min,val;
    int *diff=calloc(m,sizeof(int));
    for(i=0; i<m; i++){
        for(j=0; j<n-1; j++){
            res=abs(A[j][i]-A[j+1][i]);
            if(diff[i]<res)
                diff[i]=res;
        }
    }
    min=diff[0];
    for(i=1; i<m; i++)
        if(diff[i]<min){
            min=diff[i];
            val=i;
        }
    return val;
}

int main() {
    int A[4][3]={15,13,7,
                 6,18,4,
                 11,4,12,
                 13,9,5};
    printf("Indice: %d\n", minmaxdiff(A,4,3));
    return 0;
}
