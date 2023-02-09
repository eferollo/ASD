#include <stdio.h>
#include <stdlib.h>
#define filename "mat.txt"

int **malloc2dR(FILE *fp, int *nr, int *nc);
void malloc2dP(FILE *fp, int ***mat, int *nr, int *nc);
void separa(int **mat, int nr, int nc, int *vb, int *vn, int *d1, int *d2);
void printM(int **mat, int nr, int nc);
void freeMat(int **mat, int nr);

int main() {
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("Error while opening file\n");
        exit(-1);
    }

    int **mat,nr,nc,*vb,*vn,d1,d2,i,j;
    mat=malloc2dR(fp,&nr,&nc);
    //malloc2dP(fp,&mat,&nr,&nc);
    printM(mat,nr,nc);

    int max=(nr*nc/2)+1;
    vb=(int *)malloc(max*sizeof(int));
    vn=(int *)malloc(max*sizeof(int));

    separa(mat,nr,nc,vb,vn,&d1,&d2);
    printf("White cells:\n");
    for(i=0;i<d1;i++) printf("%d ", vb[i]);
    printf("\n");
    printf("Black cells:\n");
    for(i=0;i<d2;i++) printf("%d ", vn[i]);
    printf("\n");

    freeMat(mat,nr);
    free(vb);
    free(vn);
    return 0;
}

void malloc2dP(FILE *fp, int ***mat, int *nr, int *nc){
    int i,j;
    fscanf(fp,"%d %d", nr,nc);
    int **m=(int **)malloc(*nr*sizeof(int **));
    for(i=0;i<*nr;i++)
        m[i]=(int *)malloc(*nc*sizeof(int));
    for(i=0;i<*nr;i++)
        for(j=0;j<*nc;j++)
            fscanf(fp,"%d",&m[i][j]);
    *mat=m;
    fclose(fp);
}
int **malloc2dR(FILE *fp, int *nr, int *nc){
    int **mat,i,j;
    fscanf(fp,"%d %d", nr,nc);
    mat=(int **)malloc(*nr*sizeof(int *));
    for(i=0;i<*nr;i++)
        mat[i]=(int *)malloc(*nc*sizeof(int));
    for(i=0;i<*nr;i++)
        for(j=0;j<*nc;j++)
            fscanf(fp,"%d",&mat[i][j]);
    fclose(fp);
    return mat;
}

void separa(int **mat, int nr, int nc, int *vb, int *vn, int *d1, int *d2){
    int i,j,k=0,x=0;
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if(i%2==0){
                if(j%2==0)
                    vb[k++]=mat[i][j];
                else
                    vn[x++]=mat[i][j];
            }else{
                if(j%2==0)
                    vn[x++]=mat[i][j];
                else
                    vb[k++]=mat[i][j];
            }
        }
    }
    *d1=k;
    *d2=x;
}

void printM(int **mat, int nr, int nc){
    int i,j;
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++)
            printf("%d ",mat[i][j]);
        printf("\n");
    }
    printf("\n");
}
void freeMat(int **mat, int nr){
    for(int i=0;i<nr;i++)
        free(mat[i]);
    free(mat);
}
