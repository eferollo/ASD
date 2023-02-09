#include <stdio.h>
#define n 8

int majority1(int *a, int N, int l, int r){
    int m,mSx, mDx, cntSx=0, cntDx=0,i;
    m=(l+r)/2;

    if(l==r) return a[l];

    mSx= majority1(a,N,l,m);
    mDx= majority1(a,N,m+1,r);

    if(mSx==mDx){
        if(mSx==-1 && mDx==-1) return -1;
        else return mSx;
    }

    for(i=l;i<=r;i++)
        if(a[i]==mSx)
            cntSx++;

    for(i=0;i<=r;i++)
        if(a[i]==mDx)
            cntDx++;

    if(cntSx>N/2) return mSx;
    if(cntDx>N/2) return mDx;

    return -1;

}
int majority(int *a, int N){
    int l=0, r=N-1, m;
    m=majority1(a,N,l,r);
    return m;
}
int main() {
    int vet[n]={0, 1, 0, 2, 3, 4, 0, 5};
    int m= majority(vet,n);
    if(m!=-1)
        printf("Majority element: %d",m);
    else
        printf("Majority element not found");
    return 0;
}
