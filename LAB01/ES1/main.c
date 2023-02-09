#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *brackets(char *regexp,int index);
char *notAlpha(char *regexp, char *src, int *n);
char *cercaRegexp(char *src, char *regexp);

int main() {
    char *str="prova";
    str=cercaRegexp("AannRad","A[^f]\\anR.d");
    return 0;
}

char *brackets(char *regexp,int index){
    char *exp=(char *)malloc(strlen(regexp)*sizeof(char));
    for(int i=index;i< strlen(regexp) && regexp[i]!=']';i++)
        exp[i-index]=regexp[i];
    return exp;
}

char *notAlpha(char *regexp, char *src, int *n){
    char *exp;
    int i,found=1;
    if(regexp[0]=='[' && regexp[1]!='^'){
        exp=brackets(regexp,1);
        *n=strlen(exp)+1;
        for(i=0;i<strlen(exp);i++){
            if(src[0]==exp[i])
                return &src[0];
            else found=0;
        }
        if(!found) return NULL;
    }else if(regexp[0]=='[' && regexp[1]=='^'){
        exp=brackets(regexp,2);
        *n=strlen(exp)+2;
        for(i=0;i<strlen(exp);i++){
            if(src[0]!=exp[i])
                return &src[0];
            else found=0;
        }
        if(!found) return NULL;
    }else if(regexp[0]=='\\'){
        *n=0;
        if(islower(regexp[1])){
            if(islower(src[0]))
                return &src[0];
            else return NULL;
        }else{
            if(isupper(src[0]))
                return &src[0];
            else return NULL;
        }
    }else if(regexp[0]=='.'){
        *n=0;
        if(src[0]!='\0') return &src[0];
        else return NULL;
    }
}

char *cercaRegexp(char *src, char *regexp){
    int i,n;
    char *start,*check;
    for(i=0; i<strlen(regexp) && start!=NULL && check!=NULL; i++){
        if(i>0){
            if(isalpha(regexp[i]))
                check=strchr(check+1,regexp[i]);
            else{
                check=notAlpha(&regexp[i],check+1,&n);
                i+=n;
            }
        }else{
            if(isalpha(regexp[i])){
                start=strchr(src,regexp[i]);
                check=start;
            }
            else{
                start=notAlpha(&regexp[i],src,&n);
                check=start;
                i+=n;
            }
        }
    }
    if(start!=NULL && check!=NULL) return &start[0];
    else return NULL;
}