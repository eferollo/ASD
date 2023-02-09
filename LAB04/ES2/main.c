#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define MAXC 6
#define MAXD 11

typedef struct{
    char code[MAXC];
    char name[MAX];
    char surname[MAX];
    char date[MAXD];
    char street[MAX];
    char city[MAX];
    int cap;
}Item;
typedef char *Key;

typedef struct node *link;
struct node{
    Item val;
    link next;
};

char *reverse(char *s);
int printOpts();
void startOpts(link head);
void printList(link h);
void searchByCode(link head);

Key KEYget(Item d, int opt);
int KEYeq(Key k1, Key k2);
int KEYgeq(Key k1, Key k2);

link newNode(Item val, link next);
link sortListIns(link h, Item val);
link insertByKeyboard(link head, Item tmp);
link insertByFile(link head, Item tmp);
link findFirst(link head, Key k);
link deleteByCode(link head);
link deleteByDate(link head);
link freeList(link h);

Item ITEMsetvoid(void);
Item listSearch(link h, Key k, int opt);
Item listExtrKeyP(link *hp, Key k);
Item sortListExtrKeyP(link *hp, Key k1, Key k2);


int main() {
    link head=NULL;
    startOpts(head);
    return 0;
}

char *reverse(char *s){
    char tmp[11];
    tmp[0]=s[6];tmp[1]=s[7];tmp[2]=s[8];tmp[3]=s[9];tmp[4]=s[2];
    tmp[5]=s[3];tmp[6]=s[4];tmp[7]=s[5];tmp[8]=s[0];tmp[9]=s[1];
    s=tmp;
    return s;
}

int KEYgeq(Key k1, Key k2){
    return strcmp(k1,k2)>=0;
}

int KEYeq(Key k1, Key k2){
    return strcmp(k1,k2);
}

Key KEYget(Item d, int opt){
    Key k;
    char date[MAXD];
    strcpy(date,reverse(d.date));
    if(opt==0) k=strdup(date);
    else if(opt==1) k=strdup(d.code);
    return k;
}

link newNode(Item val, link next){
    link x = malloc(sizeof *x);
    if(x==NULL)
        return NULL;
    x->val=val;
    x->next=next;
    return x;
}

link sortListIns(link h, Item val){
    link x,p;
    Key k= KEYget(val,0);
    if(h==NULL || !KEYgeq(KEYget(h->val,0),k))
        return newNode(val,h);
    for(x=h->next, p=h; x!=NULL && KEYgeq( KEYget(x->val,0),k); p=x, x=x->next);
    p->next = newNode(val,x);
    return h;
}

link insertByKeyboard(link head, Item tmp){
    printf("Inserisci una nuiva anagrafica nel formato:"
           " <codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>\n");
    scanf("%s%s%s%s%s%s%d", tmp.code, tmp.name, tmp.surname, tmp.date, tmp.street, tmp.city, &tmp.cap);
    head=sortListIns(head, tmp);
    return head;
}

link insertByFile(link head, Item tmp){
    FILE *fp;
    char filename[MAX];
    printf("Inserisci nome file: ");
    scanf("%s", filename);
    fp=fopen(filename, "r");
    if(fp==NULL){
        printf("Errore nell'apertura del file");
        return NULL;
    }
    while(fscanf(fp,"%s%s%s%s%s%s%d", tmp.code, tmp.name, tmp.surname, tmp.date, tmp.street, tmp.city, &tmp.cap)!=EOF)
        head=sortListIns(head, tmp);
    fclose(fp);
    return head;
}

Item ITEMsetvoid(void){
    Item k;
    strcpy(k.code,"\0");
    return k;
}

Item listSearch(link h, Key k, int opt){
    link x;
    for(x=h; x!=NULL; x=x->next)
        if(KEYeq(KEYget(x->val,opt),k)==0)
            return x->val;
    return ITEMsetvoid();
}

void searchByCode(link head){
    char code[MAXC];
    Item tmp;
    printf("Inserisci codice: ");
    scanf("%s", code);
    tmp= listSearch(head,code,1);
    if(strcmp(tmp.code,"\0")!=0)
        printf("%s %s %s %s %s %s %d", tmp.code, tmp.name, tmp.surname, tmp.date, tmp.street, tmp.city, tmp.cap);
    else printf("Elemento non trovato\n");
}

Item listExtrKeyP(link *hp, Key k){
    link *xp,t;
    Item i=ITEMsetvoid();
    for(xp=hp; (*xp)!=NULL; xp=&((*xp)->next)){
        if(KEYeq(KEYget((*xp)->val,1),k)==0){
            t=*xp;
            *xp=(*xp)->next;
            i=t->val;
            free(t);
            break;
        }
    }
    return i;
}

link findFirst(link head, Key k){
    link x;
    for(x=head; x!=NULL; x=x->next)
        if(KEYgeq(k,KEYget(x->val,0)))
            return x;
    return NULL;
}

Item sortListExtrKeyP(link *hp, Key k1, Key k2){
    link *xp,t;
    Item i=ITEMsetvoid();
    xp=hp;
    if((*xp)!=NULL){
        if(KEYgeq(KEYget((*xp)->val, 0),k1)){
            t=*xp;
            *xp=(*xp)->next;
            i=t->val;
            free(t);
        }
    }
    return i;
}

link deleteByCode(link head){
    char code[MAXC];
    Item tmp;
    printf("Inserisci codice: ");
    scanf("%s", code);
    tmp=listSearch(head,code,1);
    if(strcmp(tmp.code,"\0")!=0){
        tmp=listExtrKeyP(&head,code);
        printf("Elemento eliminato:\n");
        printf("%s %s %s %s %s %s %d", tmp.code, tmp.name, tmp.surname, tmp.date, tmp.street, tmp.city, tmp.cap);
    } else printf("Elemento non trovato\n");
    return head;
}

link deleteByDate(link head){
    char date1[MAXD], date2[MAXD];
    int cnt=0;

    printf("Inserisci un intervallo di date (gg/mm/aaaa gg/mm/aaaa):\n");
    scanf("%s %s", date1,date2);
    strcpy(date1,reverse(date1));
    strcpy(date2,reverse(date2));

    Item tmp;
    head=findFirst(head,date2);
    if(head!=NULL)
        while(1){
            tmp= sortListExtrKeyP(&head, date1, date2);
            if(strcmp(tmp.code,"\0")==0)
                break;
            printf("Elemento eliminato:\n");
            printf("%s %s %s %s %s %s %d\n", tmp.code, tmp.name, tmp.surname, tmp.date, tmp.street, tmp.city, tmp.cap);
            cnt++;
        }
    if(cnt==0) printf("Nessun elemento da eliminare trovato\n");
    return head;
}

link freeList(link h) {
    link x,p;
    for(x=h, p=NULL; x!=NULL; p=x, x=x->next){
        if(x==h)
            h=x->next;
        else
            p->next=x->next;
        free(x);
    }
    return h;
}

int printOpts(){
    int option;
    printf("\nSelezionare numero opzione:\n"
           "\t1. Acquisizione ed inserimento di un nuovo elemento (da tastiera)\n"
           "\t2. Acquisizione ed inserimento di un nuovo elemento (da file)\n"
           "\t3. Ricerca di un elemento (per codice)\n"
           "\t4. Cancellazione di un elemento\n"
           "\t5. Cancellazione di elementi in un intervallo di date\n"
           "\t6. Stampa dei dati su file\n"
           "\t0. EXIT\n");
    printf("Scelta: ");
    scanf("%d", &option);
    if(option>=0 && option<7)
        return option;
    return -1;
}

void printList(link h){
    link x;
    Item tmp;
    if(h==NULL)
        printf("\tNessun dato presente. Importare nuovi dati\n");
    else{
        for(x=h; x!=NULL; x=x->next){
            tmp=x->val;
            printf("%s %s %s %s %s %s %d\n", tmp.code, tmp.name, tmp.surname, tmp.date, tmp.street, tmp.city, tmp.cap);
        }
    }

}

void startOpts(link head){
    Item d;
    int stop=1,opt;
    link tmp;
    while(stop){
        opt=printOpts();
        switch(opt){
            case 1:
                head=insertByKeyboard(head,d);
                break;
            case 2:
                tmp= insertByFile(head,d);
                if(tmp!=NULL) head=tmp;
                break;
            case 3:
                searchByCode(head);
                break;
            case 4:
                head=deleteByCode(head);
                break;
            case 5:
                head= deleteByDate(head);
                break;
            case 6:
                printList(head);
                break;
            case 0:
                stop=0;
                head=freeList(head);
                break;
            default: printf("Comando errato\n\n");
        }
    }
}
