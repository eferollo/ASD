#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int conta(char **matrice, int n, int m, char *stringa){
    int i,j,k, cnt=0;
    for(j=0; j<m; j++){
        k=0;
        for(i=0; i<n; i++)
            if(matrice[i][j]==stringa[k])
                k++;
        if(k==strlen(stringa)) cnt++;
    }
    for(i=0; i<n; i++){
        k=0;
        for(j=0; j<m; j++)
            if(matrice[i][j]==stringa[k])
                k++;
        if(k==strlen(stringa)) cnt++;
    }
    return cnt;
}

int main() {
    FILE *fin;
    fin=fopen("input.txt","r");
    if(fin==NULL) exit(-1);
    int i,j,n=4,m=5;
    char **A=malloc(n*sizeof(char *));
    for(i=0; i<n; i++) A[i]=malloc(m*sizeof (char));
    for(i=0; i<n; i++)
        for(j=0; j<m; j++)
            fscanf(fin,"%c ", &A[i][j]);

    printf("N = %d\n",conta(A,4,5,"cat"));
    fclose(fin);
    return 0;
}
