#include <stdio.h>
#include <stdlib.h>

void powerset_r(int pos, int *V, int *sol, int n, int k, int start, int *stop, int *change){
    int i;
    if(pos==k){
        *stop=1;
        for(i=0; i<k; i++)
            printf("%d ",sol[i]);
        printf("\n");
        return;
    }

    for(i=start; i<n; i++){
        if(*stop)
            return;
        if(i==0){
            sol[pos]=V[i];
            powerset_r(pos + 1, V, sol,  n, k, i + 1, stop, change);
        }else if(*change==0){
            if(V[i]>sol[pos-1]){
                sol[pos]=V[i];
                powerset_r(pos + 1, V, sol,  n, k, i + 1, stop, change);
            }else{
                *change=1;
                sol[pos]=V[i];
                powerset_r(pos + 1, V, sol,  n, k, i + 1, stop, change);
                *change=0;
            }
        }else if(*change==1){
            if(V[i]<sol[pos-1]){
                sol[pos]=V[i];
                powerset_r(pos + 1, V, sol, n, k, i + 1, stop, change);
            }
        }
    }
}

void wrapper(int *V, int n){
    int *sol=malloc(sizeof(int));
    int i,stop=0,change=0;
    for(i=n; i>1 && stop==0; i--){
        sol=realloc(sol,i*sizeof(int));
        powerset_r(0, V, sol, n, i, 0, &stop, &change);
        //stop=0;
    }
}
int main() {
    int V[]={4,2,5,9,7,6,10,3,1};
    //int V[]={1,2,3,4,5};
    wrapper(V,9);
    return 0;
}
