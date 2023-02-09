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

link build(int *inorder, int *preorder, int li, int ri, int *index){
    if(li>ri)
        return NULL;
    int i;
    link x= NEW(preorder[(*index)++],NULL,NULL);

    for(i=li; i<=ri; i++){
        if(inorder[i]==x->item)
            break;
    }

    x->left= build(inorder,preorder,li,i-1,index);
    x->right= build(inorder,preorder,i+1,ri, index);
    return x;
}
link buildTree(int *inorder, int *preorder, int N){
    int index=0;
    return build(inorder,preorder,0,N-1, &index);
}

int main() {
    int preorder[]={100, 10, 55,25, 13, 3, 30, 14, 0, 20, 90};
    int inorder[]={10, 100, 13, 25, 3, 55, 0, 14, 20, 30, 90};
    link root= buildTree(inorder, preorder, 11);
    return 0;
}
