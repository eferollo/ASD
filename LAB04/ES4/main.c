#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define filename "test_set.txt"
#define NP 5
int flag=0, start=0;

typedef struct{
    int mark[4];
    int value[4];
    int max_rip;
    int dim;
    int max_len, max_val;
}pietre_t;

pietre_t *readFile(int *num);
int check(char *sol, int pos, int cnt_z, int cnt_s);
int disp_ripet(int pos, pietre_t *p, char *val, char *sol, int n, int k, int count, int *max, int cnt_z, int cnt_s, char **best_sol, int *max_val);
int check_zs(char *sol);

int main() {
    pietre_t *p;
    int i,j,n,n_sol=0, max=0, cnt_z, cnt_s, max_val;
    char *sol, val[NP], *best_sol;
    strcpy(val, "ZRTS");
    p=readFile(&n);
    for(i=3; i<n ; i++){
        flag=0; max=0; cnt_z=0; max_val=0; cnt_s=0;
        sol=(char *)malloc(sizeof(char));
        printf("TEST #%d\n\tzaffiro = %d [%d], rubino = %d [%d], topazio = %d [%d], smeraldo = %d [%d],"
               " TOT = %d {max_rip = %d}\n",
               i+1, p[i].mark[0], p[i].value[0], p[i].mark[1], p[i].value[1], p[i].mark[2], p[i].value[2],
               p[i].mark[3], p[i].value[3], p[i].dim, p[i].max_rip);
        for(j=p[i].dim; j>0; j--){
            sol=realloc(sol, j*sizeof(char));
            n_sol= disp_ripet(0,&p[i],val,sol,4,j,0, &max, cnt_z, cnt_s, &best_sol,&max_val);
            max_val=0;
        }
        printf("\tSoluzione ottima di valore %d usando %d gemma/e\n"
               "\tComposizione collana: %s\n\n", p[i].max_len, p[i].max_val, best_sol);
        free(sol);
    }
    free(p);
    return 0;
}

pietre_t *readFile(int *num){
    pietre_t *p;
    FILE *fp;
    fp= fopen(filename,"r");
    if(fp==NULL){
        printf("Error while opening file\n");
        exit(-1);
    }
    int n,i=0;
    fscanf(fp,"%d", &n);
    p=(pietre_t *)malloc(n*sizeof(pietre_t));
    while(fscanf(fp,"%d%d%d%d%d%d%d%d%d", &p[i].mark[0], &p[i].mark[1], &p[i].mark[2], &p[i].mark[3],
                 &p[i].value[0], &p[i].value[1],&p[i].value[2],&p[i].value[3], &p[i].max_rip)!=EOF){
        p[i].dim=(p[i].mark[0]+p[i].mark[1]+p[i].mark[2]+p[i].mark[3]);
        i++;
    }
    *num=n;
    return p;
}

int check(char *sol, int pos, int cnt_z, int cnt_s){
    int x=pos-1;
    if(x>=0){
        if(sol[x]=='Z' && (sol[pos]!='Z' && sol[pos]!='R'))
            return 0;
        if(sol[x]=='S' && (sol[pos]!='S' && sol[pos]!='T'))
            return 0;
        if(sol[x]=='R' && (sol[pos]!='S' && sol[pos]!='T'))
            return 0;
        if(sol[x]=='T' && (sol[pos]!='Z' && sol[pos]!='R'))
            return 0;
    }
    if(sol[x]=='Z' && sol[pos] == 'Z')
        cnt_z++;
    if(sol[x]=='S' && sol[pos] == 'S')
        cnt_s++;
    return 1;
}

int check_zs(char *sol){
    int n_z=0, n_s=0;
    for(int i=0; i< strlen(sol); i++){
        if(sol[i]=='Z') n_z++;
        if(sol[i]=='S') n_s++;
    }
    if(n_z<=n_s) return 1;
    return 0;
};

int disp_ripet(int pos, pietre_t *p, char *val, char *sol, int n, int k, int count, int *max, int cnt_z, int cnt_s, char **best_sol, int *max_val){
    int i;
    if(pos >= k){
        if(k>p->max_len && flag==0 && check_zs(sol)){
            if(*max_val>p->max_val){
                *best_sol=sol;
                flag=1;
                p->max_len=k;
                p->max_val=*max_val;
            }
        }
        //printf("%s\n", sol);
        return count+1;
    }
    for(i=0; i<n; i++){
        if(flag==1) return count;
        if(p->mark[i]>0){
            if(i==0 && pos==0) cnt_z=1;
            if(i==3 && pos==0) cnt_s=1;
            if(cnt_z<p->max_rip || cnt_s<p->max_rip || start==0){
                start=1;
                p->mark[i]--;
                sol[pos] = val[i];
                *max_val+=p->value[i];
                if(check(sol,pos,cnt_z,cnt_s))
                    count=disp_ripet(pos+1, p, val, sol, n, k, count, max,cnt_z,cnt_s, best_sol, max_val);
                p->mark[i]++;
                *max_val-=p->value[i];
            }
            start=0;
            cnt_z=1;
            cnt_s=1;
        }
    }
    return count;
}
