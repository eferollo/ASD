#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "equipArray.h"

typedef struct equipArray_s{
    int inUso;
    int *vettEq;
}equip_t;

equipArray_t equipArray_init(){
    equipArray_t equipArray=calloc(1,sizeof(equip_t));
    equipArray->inUso=0;
    equipArray->vettEq=(int *)malloc(EQUIP_SLOT*sizeof(int));
    int i;
    for(i=0; i<EQUIP_SLOT; i++) equipArray->vettEq[i]=-1;
    return equipArray;
}

int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUso;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int i;
    for(i=0;i<EQUIP_SLOT;i++){
        if(equipArray->vettEq[i]!=-1)
            invArray_printByIndex(fp,invArray,i);
    }
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    if(equipArray==NULL)
        return -1;
    return equipArray->vettEq[index];
}
int equipArray_update(equipArray_t equipArray, invArray_t invArray, int *option){
    int opt,i,equip;
    char str[LEN];
    if(equipArray_inUse(equipArray)<EQUIP_SLOT)
        printf("0.Aggiunta equipaggiamento\n");
    if(equipArray_inUse(equipArray)>0)
        printf("1.Rimozione equipaggiameto\n");
    printf("Opzione: ");
    scanf("%d",&opt);
    switch(opt){
        case 0:
            if(equipArray_inUse(equipArray)>EQUIP_SLOT)
                return -1;
            printf("Nome equipaggiamento: ");
            scanf("%s",str);
            equip=invArray_searchByName(invArray,str);
            for(i=0; i<EQUIP_SLOT && equip!=-1; i++){
                if(equipArray->vettEq[i]==-1){
                    equipArray->vettEq[i]=equip;
                    equipArray->inUso++;
                    *option=opt;
                    break;
                }
            }
            break;
        case 1:
            if(equipArray_inUse(equipArray)<0)
                return -1;
            printf("Nome equipaggiamento: ");
            scanf("%s",str);
            equip=invArray_searchByName(invArray,str);
            for(i=0; i<EQUIP_SLOT && equip!=-1; i++){
                if(equipArray->vettEq[i]==equip){
                    equipArray->inUso--;
                    equipArray->vettEq[i]=-1;
                    *option=opt;
                    break;
                }
            }
            break;
        default: printf("Error\n");
            break;
    }
    return i;
}

void equipArray_free(equipArray_t equipArray){
    if(equipArray!=NULL)
        free(equipArray);
}