#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *left;
    struct node *right;
};

struct node *NEW(int key, struct node *left, struct node *right){
    struct node *x=malloc(sizeof(*x));
    x->key=key;
    x->right=right;
    x->left=left;
    return x;
}

struct node *insertR(struct node *h, int key) {
    if (h == NULL)
        return NEW(key, NULL, NULL);
    if (key < h->key)
        h->left = insertR(h->left, key);
    else if (key > h->key)
        h->right = insertR(h->right, key);
    return h;
}

void printPaths(struct node *root, int h, struct node **path, int pos, int *flag){
    int i;
    if(root==NULL && (*flag)){
        (*flag)=0;
        return;
    }
    if(root==NULL && !(*flag)){
        for(i=0; i<pos; i++)
                printf("%d ", path[i]->key);
        printf("\n--------------\n");
        (*flag)=1;
        return;
    }

    path[pos]=root;
    printPaths(root->left,h,path,pos+1,flag);
    printPaths(root->right,h,path,pos+1,flag);
}

int main() {
    FILE *fp;
    fp=fopen("input.txt","r");
    if(fp==NULL) exit(-1);

    int i,key,h=5;
    struct node *root=NULL;
    while(fscanf(fp,"%d",&key)!=EOF)
        root= insertR(root,key);
    struct node **path=malloc(h*sizeof (path));
    for(i=0; i<h; i++)
        path[i]=NULL;
    int flag=0;
    printPaths(root,h,path,0,&flag);
    free(path);
    return 0;
}
