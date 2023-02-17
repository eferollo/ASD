#include <stdio.h>
#include <stdlib.h>



struct node {
    int key;
    struct node *left;
    struct node *right;
};

typedef int Key;

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

int KEYcmp(Key k1, Key k2){
    return k1==k2;
}

int TREEisomorph(struct node *t1, struct node *t2){
    if(t1==NULL && t2==NULL)
        return 1;
    else if((t1==NULL && t2!=NULL) || (t1!=NULL && t2==NULL))
        return 0;

    int exit=0;
    if(KEYcmp(t1->key,t2->key)){
        exit=TREEisomorph(t1->left,t2->left);
        if(exit==0)
            return exit;
        exit=TREEisomorph(t1->right,t2->right);
        if(exit==0)
            return exit;
    }
    return exit;
}

int main() {
    FILE *fp,*fp2;
    fp=fopen("input.txt","r");
    fp2=fopen("input1.txt","r");
    if(fp==NULL) exit(-1);
    if(fp2==NULL) exit(-1);

    int key;
    struct node *t1=NULL;
    struct node *t2=NULL;
    while(fscanf(fp,"%d",&key)!=EOF)
        t1= insertR(t1,key);
    while(fscanf(fp2,"%d",&key)!=EOF)
        t2= insertR(t2,key);
    fclose(fp);
    fclose(fp2);

    printf("%d",TREEisomorph(t1,t2));
    return 0;
}