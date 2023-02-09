#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node{
    char key;
    link next;
    link prev;
};

link newNode(char key, link next,link prev){
    link x=malloc(sizeof(*x));
    if(x==NULL)
        return NULL;
    x->key=key;
    x->next=next;
    x->prev=prev;
    return x;
}

link insList(link h, char key){
    link x,p;
    if(h==NULL)
        return newNode(key,h,NULL);
    for(x=h->next, p=h; x!=NULL; p=x, x=x->next);
    p->next= newNode(key,x,p);

    return h;
}

link purgeList(link head1){
    link head2=NULL;
    link x;
    int flag=0;
    for(x=head1; x!=NULL; x=x->next){
        if(x->key==')' || (x->prev!=NULL && x->prev->key==')')) flag=0;
        if(x->prev !=NULL && x->prev->key=='(')
            head2=insList(head2,'*');
        if(flag==0)
            head2=insList(head2,x->key);
        if(x->key=='(') flag=1;
    }
    return head2;
}

int main() {
    link head1=NULL;
    FILE *fin;
    fin= fopen("input.txt","r");
    if(fin==NULL) exit(-1);

    char c;
    while(fscanf(fin,"%c\n", &c)==1)
        head1=insList(head1,c);

    link head2= purgeList(head1);

    return 0;
}
