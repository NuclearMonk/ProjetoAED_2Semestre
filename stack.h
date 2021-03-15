#include <stdlib.h>
#include <stdbool.h>
#include "Data.h"

typedef struct _stack t_stack;
/*
t_stack* ST_New(unsigned int sz);
void ST_Free(t_stack* st);
void ST_Push(t_stack* st,Data data);
Data  ST_Pop(t_stack* st);
Data  ST_Peek(t_stack* st);
int ST_Used(t_stack* st);
bool ST_IsEmpty(t_stack* st);
*/

t_stack* ST_New(unsigned int sz);
void 	ST_Free(t_stack* st);
void 	ST_Push(t_stack* st, Data data);
Data    ST_Pop(t_stack* st);
Data    ST_Peek(t_stack* st);
int 	ST_Used(t_stack* st);
bool 	ST_IsEmpty(t_stack* st);

