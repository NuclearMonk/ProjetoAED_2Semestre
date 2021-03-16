#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#include "slist.h"

void    DoNothing(Data data);

/*
struct _stack{
	unsigned int stpointer;
	Data*	array;
};



t_stack* ST_New(unsigned int sz){
	t_stack* new_stack= (t_stack*)malloc(sizeof(t_stack));
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
*/

struct _stack{
	unsigned int length;
	t_slist*	lista;
};

t_stack* ST_New(unsigned int sz){
	t_stack* new_stack = (t_stack*)malloc(sz*sizeof(t_stack));
	new_stack->length = 0;
    new_stack->lista = SL_Initialize();
	return new_stack;
}

void 	ST_Free(t_stack* st){
	SL_FreeList(st->lista,&DoNothing);
	free(st);
}

void 	ST_Push(t_stack* st, Data data){
	t_slist* aux = SL_NewElement(data);
	st->lista = SL_InsertBefore(st->lista, aux);
	st->length ++;
}

Data  ST_Pop(t_stack* st){
	Data aux = SL_GetData(st->lista);
    t_slist* aux2= st->lista;
	st->lista = SL_GetNext(st->lista);
	SL_FreeElement(aux2,&DoNothing);
	st->length--;
    return aux;
}

Data  ST_Peek(t_stack* st){
	return SL_GetData(st->lista);
}


int 	ST_Used(t_stack* st){
	return st->length;
}

bool 	ST_IsEmpty(t_stack* st){
	return (st->length == 0);
}