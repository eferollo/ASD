#include <stdio.h>
#include <stdlib.h>

void remove_dup(int *v, int *n){
    int i,j=1, curr;
    for(i=1; i<*n; i++)
        if(v[i] != curr){
            curr=v[i];
            v[j++]=v[i];
        }
    *n=j;
}

int *f(int *v1, int *v2, int dim1, int dim2, int *dim3){
    int i,j,cnt=0,k;
    int *v3=malloc(sizeof(int));

    remove_dup(v1,&dim1);
    remove_dup(v2,&dim2);

    for(i=0; i<dim2; i++){
        for(j=0; j<dim1; j++){
            if(v1[j]!=v2[i] && v1[j]<v2[i]){
                for(k=0;k<i; k++){
                    if(v1[j]>v2[k]){
                        cnt++;
                        realloc(v3,cnt*sizeof (int));
                        v3[cnt-1]=v1[j];
                    }
                }
            }
            else if(i==dim2-1 && v1[j]>v2[i]){
                cnt++;
                realloc(v3,cnt*sizeof (int));
                v3[cnt-1]=v1[j];
            }
        }
    }
    *dim3=cnt;
    return v3;
}


int main() {
    int v1[6]={1,2,2,3,4,5};
    int v2[2]={1,3};
    int dim3,i;
    int *v3=f(v1,v2,6,2, &dim3);
    for(i=0; i<dim3;i++)
        printf("%d ",v3[i]);
    printf("  Dim: %d", dim3);
    return 0;
}
