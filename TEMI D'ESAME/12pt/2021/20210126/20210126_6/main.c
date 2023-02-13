#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getstr(int *sol, char **dict, int n){
    int i;
    char *str=malloc(sizeof(char));
    for(i=0; i<n; i++){
        strcat(str,dict[sol[i]]);
    }
    return str;
}

int check_rip(int *mark, int n, int s){
    int i,cnt=0;
    for(i=0; i<n; i++)
        if(mark[i]==1)
            cnt++;
    if(cnt>=s)
        return 1;
    return 0;
}

void disp_rip(int pos, char *str, char **dict, int *sol, int *mark, int n, int k, int s,int *stop){
    int i;
    if(*stop)
        return;
    if(pos==k){
        char *res;
        res= getstr(sol,dict,pos);
        if(strcmp(res, str)==0 && check_rip(mark,n,s)){
            *stop=1;
            for(i=0; i<k; i++)
                printf("%s ", dict[sol[i]]);
            free(res);
        }
        return;
    }
    for(i=0; i<n; i++){
        if(!*stop && strlen(getstr(sol,dict,pos)) + strlen(dict[i]) <= strlen(str)+1){
            mark[i]=1;
            sol[pos]=i;
            disp_rip(pos+1,str,dict,sol,mark, n,k,s,stop);
        }else
            mark[i]=0;
    }
}
void solve(char *str, char **dict, int n, int s){
    int *sol=malloc(sizeof(int));
    int *mark=calloc(n,sizeof(int));
    int i,stop=0;
    printf("s = %d -> ",s);
    for(i=s; i<n && stop==0; i++){
        sol=realloc(sol,i*sizeof(int));
        disp_rip(0,str,dict,sol,mark,n,i,s,&stop);
        mark=calloc(n,sizeof(int));
    }
    free(mark);
    free(sol);
}

int main() {
    char *str="abracadabra";
    char *dict[8]={"a", "ab", "cada", "abra", "ra", "da", "ca", "bra"};
    solve(str,dict,8,3);
    return 0;
}
