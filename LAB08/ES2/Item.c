#include "Item.h"

Item ITEMload(char str1[], char str2[]){
    Item x;
    strcpy(x.id_elab,str1);
    strcpy(x.id_rete,str2);
    return x;
}

void ITEMstore(Item val){
    printf("Elaboratore: %s --- Rete: %s\n", val.id_elab, val.id_rete);
}

Item ITEMsetvoid(){
    Item x;
    strcpy(x.id_elab,"");
    strcpy(x.id_rete,"");
    return x;
}

KEY KEYget(Item *val){
    return val->id_elab;
}

int KEYcmp(KEY k1, KEY k2){
    return strcmp(k1,k2);
}

void KEYscan(char node[MAX]){
    scanf("%s", node);
}
