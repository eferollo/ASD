#include "nTREE.h"

struct node{
    char *key;
    struct node *children[N];
};

struct binarytree{
    struct node *root;
};

static struct node *NEW(char *key){
    struct node *x=malloc(sizeof(*x));
    x->key=malloc(sizeof(char));
    strcpy(x->key,key);
    int i;
    for(i=0; i<N; i++) x->children[i]=NULL;
    return x;
}

void insertR(struct node *node, int parent, char vett[][2], int dim){
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

int searchR(struct node *h, int pcount, int *cnt){
    if(h==NULL)
        return 0;
    int i,n=0,count=0;

    for(i=0; i<N; i++)
        if(h->children[i]!=NULL)
            n++;
    for(i=0; i<N; i++)
        count+=searchR(h->children[i],n,cnt);

    if(count>pcount)
        (*cnt)++;
    return 1;
}

int countIf(nTREE t){
    int cnt=0;
    searchR(t->root,1,&cnt);
    return cnt;
}




