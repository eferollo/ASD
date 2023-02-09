#include <stdio.h>

void swap(int *a,int *b);
int gcd(int a, int b);
int odd(int x);

int main() {
    int a,b;
    printf("Insert a and b: ");
    scanf("%d %d",&a,&b);
    printf("GCD is %d",gcd(a,b));
    return 0;
}

void swap(int *a,int *b){
    int tmp;
    tmp=*a;
    *a=*b;
    *b=tmp;
}

int odd(int x){
    if(x%2!=0)
        return 1;
    else return 0;
}

int gcd(int a, int b){
    if(a==b) return a;
    if(a<b) swap(&a,&b);
    if(!odd(a) && !odd(b))
        return 2*gcd(a/2,b/2);
    if(odd(a) && !odd(b))
        return gcd(a,b/2);
    if(!odd(a) && odd(b))
        return gcd(a/2,b);
    if(odd(a) && odd(b))
        return gcd((a-b)/2,b);
}