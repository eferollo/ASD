#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int getMax(int **M, int r, int c){
    int i,j,max=INT_MIN;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            if(M[i][j]>max)
                max=M[i][j];
        }
    }
    return max;
}

int calc_sum(int **M, int lr, int r, int lc, int c){
    int i,j,sum=0;
    for(i=lr; i<r; i++){
        for(j=lc; j<c; j++){
            sum+=M[i][j];
        }
    }
    return sum;
}

void print(int **A, int lr, int r, int lc, int c){
    int i,j;
    for(i=lr; i<r; i++){
        for(j=lc; j<c; j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

int f(int **M, int r, int c){
    int i,j,s,max_elem,max_size,sum,cnt=0;
    max_elem= getMax(M,r,c);

    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            max_size=(r-i < c-j) ? r-i : c-j;
            for(s=2; s<=max_size; s++){
                sum= calc_sum(M, i,i+s, j,j+s);
                if(sum<max_elem){
                    print(M,i,i+s, j,j+s);
                    cnt++;
                }
            }
        }
    }
    return cnt;
}

int main() {
    int i,j,r=3,c=4,cnt;
    int **M=malloc(r*sizeof(int));
    for(i=0; i<r; i++) M[i]=malloc(c*sizeof(int));
    FILE *fin= fopen("input.txt","r");
    if(fin==NULL) exit(-1);
    for(i=0; i<r; i++)
        for(j=0; j<c; j++)
            fscanf(fin,"%d ", &M[i][j]);

    cnt=f(M,r,c);
    printf("N square submatrices = %d\n", cnt);
    return 0;
}
