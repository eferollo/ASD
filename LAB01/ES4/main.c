#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define filename "corse.txt"
#define MAXN 1000
#define MAXC 31

typedef enum{
    o_date, o_codice, o_partenza, o_arrivo, ricerca, or_fine, or_err
}comando_e;

typedef struct{
    char codice_tratta[MAXC];
    char partenza[MAXC];
    char destinazione[MAXC];
    char data[MAXC];
    char ora_partenza[MAXC];
    char ora_arrivo[MAXC];
    int ritardo;
}LOG;

int leggiTabella(LOG *tabella);
comando_e leggiComando(void);
void strToLower(char *s);
void menuParola(LOG *tabella, int n);
void sorting(LOG **tabella, int n, int key);
void print(LOG **tabella, int n, char *name,int option);
void findAlgorithm(LOG *tabella,int n);
void linearSearch(LOG **tabella, int n, int l, int r,int cmd);
int BinSearch_lower(LOG **tabella, int l, int r, char *partenza);
int BinSearch_upper(LOG **tabella, int l, int r, char *partenza);

int main() {
    LOG tabella[MAXN];
    int n=leggiTabella(tabella);
    menuParola(tabella,n);
    return 0;
}

void print(LOG **tabella, int n, char *name, int option){
    int cmd,i;
    FILE *fout;
    if(option==1){
        printf("Scegliere se visualizzare il risultato a video o esportare su un file:\n1-Video\n2-File\n"
               "Comando (1 o 2): ");
        scanf("%d",&cmd);
        switch(cmd){
            case 1:
                for(i=0;i<n;i++)
                    printf("%s %s %s %s %s %s %d\n", tabella[i]->codice_tratta, tabella[i]->partenza, tabella[i]->destinazione,
                           tabella[i]->data, tabella[i]->ora_partenza, tabella[i]->ora_arrivo, tabella[i]->ritardo);
                printf("\n");
                break;
            case 2:
                fout=fopen(name,"w");
                if(fout==NULL){
                    printf("Errore durante la creazione del file\n");
                    exit(-1);
                }
                for(i=0;i<n;i++)
                    fprintf(fout,"%s %s %s %s %s %s %d\n",tabella[i]->codice_tratta, tabella[i]->partenza, tabella[i]->destinazione,
                            tabella[i]->data, tabella[i]->ora_partenza, tabella[i]->ora_arrivo, tabella[i]->ritardo);
                fclose(fout);
                break;
            default: printf("Comando errato\n");
        }
    }else{
        if(option%2!=0)
            printf("%s %s %s %s %s %s %d\n", tabella[0]->codice_tratta, tabella[0]->partenza, tabella[0]->destinazione,
                   tabella[0]->data, tabella[0]->ora_partenza, tabella[0]->ora_arrivo, tabella[0]->ritardo);
        else{
            fout=fopen(name,"aw");
            if(fout==NULL){
                printf("Errore durante la creazione del file\n");
                exit(-1);
            }
            fprintf(fout,"%s %s %s %s %s %s %d\n", tabella[0]->codice_tratta, tabella[0]->partenza, tabella[0]->destinazione,
                    tabella[0]->data, tabella[0]->ora_partenza, tabella[0]->ora_arrivo, tabella[0]->ritardo);
            fclose(fout);
        }
    }
}

int sortDate(LOG a, LOG b){
    return (strcmp(strcat(a.data,a.ora_partenza),strcat(b.data,b.ora_partenza)));
}

void sorting(LOG **tabella, int n, int key){
    int i,j,l=0,r=n-1,flag=1;
    LOG *tmp;
    for (i=l; i<r && flag==1; i++) {
        flag=0;
        for (j=l; j<r-i+l; j++){
            if(key==o_date){
                if(sortDate(*tabella[j],*tabella[j+1])>0){
                    flag=1;
                    tmp=tabella[j];
                    tabella[j] = tabella[j+1];
                    tabella[j+1]=tmp;
                }
            }else if(key==o_codice){
                if(strcmp(tabella[j]->codice_tratta,tabella[j+1]->codice_tratta)>0) {
                    flag=1;
                    tmp=tabella[j];
                    tabella[j] = tabella[j+1];
                    tabella[j+1]=tmp;
                }
            }else if(key==o_partenza){
                if(strcmp(tabella[j]->partenza,tabella[j+1]->partenza)>=0){
                    if(strcmp(tabella[j]->partenza,tabella[j+1]->partenza)==0 && sortDate(*tabella[j],*tabella[j+1])>0){
                        flag=1;
                        tmp=tabella[j];
                        tabella[j] = tabella[j+1];
                        tabella[j+1]=tmp;
                    }else if(strcmp(tabella[j]->partenza,tabella[j+1]->partenza)>0){
                        flag=1;
                        tmp=tabella[j];
                        tabella[j] = tabella[j+1];
                        tabella[j+1]=tmp;
                    }
                }
            }else{
                if(strcmp(tabella[j]->destinazione,tabella[j+1]->destinazione)>0){
                    flag=1;
                    tmp=tabella[j];
                    tabella[j] = tabella[j+1];
                    tabella[j+1]=tmp;
                }
            }
        }
    }
}

void findAlgorithm(LOG *tabella,int n){
    char str[MAXC],str2[MAXC];
    LOG *ref[MAXN];
    int upper_bound, lower_bound,p_opt,i,found=1;
    for(i=0;i<n;i++) ref[i]=&tabella[i];
    printf("Inserisci la fermata: ");
    scanf("%s", str);
    strToLower(str);
    for(i=0;i<n;i++){
        strcpy(str2, tabella[i].partenza);
        strToLower(str2);
        if(strncmp(str,str2, strlen(str))==0){
            strcpy(str,tabella[i].partenza);
            found=1;
            break;
        }
        else found=0;
    }
    if(!found){
        printf("\nNo matching record\n\n");
    }else{
        sorting(ref,n,o_partenza);
        lower_bound=BinSearch_lower(ref,0,n,str);
        upper_bound=BinSearch_upper(ref,0,n,str);
        printf("Scegliere se visualizzare il risultato a video o esportare su un file:\n1-Video\n2-File\n"
                                                        "Comando (1 o 2): ");
        scanf("%d",&p_opt);
        linearSearch(ref,n, lower_bound,upper_bound, p_opt);
    }
}

void linearSearch(LOG **tabella, int n, int l, int r,int cmd){
    for(int i=l;i<=r;i++)
        print(tabella+i,n,"SelectByDeparture.txt",2+cmd);
}

int BinSearch_lower(LOG **tabella, int l, int r, char *partenza) {
    int m;
    if (l>r)
        return -1;
    m=(l + r)/2;
    if (strcmp(partenza,tabella[m]->partenza)<=0){
        if(m!=0 && sortDate(*tabella[m],*tabella[m-1])>0
        && strcmp(tabella[m]->partenza,tabella[m-1]->partenza)<=0)
            return BinSearch_lower(tabella, l, m-1, partenza);
        else if(strcmp(partenza,tabella[m]->partenza)==0)
            return (m);
        else if(strncmp(partenza,tabella[m]->partenza,strlen(partenza))<0)
            return BinSearch_lower(tabella, l, m-1, partenza);
    }
    return BinSearch_lower(tabella, m+1, r, partenza);
}

int BinSearch_upper(LOG **tabella, int l, int r, char *partenza) {
    int m;
    if (l>r)
        return -1;
    m=(l + r)/2;
    if (strcmp(partenza,tabella[m]->partenza)==0)
        return (m);
    if (strcmp(partenza,tabella[m]->partenza)<0)
        return BinSearch_upper(tabella, l, m-1, partenza);
    return BinSearch_upper(tabella, m+1, r, partenza);
}

void menuParola(LOG *tabella, int n){
    LOG *refD[MAXN], *refC[MAXN], *refP[MAXN], *refA[MAXN];
    comando_e cmd;
    int continua=1,i;
    for(i=0;i<n;i++){
        refD[i]=&tabella[i];
        refC[i]=&tabella[i];
        refP[i]=&tabella[i];
        refA[i]=&tabella[i];
    }
    while(continua){
        cmd=leggiComando();
        switch(cmd){
            case o_date:
                sorting(refD,n,o_date);
                print(refD,n,"SortByDate.txt",1);
                break;
            case o_codice:
                sorting(refC,n,o_codice);
                print(refC,n,"SortByID.txt",1);
                break;
            case o_partenza:
                sorting(refP,n,o_partenza);
                print(refP,n,"SortByDeparture.txt",1);
                break;
            case o_arrivo:
                sorting(refA,n,o_arrivo);
                print(refA,n,"SortByArrival.txt",1);
                break;
            case ricerca:
                findAlgorithm(tabella,n);
                break;
            case or_fine: continua=0;
                break;
            case or_err:
            default: printf("Comando errato\n");
        }
    }
}

void strToLower(char *s){
    while(*s != '\0'){
        *s=tolower(*s);
        s++;
    }
}

comando_e leggiComando(void){
    char cmd[MAXC];
    comando_e c;
    char *tabComandi[]={"data", "codice", "partenza", "arrivo", "ricerca", "fine"};
    printf("1. Scelta ordinamento file per:\n-data\n-codice tratta\n-stazione di partenza\n-stazione di arrivo"
           "\n2. Ricerca per stazione di partenza\n"
           "Inserire comando (Ordinamento: data/codice/partenza/arrivo) (Ricerca: ricerca): ");
    scanf("%s", cmd);
    strToLower(cmd);
    c=o_date;
    while(c<or_err && strcmp(cmd,tabComandi[c])!=0)
        c++;
    return c;
}

int leggiTabella(LOG *tabella){
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("Error while opening file\n");
        exit(1);
    }
    int n, i=0;
    fscanf(fp,"%d", &n);
    while(fscanf(fp, "%s%s%s%s%s%s%d", tabella[i].codice_tratta, tabella[i].partenza,
                 tabella[i].destinazione, tabella[i].data,
                 tabella[i].ora_partenza, tabella[i].ora_arrivo,
                 &tabella[i].ritardo)!=EOF)
        i++;
    return n;
}