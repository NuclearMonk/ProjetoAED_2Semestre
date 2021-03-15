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

/*returns NULL to initialize an empty list*/
t_slist*  SL_Initialize();

/*returns true if the list has no elements*/
bool    SL_IsEmpty(t_slist* head);

/* returns a new allocated element that is storing the passed data*/
t_slist*  SL_NewElement(Data data);
/*destroys the provided element using the provided function*/
void    SL_FreeElement(t_slist* element, void (*free_function)(Data data));

/*returns the data stored in element*/
Data   SL_GetData(t_slist* element);
/*sets the data stored in element*/
void    SL_SetData(t_slist* element, Data data);

/*returns the element that sucedes the one provided*/
t_slist*  SL_GetNext(t_slist* element);
/*returns the element that sucedes the one provided*/
void    SL_SetNext(t_slist* element, t_slist* next);

/*adds element at the top of the list head and returns the new head*/
t_slist*  SL_Prepend(t_slist* head,t_slist* element);
/*adds element to the list between element and the one that follows element
 *RETURNS
 *true if postpend was sucessful;
 *false if element was null and was prepended instead;
 */
bool    SL_InsertAfter(t_slist* element,t_slist* new_element);

/*Liberta a lista usando a fucao freefunction Para libertar Data*/
void    SL_FreeList(t_slist* head, void (*free_function)(Data data));

/* Apply f to data to all elements in list */
void    SL_Apply(t_slist* head, void (*f)(Data data));