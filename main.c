#include <stdio.h>

#include "slist.h"

void Print(void* number);

int main(){
    slist* test = SL_Initialize();
    int* aux = NULL;
    for(int i =0 ;i<100;i++){
        aux = malloc(sizeof(int));
        aux[0] = i;
        test = SL_Prepend(test,SL_NewElement(aux));
    }
    SL_Apply(test,&Print);
    SL_FreeList(test,&free);
    return 0;
}

void Print(void* number){
    printf("%d\n",((int*)number)[0]);
}

