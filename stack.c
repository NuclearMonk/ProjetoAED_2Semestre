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



stack_t* ST_New(unsigned int sz){
	stack_t* new_stack= (stack_t*)malloc(sizeof(stack_t));
	new_stack->array = (Data*)malloc(sz*sizeof(Data));
	new_stack->stpointer = 0;
	return new_stack;
}

void ST_Free(stack_t* st){
	free(st->array);
	free(st);
}


void ST_Push(stack_t* st,Data data ){
	st->array[st->stpointer++]= data;
}

Data  ST_Pop(stack_t* st){
	if(st->stpointer==0)return NULL;
	return (st->array[--st->stpointer]);
}

Data  ST_Peek(stack_t* st){
	return(st->array[st->stpointer]);
}

int ST_Used(stack_t* st){
	return st->stpointer;
}

bool ST_IsEmpty(stack_t* st){
	return (st->stpointer == 0);
}
*/

struct _stack{
	unsigned int length;
	slist_t*	lista;
};

stack_t* ST_New(unsigned int sz){
	stack_t* new_stack = (stack_t*)malloc(sz*sizeof(stack_t));
	new_stack->length = 0;
    new_stack->lista = SL_Initialize();
	return new_stack;
}

void 	ST_Free(stack_t* st){
	SL_FreeList(st->lista,&DoNothing);
	free(st);
}

void 	ST_Push(stack_t* st, Data data){
	slist_t* aux = SL_NewElement(data);
	st->lista = SL_InsertBefore(st->lista, aux);
	st->length ++;
}

Data  ST_Pop(stack_t* st){
	Data aux = SL_GetData(st->lista);
    slist_t* aux2= st->lista;
	st->lista = SL_GetNext(st->lista);
	SL_FreeElement(aux2,&DoNothing);
	st->length--;
    return aux;
}

Data  ST_Peek(stack_t* st){
	return SL_GetData(st->lista);
}


int 	ST_Used(stack_t* st){
	return st->length;
}

bool 	ST_IsEmpty(stack_t* st){
	return (st->length == 0);
}