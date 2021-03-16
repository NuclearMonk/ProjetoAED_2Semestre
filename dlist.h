#include <stdlib.h>
#include <stdbool.h>
#include "Data.h"

typedef struct _dlist t_dlist;


t_dlist* DL_Initialize();
bool     DL_IsEmpty(t_dlist* head);

t_dlist* DL_NewElement(Data data);
void     DL_FreeElement(t_dlist* element, void (*free_function)(Data data));
void      DL_FreeList(t_dlist* head, void (*free_function)(Data data));

Data     DL_GetData(t_dlist* element);
void     DL_SetData(t_dlist* element, Data data);

t_dlist* DL_GetNext(t_dlist* element);
void     DL_SetNext(t_dlist* element, t_dlist* next);


t_dlist*  DL_GetPrevious(t_dlist* element);
void      DL_SetPrevious(t_dlist* element, t_dlist* previous);

t_dlist*  DL_InsertBefore(t_dlist* head,t_dlist* element);
t_dlist* DL_InsertAfter(t_dlist* element,t_dlist* new_element);

void    DL_Apply(t_dlist* head, void (*f)(Data data));