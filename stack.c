#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

Typedef Struct _stack{
		Unsigned int stpointer;
		DATA*	Array;
}stack


stack* ST_New(unsigned int sz){
	New_Stack = malloc(sz*sizeof(DATA));
	Stpointer = 0;
}

Void ST_Free(stack* st){
	free(st.Array);
	free(st);
}


Void ST_Push(DATA data , stack* st){
	st.array[++stpointer]= data;
}

DATA  ST_Pop(stack* st){
	return (st.array[st.stpointer--]);
}

DATA  ST_Peek(stack* st){
	return(st.array[st.stpointer]);
}

Int ST_Used(stack* st){
	Return sz.stpointer;
}

Bool ST_IsEmpty(stack* st){
	Return (sz.stpointer == 0);
}

/*Typedef struct _stack{
	Unsigned int length;
	slist* 	lista;
}stack

stack* ST_New(unsigned int sz){
	St = malloc(sz*sizeof(slist));
	St.length =0;
	Lista = SL_Initialize();
}

Void 	ST_Free(stack* st){
	free(st);
}

Void 	ST_Push(DATA data , stack* st){
	Slist * aux = SL_NewElement(data);
	st.lista = SL_Prepend(st.lista, aux);
	st.length ++;
}

DATA  ST_Pop(stack* st){
	DATA Aux = SL_GetData(lista);
	Slist aux2= lista;
	Lista = SL_GetNext(lista);
	SL_FreeElement(aux2,&DoNothing());
	St.legth--;
    Return Aux;
}

Void DoNothing(Data data){
	Return;
}

DATA  ST_Peek(stack* st){
	Return SL_GetData(st.lista);
}


Int 	ST_Used(stack* st){
	Return st.leght;
}

Bool 	ST_IsEmpty(stack* st){
	Return (st.leght == 0);
}