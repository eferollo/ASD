#include <stdio.h>
#include <stdlib.h>

int isvowel(char c){
    if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u')
        return 1;
    return 0;
}

void change(char **M, int r, int c, int il, int jr){
    int i;
    for(i=0; i<c; i++)
        M[il][i]='*';
    for(i=0; i<r; i++)
        M[i][jr]='*';
}

void f(char **M, int r, int c, char ***M1, int *r1, int *c1) {
    int i,j,cnt=0;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            if(isvowel(M[i][j])){
                change(M,r,c,i,j);
                cnt++;
            }
        }
    }

    if(cnt>0){
        *r1=r-cnt;
        *c1=c-cnt;
        char **M11=malloc((*r1)*sizeof(char *));
        for(i=0; i<*r1; i++) M11[i]=malloc((*c1)*sizeof(char));
        int it=0,jt=0;

        for(i=0; i<r; i++){
            for(j=0; j<c; j++){
                if(M[i][j]!='*')
                    M11[it][jt++]=M[i][j];
            }
            if(jt>0) it++;
            jt=0;
        }
        *M1=M11;
    }

}

int main() {
    int i,j,r=4,c=5;
    char **M=malloc(r*sizeof(char *));
    for(i=0; i<r; i++) M[i]=malloc(c*sizeof(char));
    FILE *fin= fopen("input.txt","r");
    if(fin==NULL) exit(-1);
    for(i=0; i<r; i++)
        for(j=0; j<c; j++)
            fscanf(fin,"%c ", &M[i][j]);

    char **M1;
    int r1,c1;
    f(M,r,c,&M1,&r1,&c1);

    for(i=0; i<r1; i++){
        for(j=0; j<c1; j++){
            printf("%c ", M1[i][j]);
        }
        printf("\n");
    }
    return 0;
}
