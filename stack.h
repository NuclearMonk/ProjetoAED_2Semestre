#include <stdlib.h>
#include <stdbool.h>

stack* ST_New(unsigned int sz);
Void ST_Free(stack* st);
Void ST_Push(DATA data , stack* st);
DATA  ST_Pop(stack* st);
DATA  ST_Peek(stack* st);
Int ST_Used(stack* st);
Bool ST_IsEmpty(stack* st);
/*Void 	ST_Free(stack* st);
Void 	ST_Push(DATA data , stack* st);
DATA  ST_Pop(stack* st);
Void DoNothing(Data data);
DATA  ST_Peek(stack* st);
Int 	ST_Used(stack* st);
Bool 	ST_IsEmpty(stack* st);
