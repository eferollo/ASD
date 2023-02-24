#include "nTREE.h"

typedef struct node *link;

struct node{
    char *key;
    link children[N];
};

struct binarytree{
    struct node *root;
};

link NEW(char *key){
    struct node *x=malloc(sizeof(*x));
    x->key=malloc(sizeof(char));
    strcpy(x->key,key);
    int i;
    for(i=0; i<N; i++) x->children[i]=NULL;
    return x;
}

void insertR(link node, int parent, char vett[][2], int dim){
    int i,j;
    int child1=N*parent+1;
    if(child1>dim)
        return;

    for(i=0, j=child1; i<N && j<child1+N && j<dim; i++, j++){
        if(strcmp(vett[j],"*")==0)
            continue;
        node->children[i]=NEW(vett[j]);
        insertR(node->children[i],j,vett,dim);
    }
}

nTREE init(){
    nTREE tree=malloc(sizeof (*tree));
    char vett[][2]={"A","B","C","D",
                    "E","F","*","*","G","*", "H","I","*",
                    "L","M","N","*","*","*","*","*","*",
                    "*","*","*","Z","*","Y"};
    tree->root=NEW(vett[0]);
    insertR(tree->root, 0, vett, 28);
    return tree;
}

void pathR(link h, int k, int *n, int *path){
    if(h==NULL){
        return;
    }

    if(k%2 != 0)
        path[(*n)++]=k;
    int i;
    for(i=0; i<N; i++){
        pathR(h->children[i],k+1,n,path);
    }
}

void findOddPath(nTREE t){
    int n=0;
    int *path=calloc(100,sizeof(int));
    pathR(t->root,0,&n,path);
    for(int i=0; i<100; i++)
        if(path[i]!=0)
            printf("%d ", path[i]);
}

