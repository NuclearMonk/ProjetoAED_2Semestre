#ifndef _DLIST_H
#define _DLIST_H
#include <stdlib.h>
#include <stdbool.h>
#include "Data.h"

typedef struct _dlist dlist_t;


dlist_t* DL_Initialize();
bool     DL_IsEmpty(dlist_t* head);

dlist_t* DL_NewElement(Data data);
void     DL_FreeElement(dlist_t* element, void (*free_function)(Data data));
void     DL_FreeListHead(dlist_t* head, void (*free_function)(Data data));
void     DL_FreeListTail(dlist_t* tail, void (*free_function)(Data data));

Data     DL_GetData(dlist_t* element);
void     DL_SetData(dlist_t* element, Data data);

dlist_t* DL_GetNext(dlist_t* element);
void     DL_SetNext(dlist_t* element, dlist_t* next);


dlist_t* DL_GetPrevious(dlist_t* element);
void     DL_SetPrevious(dlist_t* element, dlist_t* previous);

dlist_t* DL_InsertBefore(dlist_t* head,dlist_t* element);
dlist_t* DL_InsertAfter(dlist_t* element,dlist_t* new_element);

void     DL_Apply(dlist_t* head, void (*f)(Data data));

#endif