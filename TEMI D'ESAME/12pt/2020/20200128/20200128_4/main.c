#include <stdio.h>
#include <stdlib.h>

typedef struct node* link;

struct node {
    int item;
    link left;
    link right;
};

link NEW(int chiave, link left, link right) {
    link x = malloc(sizeof *x);
    x->item = chiave;
    x->left = left;
    x->right = right;
    return x;
}

link insertTree(link h, int chiave){
    if(h==NULL)
        return NEW(chiave,NULL,NULL);

}

link buildTree(int *inorder, int *preorder, int N){
    int i,j=0;
    link x;
    for(i=0; i<N; i++){
        while(inorder[j]==preorder[i])
            j++;
        x= insertTree(x,inorder[j]);
        
    }
}

int main() {
    int preorder[]={100, 10, 55,25, 13, 3, 30, 14, 0, 20, 90};
    int inorder[]={10, 100, 13, 25, 3, 55, 0, 14, 20, 30, 90};
    link root= buildTree(inorder, preorder, 11);
    return 0;
}
