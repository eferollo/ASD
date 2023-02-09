#include <stdio.h>
#include <stdlib.h>

#define K 3

typedef struct node node_t;
typedef node_t *link;

struct node{
    int i;
    float wi;
    link children[K];
};

int maxSum(link root, int *maxwt);

int main(){
    node_t n0={0,15.2};
    node_t n1={1, -8.1};
    node_t n2={2,3};
    node_t n3={3,7.27};
    node_t n4={4,-20.9};
    node_t n5={5,-4};
    node_t n6={6,5.3};
    node_t n7={7,-10.8};
    node_t n8={8,2.4};
    node_t n9={9,-5};
    node_t n10={10,-3.1};
    node_t n11={11,2};
    node_t n12={12,2.8};

    n0.children[0]=&n1;
    n0.children[1]=&n2;
    n0.children[2]=&n3;
    n1.children[0]=&n4;
    n1.children[2]=&n5;
    n2.children[1]=&n6;
    n3.children[1]=&n7;
    n6.children[0]=&n8;
    n6.children[2]=&n9;
    n7.children[0]=&n10;
    n7.children[1]=&n11;
    n7.children[2]=&n12;

}

int maxSum(link root, int *maxwt){
    int i, id,t;
    float s;

    id=root->i;

    for(i=0; i<K; i++){
        s = *maxwt;
        t = maxSum(root->children[i], maxwt);
        if(*maxwt > s)
            id=t;
    }
    return id;
}