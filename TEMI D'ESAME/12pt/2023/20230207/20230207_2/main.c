#include <stdio.h>
#include <stdlib.h>

void print(float **M, int r, int c){
    int i,j;
    for(i=0; i<r;i++){
        for(j=0; j<c; j++){
            printf("%.2f ",M[i][j]);
        }
        printf("\n");
    }
}

float avg(int **M, int r , int c, int li, int lj, int ri, int rj){
    int i,j,cnt=0,sum=0;
    float avg;

    if(li<0) li=0;
    if(ri==r) ri=r-1;
    if(lj<0) lj=0;
    if(rj==c) rj=c-1;

    for(i=li; i<=ri; i++)
        for(j=lj; j<=rj; j++){
            sum+=M[i][j];
            cnt++;
        }
    avg=(float)sum/(float)cnt;
    return avg;
}
void f(int **M, int r, int c, float **M1){
    int i,j;
    float val;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            val=avg(M,r,c,i-1,j-1,i+1,j+1);
            M1[i][j]=val;
        }
    }
}

int main() {
    int i,j,r=3,c=3;
    int **M=malloc(r*sizeof(int *));
    for(i=0; i<r; i++) M[i]=malloc(c*sizeof(int));
    FILE *fin= fopen("input.txt","r");
    if(fin==NULL) exit(-1);
    for(i=0; i<r; i++)
        for(j=0; j<c; j++)
            fscanf(fin,"%d ", &M[i][j]);

    float **M1=malloc(r*sizeof(float *));
    for(i=0; i<r; i++) M1[i]=malloc(c*sizeof(float));
    f(M,r,c,M1);
    print(M1,r,c);
    fclose(fin);
    return 0;
}
