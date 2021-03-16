#include <stdio.h>

#include "slist.h"
#include "stack.h"

void PrintAndFree(void* number);
void DoNothing(Data data);

int main(){
    t_slist*  list = SL_Initialize();
    t_stack*  stack = ST_New(100); 
    int* aux = NULL;
    for(int i =0 ;i<100;i++){
        aux = malloc(sizeof(int));
        aux[0] = i;
        list = SL_InsertBefore(list,SL_NewElement(aux));
    }
    for(t_slist* auxlist =list;auxlist!=NULL; auxlist=SL_GetNext(auxlist)){
        ST_Push(stack,SL_GetData(auxlist));
    }
    SL_FreeList(list,&DoNothing);
    aux= NULL;
    while(!ST_IsEmpty(stack)){
        PrintAndFree(ST_Pop(stack));
    }
    ST_Free(stack);
    return 0;
}

void PrintAndFree(Data number){
    printf("%d\n",((int*)number)[0]);
    free(number);
}

void DoNothing(Data data){
	return;
}