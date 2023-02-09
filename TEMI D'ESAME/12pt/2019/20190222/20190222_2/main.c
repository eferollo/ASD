#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum(int *V, int pos, int n){
    int i,sum=0;
    for(i=0; i<n; i++){
        sum+=V[pos+i];
    }
    return sum;
}

int f(int *V, int N, int *posMax, int *mMax){
    int i,j,s;

    int max=INT_MIN;
    for(i=1; i<N; i++){
        for(j=0; j<=N-i; j++){
            s=sum(V,j,i);
            if(s>max){
                max=s;
                *posMax=j;
                *mMax=i;
            }
        }
    }
    return max;
}

int main() {
    int V[]={-1,2,3,-6,1,3,1};
    int i,iMax,mMax,sum;
    sum=f(V,7,&iMax,&mMax);
    printf("Dim: %d, sum: %d\n", mMax,sum);
    for(i=iMax; i<iMax+mMax; i++)
        printf("%d ",V[i]);

    return 0;
}
