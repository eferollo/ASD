#include <stdio.h>
#include <stdlib.h>

void SP_rec(int pos, int *sol, int *P, int *S, int nP, int nS, int k, int m, int *stop){
    int i,j,z,sum,cnt,flag;
    if(*stop)
        return;

    if(pos>=nP){
        if(m==k){
            int *mark=malloc(nS*sizeof(int));
            for(z=0;z<nS;z++) mark[z]=S[z];
            cnt=0;
            for(i=0; i<m; i++){
                flag=0;
                sum=0;

                for(j=0; j<nP; j++)
                    if(sol[j]==i)
                        sum+=P[j];

                for(z=0;z<nS && !flag;z++)
                    if(sum<=mark[z]){
                        mark[z]=0;
                        cnt++;
                        flag=1;
                    }
            }
            if(cnt==m){
                for(i=0; i<m; i++) {
                    *stop=1;
                    printf("{");
                    for (j = 0; j < nP; j++)
                        if (sol[j] == i)
                            printf("%d", P[j]);
                    printf("} ");
                }
                printf("\n");
                free(mark);
            }
        }
        return;
    }
    for(i=0; i<m; i++){
        sol[pos]=i;
        SP_rec(pos+1,sol,P,S,nP,nS,k,m,stop);
    }
    sol[pos]=m;
    SP_rec(pos+1, sol, P,S,nP,nS, k,m+1,stop);
}
void solve(int *S, int nS, int *P, int nP){
    int *sol=malloc(nP*sizeof(int));
    int i,stop=0;
    for(i=1; i<=nS && stop==0; i++)
        SP_rec(0,sol,P,S,nP,nS,i,0,&stop);
    free(sol);
}

int main() {
    int S[]={4,9,11,5};
    int P[]={2,2,3,2,6,2,4,4,3};
    solve(S,4,P,9);
    return 0;
}
