#ifndef _STACK_H
#define _STACK_H
#include <stdlib.h>
#include <stdbool.h>
#include "Data.h"

typedef struct _stack stack_t;
/*
stack_t* ST_New(unsigned int sz);
void ST_Free(stack_t* st);
void ST_Push(stack_t* st,Data data);
Data  ST_Pop(stack_t* st);
Data  ST_Peek(stack_t* st);
int ST_Used(stack_t* st);
bool ST_IsEmpty(stack_t* st);
*/

stack_t* ST_New(unsigned int sz);
void 	 ST_Free(stack_t* st);
void 	 ST_Push(stack_t* st, Data data);
Data     ST_Pop(stack_t* st);
Data     ST_Peek(stack_t* st);
int 	 ST_Used(stack_t* st);
bool   	 ST_IsEmpty(stack_t* st);
#endif

