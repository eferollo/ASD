#include <stdio.h>
#include <stdlib.h>

void disp_sempl(int pos, int *V, int *sol, int *mark, int n, int k, int *stop){
    int i;
    if(pos==k){
        *stop=1;
        for(i=0; i<k; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return;
    }
    for(i=0; i<n; i++){
        if(mark[i]==0){
            if(pos>0 && ((pos%2==0 && V[i]<sol[pos-1]) || (pos%2!=0 && V[i]>sol[pos-1]))){
                mark[i]=1;
                sol[pos]=V[i];
                disp_sempl(pos + 1, V, sol, mark, n, k,stop);
                if(*stop) return;
            }else if(pos==0){
                mark[i]=1;
                sol[pos]=V[i];
                disp_sempl(pos + 1, V, sol, mark, n, k,stop);
                if(*stop) return;
            }
            mark[i]=0;
        }
    }
}
//if((pos%2==0 && sol[pos]<V[i]) || (pos%2!=0 && V[i]>sol[pos-1]))
void wrapper(int *V, int n){
    int *sol=calloc(1,sizeof(int));
    int i,stop=0;
    int *mark=calloc(n,sizeof (int));
    for(i=n; i>1 && stop==0; i--){
        sol= realloc(sol,i*sizeof (int));
        mark=calloc(n,sizeof (int));
        disp_sempl(0, V, sol, mark, n, i,&stop);
        //stop=0;
    }
}
int main() {
    int V[9]={8,9,6,4,5,7,3,2,4};
    wrapper(V,9);
    return 0;
}
