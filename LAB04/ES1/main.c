#include <stdio.h>
#include <stdlib.h>
#define filename "grafo.txt"

typedef struct{
    int u;
    int v;
}vertex_t;

vertex_t *readGraph(int *e, int *n);
int check(const int *sol, vertex_t *bows, int n, int e);
int powerset(vertex_t *bows, int *val, int k, int e, int *sol, int n, int pos, int start);
void vertex_cover();

int main() {
    vertex_cover();
    return 0;
}

vertex_t *readGraph(int *e, int *n){
    FILE *fp;
    fp=fopen(filename, "r");
    if(fp==NULL){
        printf("Error while opening file\n");
        exit(-1);
    }
    int N,E,i;
    fscanf(fp,"%d %d", &N, &E);
    *e=E;*n=N;
    vertex_t *bows;
    bows=(vertex_t *)malloc(E*sizeof(vertex_t));
    for(i=0;i<E;i++)
        fscanf(fp,"%d %d", &bows[i].u, &bows[i].v);
    fclose(fp);
    return bows;
}

int check(const int *sol, vertex_t *bows, int n, int e){
    int i,j,cnt=0;
    int check_b[e];
    for(i=0;i<e;i++) check_b[i]=0;
    for(i=0; i<n; i++)
        for(j=0;j<e;j++)
            if(check_b[j]==0 && (sol[i]==bows[j].u || sol[i]==bows[j].v)){
                check_b[j]=1;
                cnt++;
            }
    if(cnt==e)
        return 1;
    return 0;
}

int powerset(vertex_t *bows, int *val, int k, int e, int *sol, int n, int pos, int start){
    int count=0;
    int i;
    if(pos==n){
        if(check(sol,bows,n,e)){
            for(i=0; i<n; i++)
                printf("%d ", sol[i]);
            printf("\n");
            return 1;
        }
    }
    for(i=start; i<k; i++){
        sol[pos] = val[i];
        count+= powerset(bows, val, k,e,sol,n,pos+1,i+1);
    }
    return count;
}

void vertex_cover(){
    vertex_t *bows;
    int E,N, count=0,i;
    bows=readGraph(&E, &N);

    int *val=(int *)malloc(N*sizeof(int));
    int *sol=(int *)malloc(sizeof(int));

    for(i=0;i<N;i++) val[i]=i;
    for(i=2; i<=N; i++)
        count += powerset(bows, val, N,E, sol, i, 0,0);
}
