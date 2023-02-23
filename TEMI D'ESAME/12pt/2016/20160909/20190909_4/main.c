#include <stdio.h>
#include <stdlib.h>
#define N 7

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

int distance (struct node *root, int key1, int key2){

}

void LISprint(int *val, int *P, int i) {
    if (P[i]==-1) {
        printf("%d ", val[i]);
        return;
    }
    LISprint(val, P, P[i]);
    printf("%d ", val[i]);
}

void LISDP(int *val) {
    int i, j, ris = 1, L[N], P[N], last = 1;
    L[0] = 1;
    P[0] = -1;
    for (i = 1; i < N; i++) {
        L[i] = 1;
        P[i] = -1;
        for (j = 0; j < i; j++)
            if ((val[j] < val[i]) && (L[i] < 1 + L[j])) {
                L[i] = 1 + L[j];
                P[i] = j;
            }
        if (ris < L[i]) {
            ris = L[i];
            last = i;
        }
    }

    for(i=0; i<N;i++)
        printf("%d\t", L[i]);
    printf("\n");
    for(i=0; i<N;i++)
        printf("%d\t", P[i]);

    printf("\nOne of the Longest Increasing Sequences is (");
    LISprint(val, P, last);
    printf(") and its length is %d\n", ris);
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

    int res= distance(root,20,11);
    int val[]={2,1,8,4,12,13,11};
    LISDP(val);
    return 0;
}