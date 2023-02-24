#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

int main() {
    FILE *fp=fopen("input.txt","r");
    FILE *fp2=fopen("input2.txt","r");
    if(fp==NULL) exit(-1);
    int key,x;

    BST bst=BSTinit();
    while(fscanf(fp,"%d ", &key)!=EOF)
        BSTinsert(bst,key);
    //x=oneChildCount(bst);
    //findLeafMinHeight(bst);
    //deleteFromLevel(bst,2);
    //x=countLR(bst);
    //x= findMax(bst);
    BST bst2=BSTinit();
    while(fscanf(fp2,"%d ", &key)!=EOF)
        BSTinsert(bst2,key);
    //x=isSubTree(bst2,bst);
    //freeBST(bst);
    BSTinsert_root(bst,50);
    return 0;
}
