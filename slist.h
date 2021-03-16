/*
*   #include <slist.h>
*   
*   Implementa Single linked lists e funcoes para o seu manuseamento
*
*   Author:Manuel Soares
*/

#include <stdlib.h>
#include <stdbool.h>
#include "Data.h"

typedef struct _slist t_slist;

t_slist*  SL_Initialize();
bool    SL_IsEmpty(t_slist* head);

t_slist*    SL_NewElement(Data data);
void        SL_FreeElement(t_slist* element, void (*free_function)(Data data));
void        SL_FreeList(t_slist* head, void (*free_function)(Data data));

Data   SL_GetData(t_slist* element);
void    SL_SetData(t_slist* element, Data data);


t_slist*  SL_GetNext(t_slist* element);
void    SL_SetNext(t_slist* element, t_slist* next);


t_slist*  SL_InsertBefore(t_slist* head,t_slist* element);
t_slist* SL_InsertAfter(t_slist* element,t_slist* new_element);

void    SL_Apply(t_slist* head, void (*f)(Data data));