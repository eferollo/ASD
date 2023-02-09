#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define filename "brani.txt"

typedef struct{
    int n;
    char **songs;
}songs_t;

songs_t *readFile(int *nread);
int princ_molt(int pos, songs_t *friends, char **sol, int n, int count);
void freeStruct(songs_t *a, int n);
void freeSol(char **sol, int n);

int main() {
    songs_t *friends;
    int n,i;
    friends=readFile(&n);

    char **sol;
    sol=(char **)malloc(n*sizeof(char *));
    for(i=0;i<n;i++)
        sol[i]=(char *)malloc(256*sizeof(char));

    int n_playlist=princ_molt(0,friends,sol,n,0);
    printf("\nNumero di playlist possibili: %d", n_playlist);

    freeSol(sol,n);
    freeStruct(friends,n);
    return 0;
}

songs_t *readFile(int *nread){
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("Error while opening file\n");
        exit(-1);
    }
    int n,n_s;
    fscanf(fp,"%d", &n);
    *nread=n;
    songs_t *friends=(songs_t *)malloc(n*sizeof(songs_t));
    for(int i=0;i<n;i++){
        fscanf(fp,"%d", &n_s);
        friends[i].n=n_s;
        friends[i].songs=(char **)malloc(n_s*sizeof(char *));
        for(int j=0;j<n_s;j++){
            friends[i].songs[j]=(char *)malloc(256*sizeof(char));
            fscanf(fp,"%s", friends[i].songs[j]);
        }
    }
    return friends;
}

int princ_molt(int pos, songs_t *friends, char **sol, int n, int count){
    int i;
    if(pos>=n){
        for(i=0;i<n;i++)
            printf("\n%s ", sol[i]);
        printf("\n");
        return count+1;
    }
    for(i=0; i<friends[pos].n; i++){
        strcpy(sol[pos],friends[pos].songs[i]);
        count= princ_molt(pos+1, friends, sol, n, count);
    }
    return count;
}

void freeStruct(songs_t *a, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<a[i].n;j++)
            free(a[i].songs[j]);
        free(a[i].songs);
    }
    free(a);
}

void freeSol(char **sol, int n){
    for(int i=0;i<n;i++)
        free(sol[i]);
    free(sol);
}

