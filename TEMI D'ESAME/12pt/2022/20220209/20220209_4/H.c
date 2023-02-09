#include "H.h"

typedef struct node *link;

struct node{
    link l,r;
    Item val;
};

struct minHeap{
    int heapsize;
    link *pnodes;
};

static link NEW(char letter, int freq){
    link x=malloc(sizeof(*x));
    x->l=NULL;
    x->r=NULL;
    x->val=ITEMload(letter,freq);;

    return x;
}

H Hinit(){
    H h=malloc(sizeof (*h));
    h->heapsize=0;
    h->pnodes=malloc(100*sizeof(link*));
    return h;
}

void insertMinHeap(H h, link node){
    h->heapsize++;
    int i=h->heapsize-1;

    while(i && KEYget(node->val) < KEYget(h->pnodes[(i-1)/2]->val)){
        h->pnodes[i]=h->pnodes[(i-1)/2];
        i=(i-1)/2;
    }

    h->pnodes[i]=node;
}

void swap(link *a, link *b){
    link t = *a;
    *a=*b;
    *b=t;
}

void Heapify(H h, int i){
    int l,r, smallest;

    smallest=i;
    l= 2*i + 1;
    r= 2*i + 2;
    if(l < h->heapsize && KEYget(h->pnodes[l]->val) < KEYget(h->pnodes[smallest]->val))
        smallest=l;

    if(r < h->heapsize && KEYget(h->pnodes[r]->val) < KEYget(h->pnodes[smallest]->val))
        smallest=r;

    if(smallest != i){
        swap(&h->pnodes[smallest], &h->pnodes[i]);
        Heapify(h,smallest);
    }
}

void BuildHeap(H h){
    int i;
    for(i=(h->heapsize)/2-1; i>=0; i--)
        Heapify(h,i);
}

void newHeap(H h,FILE *fp){
    int i,size, freq;
    char letter;

    fscanf(fp,"%d\n", &size);
    for(i=0; i<size; i++){
        fscanf(fp,"%c:%d\n", &letter, &freq);
        h->pnodes[i]=NEW(letter,freq);
    }
    fclose(fp);

    h->heapsize=size;
    BuildHeap(h);
}

link extractMin(H h){
    link tmp= h->pnodes[0];
    h->pnodes[0]=h->pnodes[h->heapsize-1];

    h->heapsize--;
    Heapify(h,0);

    return tmp;
}

link encode(H h){
    link l,r,root;

    while(h->heapsize>1){
        l=extractMin(h);
        r=extractMin(h);
        root=NEW('!', KEYget(l->val)+KEYget(r->val));
        root->l=l;
        root->r=r;
        insertMinHeap(h,root);
    }
    root=extractMin(h);
    return root;
}

void HuffHeapEncode(H h){
    link root= encode(h);
}

char *decode(H h, char *str){
    link root=h->pnodes[0];
    link x=root;
    int i;
    char *word=malloc(sizeof(char));
    word[0]='\0';
    for(i=0; i<strlen(str); i++){
        if(str[i]=='0')
            x=x->l;
        else
            x=x->r;

        if(x->l == NULL && x->r == NULL){
            strncat(word,&x->val.c,1);
            x=root;
        }
    }
    return word;
}

