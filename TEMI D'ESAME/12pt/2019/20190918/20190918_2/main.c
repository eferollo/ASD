#include <stdio.h>
#include <stdlib.h>


int findBound(int *V, int N, int *lp, int *rp){
    int start=-1, end=-1;
    int max=0, curr=0, i;
    for(i=0; i<N; i++){
        if(V[i]>0){
            if(curr==0)
                start=i;
            curr++;
        }else{
            if(curr > max){
                max=curr;
                end=i-1;
                *lp=start;
                *rp=end;
            }
            curr=0;
        }
    }
    if(curr>max){
        *lp=start;
        *rp=N-1;
    }
    if((max==0 && curr==0))
        return 0;
    return 1;
}

void dec(int *V, int l, int r){
    int i;
    for(i=l; i<=r; i++)
        V[i]--;
}
void print(int *V, int n){
    for(int i=0; i<n;i++){
        printf("%d ", V[i]);
    }
    printf("\n");
}
void toZero(int *V, int n){
    int lp=0,rp=0;
    print(V,n);
    while(findBound(V,n,&lp,&rp)){
        dec(V,lp,rp);
        print(V,n);
    }
}
int main() {
    int V[]={3,1,2,0,0,3,4,5};
    int lp=0,rp=0;
    toZero(V,8);
    return 0;
}
