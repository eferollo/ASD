#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 3

struct node{
    int key;
    struct node *children[N];
};

struct node *NEW(int key){
    struct node *x=malloc(sizeof(*x));
    x->key=key;
    int i;
    for(i=0; i<N; i++)
        x->children[i]=NULL;
    return x;
}

void insertR(struct node *h, int parent, int *vett, int dim){
    int i,j;
    int child1=N*parent+1;
    if(child1>dim)
        return;

    for(i=0, j=child1; i<N && j<child1+N && j<dim; i++, j++){
        if(vett[j]==INT_MIN)
            continue;
        h->children[i]=NEW(vett[j]);
        insertR(h->children[i],j,vett,dim);
    }
}

struct node *init(){
    int vett[]={10,1,-2,5,
                6,INT_MIN,1,5,-9,4,3,1,7,
                5,12};
    struct node *root;
    root= NEW(vett[0]);
    insertR(root,0,vett,15);
    return root;
}

void visitR(struct node *h, int l1, int l2, int curr_l){
    if(h==NULL)
        return;

    int i;
    if(curr_l>=l1 && curr_l<=l2){
        printf("%d ", h->key);
        return;
    }

    for(i=0; i<N; i++)
        visitR(h->children[i],l1,l2,curr_l+1);
}

void visitLevelByLevel(struct node *root, int l1, int l2){
    int i;
    int curr_l=0;
    for(i=0; i<l2; i++){
        visitR(root,l1,l2,curr_l--);
        printf("\n");
    }
}

int main() {
    struct node *root=init();
    visitLevelByLevel(root,1,2);
    return 0;
}
