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
    BST bst2=BSTinit();
    while(fscanf(fp2,"%d ", &key)!=EOF)
        BSTinsert(bst2,key);
    BST sumBst=getBSTforSumtest();
    //x=oneChildCount(bst);
    //findLeafMinHeight(bst);
    //deleteFromLevel(bst,2);
    //x=countLR(bst);
    //x= findMax(bst);
    //x=isSubTree(bst2,bst);
    //BSTinsert_root(bst,50);
    //x=isSumTree(sumBst);
    //freeBST(bst);
    //x=countCompleteNodes(bst);
    //x= greatherNodes(bst2, 1, 3, 2);
    //x=nLeaf(bst,4);
    return 0;
}
