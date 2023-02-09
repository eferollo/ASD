#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int check_lowercase(char *sol, int k){
    int i,cnt=0;
    for(i=0; i<k; i++){
        if(islower(sol[i]))
            cnt++;
    }
    if(cnt<=k/2)
        return 1;
    return 0;
}

void powerset_r(int pos, char *sol, int k, int p, int last_c, int mark){
    int i;
    if(pos==k){
        if(check_lowercase(sol,k)){
            for(i=0; i<k; i++)
                printf("%c", sol[i]);
            printf("\n");
        }
        return;
    }
    for(i='a'; i<'z'; i++){
        if(i==last_c){
            if(mark+1<=p){
                sol[pos]=(char)i;
                powerset_r(pos+1,sol,k,p,i,mark+1);
            }
        }else{
            sol[pos]=(char)i;
            powerset_r(pos+1,sol,k,p,i,1);
        }

    }
    for(i='A'; i<'Z'; i++){
        if(i==last_c){
            if(mark+1<=p){
                sol[pos]=(char)i;
                powerset_r(pos+1,sol,k,p,i,mark+1);
            }
        }else{
            sol[pos]=(char)i;
            powerset_r(pos+1,sol,k,p,i,1);
        }
    }
}

void powerset(char *sol, int k, int p){
    powerset_r(0,sol,k,p,0,0);
}
int main() {
    //char charset[]= "abcdefghilmnopqrstuvzABCDEFGHILMNOPQRSTUVZ";
    int k=3;
    char *sol=malloc(k*sizeof(char));
    powerset(sol,k,2);
    return 0;
}
