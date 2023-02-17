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

void doubleTree(struct node *root){
    if(root==NULL)
        return;

    struct node *tl;
    tl=root;
    tl->left=NEW(root->key,root->left,NULL);

    doubleTree(root->left->left);
    doubleTree(root->right);
}

int main() {
    FILE *fp;
    fp=fopen("input.txt","r");
    if(fp==NULL) exit(-1);

    int key;
    struct node *root=NULL;
    while(fscanf(fp,"%d",&key)!=EOF)
        root= insertR(root,key);
    fclose(fp);

    doubleTree(root);
    return 0;
}