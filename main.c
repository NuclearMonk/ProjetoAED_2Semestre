#include <stdio.h>

#include "slist.h"
#include "stack.h"
#include "dlist.h"
#include "fileinterface.h"

void PrintAndFree(void* number);
void DoNothing(Data data);

int main(){
    int i=0;
    cabecalho_t* cabecalho;
    slist_t*  test_slist = SL_Initialize();
    dlist_t*  test_dlist = DL_Initialize();
    stack_t*  test_stack = ST_New(100); 

    int* aux = NULL;
    for(int i =0 ;i<100;i++){
        aux = (int*)malloc(sizeof(int));
        aux[0] = i;
        test_slist = SL_InsertBefore(test_slist,SL_NewElement(aux));
    }
    for(slist_t* auxlist =test_slist;auxlist!=NULL; auxlist=SL_GetNext(auxlist)){
        ST_Push(test_stack,SL_GetData(auxlist));
    }
    SL_FreeList(test_slist,&DoNothing);
    aux= NULL;
    while(!ST_IsEmpty(test_stack)){
        test_dlist = DL_InsertAfter(test_dlist,DL_NewElement(ST_Pop(test_stack)));
    }
    ST_Free(test_stack);
    for(dlist_t* aux_dlist= test_dlist; aux_dlist!= NULL; aux_dlist= DL_GetPrevious(aux_dlist)){
        PrintAndFree(DL_GetData(aux_dlist));
    }
    DL_FreeListTail(test_dlist,DoNothing);
    FILE *fp;
    fp=fopen("problema.txt", "r");
    while(i<4){
    cabecalho = le_cabecalho_prob(fp);
    printf("tipo: %d Vincio: %d Vfinal: %d Vflag: %d \n", C_GetProblema(cabecalho), C_GetVInicial(cabecalho), C_GetVFinal(cabecalho), C_GetFlag(cabecalho));
    i++;
    }
    C_Liberta(cabecalho);

    return 0;
}

void PrintAndFree(Data number){
    printf("%d\n",((int*)number)[0]);
    free(number);
}

void DoNothing(Data data){
	return;
}