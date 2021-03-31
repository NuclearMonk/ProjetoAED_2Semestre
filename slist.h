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

typedef struct _slist slist_t;

slist_t*    SL_Initialize();
bool        SL_IsEmpty(slist_t* head);

slist_t*    SL_NewElement(Data data);
void        SL_FreeElement(slist_t* element, void (*free_function)(Data data));
void        SL_FreeList(slist_t* head, void (*free_function)(Data data));

Data        SL_GetData(slist_t* element);
void        SL_SetData(slist_t* element, Data data);


slist_t*    SL_GetNext(slist_t* element);
void        SL_SetNext(slist_t* element, slist_t* next);


slist_t*    SL_InsertBefore(slist_t* head,slist_t* element);
slist_t*    SL_InsertAfter(slist_t* element,slist_t* new_element);

void        SL_Apply(slist_t* head, void (*f)(Data data));