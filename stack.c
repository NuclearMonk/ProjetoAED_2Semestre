#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

struct _stack{
	unsigned int stpointer;
	Data*	array;
};


t_stack* ST_New(unsigned int sz){
	t_stack* new_stack= malloc(sizeof(t_stack));
	new_stack->array = malloc(sz*sizeof(Data));
	new_stack->stpointer = 0;
	return new_stack;
}

void ST_Free(t_stack* st){
	free(st->array);
	free(st);
}


void ST_Push(t_stack* st,Data data ){
	st->array[st->stpointer++]= data;
}

Data  ST_Pop(t_stack* st){
	if(st->stpointer==0)return NULL;
	return (st->array[--st->stpointer]);
}

Data  ST_Peek(t_stack* st){
	return(st->array[st->stpointer]);
}

int ST_Used(t_stack* st){
	return st->stpointer;
}

bool ST_IsEmpty(t_stack* st){
	return (st->stpointer == 0);
}

/*Typedef struct _stack{
	Unsigned int length;
	t_slist* 	lista;
};

stack* ST_New(unsigned int sz){
	St = malloc(sz*sizeof(t_slist));
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

DATA  ST_Peek(stack* st){
	Return SL_GetData(st.lista);
}


Int 	ST_Used(stack* st){
	Return st.leght;
}

Bool 	ST_IsEmpty(stack* st){
	Return (st.leght == 0);
}

*/