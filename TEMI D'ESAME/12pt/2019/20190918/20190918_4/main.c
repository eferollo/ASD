#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxC 10

typedef struct node_t *linkT;

struct node_t{
    char key[maxC];
    linkT l,r;
};

typedef struct node_l *linkL;

struct node_l{
    char key[maxC];
    linkL next;
};

static linkT NEW(char *key, linkT l, linkT r){
    linkT x=malloc(sizeof(*x));
    if(x==NULL)
        return NULL;
    strcpy(x->key,key);
    x->l=l;
    x->r=r;
    return x;
}

static linkT insertR(linkT h, char *key){
    if(h==NULL)
        return NEW(key,NULL,NULL);
    if(strcmp(key,h->key)<0)
        h->l= insertR(h->l,key);
    if(strcmp(key,h->key)>0)
        h->r= insertR(h->r, key);
    return h;
}

linkT BSTinsert(linkT root, char *key){
    return insertR(root,key);
}

static linkL newNode(char *key, linkL next){
    linkL h=malloc(sizeof(*h));
    if(h==NULL)
        return NULL;
    strcpy(h->key,key);
    h->next=next;
    return h;
}

linkL ListIns(linkL h, char *key){
    linkL x,p;
    if(h==NULL)
        return newNode(key,NULL);

    for(x=h->next, p=h; x!=NULL; p=x, x=x->next);
    p->next= newNode(key,x);
    return h;
}

void inorder(linkT x, char **nodes, int *i){
    if(x==NULL)
        return ;
    inorder(x->l,nodes,i);
    nodes[++(*i)]=x->key;
    inorder(x->r,nodes,i);
}

void preorder(linkT x, char **nodes, int *i){
    if(x==NULL)
        return;
    nodes[++(*i)]=x->key;
    inorder(x->l,nodes,i);
    inorder(x->r,nodes,i);
}

void postorder(linkT x, char **nodes, int *i){
    if(x==NULL)
        return;
    inorder(x->l,nodes,i);
    inorder(x->r,nodes,i);
    nodes[++(*i)]=x->key;
}

int count(linkT root){
    if(root==NULL)
        return 0;
    return count(root->l) + count(root->r)+1;
}

linkL generateList(char **nodes, int n, linkL head){
    int i;
    for(i=0; i<n; i++)
        head=ListIns(head,nodes[i]);
    return head;
}

linkL tree2List(linkT root, int visit){
    linkL head=NULL;
    int n=count(root), i=-1,j;
    char **nodes=malloc(n*sizeof (char *));
    for(j=0; j<n; j++) nodes[j]=malloc(maxC*sizeof(char));

    if(visit==1){
        inorder(root,nodes,&i);
        head=generateList(nodes,n,head);
    }else if(visit==2){
        preorder(root,nodes,&i);
        head= generateList(nodes,n,head);
    }else{
        postorder(root,nodes,&i);
        head= generateList(nodes,n,head);
    }
    return head;
}

void print(linkL h){
    linkL x;
    for(x=h; x!=NULL; x=x->next)
        printf("%s ", x->key);
}

int main() {
    linkT root=NULL;
    linkL head=NULL;
    FILE *fp;
    fp= fopen("input.txt","r");
    if(fp==NULL) exit(-1);
    char str[maxC];

    while(fscanf(fp,"%s\n", str)!=EOF)
        root= BSTinsert(root,str);

    head= tree2List(root,3);
    print(head);
    return 0;
}