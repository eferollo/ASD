#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct coppia_{
    char *scelta_A;
    char *scelta_B;
}coppia;

char get_c(char f, int i){
    if(i==0){
        if(f=='a') return 'R';
        else return 'R';
    }
    else if(i==1){
        if(f=='a') return 'R';
        else return 'C';
    }
    else if(i==2){
        if(f=='a') return 'C';
        else return 'R';
    }
    else if(i==3){
        if(f=='a') return 'C';
        else return 'C';
    }
    return '*';
}

int calc(int **A, int nA, int **B, int nB, int *aind, int *bind, int opt, int *best){
    int i,j,k,z;
    int val_A=0, val_B=0, sum, min=INT_MAX;

    for(i=0; i<nA; i++){
        for(j=0; j<nA; j++){
            if(opt==0 || opt==1)
                val_A+=A[i][j];
            else if(opt==2 || opt==3)
                val_A+=A[j][i];
        }
        for(k=0; k<nB; k++){
            for(z=0; z<nB; z++){
                if(opt==0 || opt==2)
                    val_B+=B[k][z];
                else if(opt==1 || opt==3)
                    val_B+=B[z][k];
            }
            sum=abs(val_A+val_B);
            if(sum<min){
                min=sum;
                if(opt==0){
                    *aind=i; *bind=k;
                }else if(opt==1){
                    *aind=i; *bind=z;
                }else if(opt==2){
                    *aind=j-1; *bind=k;
                }else if(opt==3){
                    *aind=j-1; *bind=z;
                }
            }
            val_B=0;
        }
        val_A=0;
    }
    if(min<*best){
        *best=min;
        return opt;
    }
}

coppia mySum(int **A, int nA, int **B, int nB){
    int dim=4,max=2,i;
    coppia *c=malloc(dim*sizeof(*c));
    for(i=0;i<dim;i++){
        c[i].scelta_A=malloc(max*sizeof(char));
        c[i].scelta_B=malloc(max*sizeof(char));
    }
    int a,b,best=INT_MAX, pos;
    for(i=0; i<dim;i++){
        pos=calc(A,nA,B,nB,&a,&b,i,&best);
        c[i].scelta_A[0]= get_c('a',i); c[i].scelta_A[1]=(char)(a+'0');
        c[i].scelta_B[0]=get_c('b',i); c[i].scelta_B[1]=(char)(b+'0');
    }
    return c[pos];
}

int main() {
    FILE *fin;
    fin=fopen("input.txt","r");
    if(fin==NULL) exit(-1);
    int i,j,nA=3, nB=2;

    int **A=malloc(nA * sizeof(int *));
    for(i=0; i < nA; i++) A[i]=malloc(nA * sizeof (int));
    int **B=malloc(nB * sizeof(int *));
    for(i=0; i < nB; i++) B[i]=malloc(nB * sizeof (int));

    for(i=0; i < nA; i++)
        for(j=0; j < nA; j++)
            fscanf(fin,"%d ", &A[i][j]);
    for(i=0; i < nB; i++)
        for(j=0; j < nB; j++)
            fscanf(fin,"%d ", &B[i][j]);
    fclose(fin);

    coppia sol=mySum(A,nA,B,nB);
    printf("(%s, %s)", sol.scelta_A,sol.scelta_B);

    return 0;
}
