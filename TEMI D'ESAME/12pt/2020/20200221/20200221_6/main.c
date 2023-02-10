#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int charcmp(char *str1, char *str2){
    int i,j;
    for(i=0; i<strlen(str1); i++){
        for(j=0; j<strlen(str2); j++)
            if(str2[j]==str1[i])
                return 0;
    }
    return 1;
}

int check(int *sol, char **stringhe, int n, int k){
    int i,j;
    for(i=0; i<k-1; i++){
        for(j=i+1; j<k; j++){
            if(!charcmp(stringhe[sol[i]],stringhe[sol[j]]))
                return 0;
        }
    }
    return 1;
}

void powerset(int pos, char **stringhe, int *set, int *sol, int k, int n, int start, int *stop){
    int i;
    if(pos==k){
        if(check(sol,stringhe,n,k)){
            for(i=0; i<k; i++)
                printf("%s ", stringhe[sol[i]]);
            *stop=1;
        }
        return;
    }
    for(i=start; i<n; i++){
        if(!*stop){
            sol[pos]=set[i];
            powerset(pos+1,stringhe,set,sol,k,n,i+1,stop);
        }else
            return;
    }
}

int disgiunte(char **stringhe, int n){
    int i,stop=0;
    int *set=malloc(n*sizeof(int));
    int *sol=malloc(sizeof(int));
    for(i=0; i<n; i++) set[i]=i;
    for(i=n; i>1 && stop==0; i--){
        sol=realloc(sol,i*sizeof (int));
        powerset(0,stringhe,set,sol,i,n,0,&stop);
    }
    free(set);
    free(sol);
    return i+1;
}

int main() {
    int i,n;
    char *str;
    FILE *fp;
    fp=fopen("input.txt","r");
    if(fp==NULL) exit(-1);

    fscanf(fp,"%d", &n);
    char **set=malloc(n*sizeof(char *));
    for(i=0; i<n; i++){
        fscanf(fp,"%s", str);
        set[i]=malloc(sizeof(char));
        strcpy(set[i],str);
    }
    fclose(fp);
    printf("Stringhe mutualmente disgiunte:\n");
    printf("\n%d", disgiunte(set,n));
    return 0;
}
