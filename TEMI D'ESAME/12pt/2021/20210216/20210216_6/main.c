#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void solve(char *start, char *end, char **dict, int n, int k){

}

int main() {
    int i;
    char **dict=malloc(26*sizeof(char *));
    for(i=0; i<26; i++) dict[i]=malloc(sizeof(char));
    for(i=65; i<=90; i++) dict[i-65][0]=(char)i;


    return 0;
}