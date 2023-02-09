#include <stdio.h>
#include <stdlib.h>

int calc_weight(int *price, int *sol, int *len, int index, int m){
    int i,j,w=0;
    for(j=0; j<m; j++){
        if(len[j]==sol[index]){
            w+=price[j];
            break;
        }
    }
    return w;
}
void powerset_r(int pos, int *len, int *price, int n, int max, int k, int *sol,
                int *bestsol,int *bi, int weight, int *bweight, int l, int start){
    int i;
    if(pos==n){
        int sum=0;
        for(i=0; i<pos; i++) sum+=sol[i];
        if(sum!=max)
            return;
        if(weight>*bweight){
            *bweight=weight;
            bestsol=realloc(bestsol,pos*sizeof(int));
            for(i=0; i<pos; i++) bestsol[i]=sol[i];
            *bi=pos;
        }
        return;
    }
    for(i=start; i<k; i++){
        if(l+len[i]<=max){
            sol[pos]=len[i];
            l+=len[i];
            weight+=calc_weight(price,sol,len,pos,k);
            powerset_r(pos+1,len,price,n,max,k,sol,bestsol,bi,weight,bweight,l, start);
            weight-=calc_weight(price,sol,len,pos,k);
            l-=len[i];
            start++;
        }
    }
}

void powerset(int *len, int *price, int n, int m){
    int i;
    int *sol=malloc(m*sizeof(int));
    int *bestsol=malloc(sizeof(int));
    int weight=0,index;
    for(i=1; i<=n; i++){
        sol=realloc(sol,i*sizeof(int));
        powerset_r(0,len,price,i,n,m,sol,bestsol,&index,0,&weight,0,0);
    }
    printf("Soluzione ottima:\n");
    for(i=0;i<index; i++)
        printf("%d ", bestsol[i]);
    printf("   peso=%d",weight);
}

int main() {
    int lunghezza[8]={7,4,8,1,5,2,6,3};
    int prezzo[8]={17,9,20,1,10,5,17,8};
    powerset(lunghezza,prezzo,4,8);

    return 0;
}
