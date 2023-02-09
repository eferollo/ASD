#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define filename "easy_test_set.txt"
#define NP 5
int flag=0;

typedef struct{
    int mark[4];
    int dim;
}pietre_t;

pietre_t *readFile(int *num);
int check(char *sol, int pos);
int disp_ripet(int pos, pietre_t p, char *val, char *sol, int n, int k, int count, int *max);

int main() {
    pietre_t *p;
    int i,j,n,n_sol=0, max=0;
    char *sol, val[NP];
    strcpy(val, "ZRTS");
    p=readFile(&n);

    for(i=0; i<n; i++){
        flag=0,max=0;
        sol=(char *)malloc(sizeof(char));
        printf("TEST #%d\n\tzaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n",
               i+1, p[i].mark[0], p[i].mark[1], p[i].mark[2], p[i].mark[3], p[i].dim);
        for(j=p[i].dim; j>0; j--){
            sol=realloc(sol, j*sizeof(char));
            n_sol+= disp_ripet(0,p[i],val,sol,4,j,0, &max);
        }
        printf("\tCollana massima di lunghezza: %d\n\n", max);
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
    while(fscanf(fp,"%d%d%d%d", &p[i].mark[0], &p[i].mark[1], &p[i].mark[2], &p[i].mark[3])!=EOF){
        p[i].dim=(p[i].mark[0]+p[i].mark[1]+p[i].mark[2]+p[i].mark[3]);
        i++;
    }
    *num=n;
    fclose(fp);
    return p;
}

int check(char *sol, int pos){
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
    return 1;
}

int disp_ripet(int pos, pietre_t p, char *val, char *sol, int n, int k, int count, int *max){
    int i;
    if(pos >= k){
        if(k>*max && flag==0){
            flag=1;
            *max=k;
        }
        sol[*max]='\0';
        printf("\t%s\n", sol);
        return count+1;
    }
    for(i=0; i<n; i++){
        if(flag==1) return count;
        if(p.mark[i]>0){
            p.mark[i]--;
            sol[pos] = val[i];
            if(check(sol,pos))
                count=disp_ripet(pos+1, p, val, sol, n, k, count, max);
            p.mark[i]++;
        }
    }
    return count;
}

