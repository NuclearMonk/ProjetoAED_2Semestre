/*
*   #include <slist.h>
*   
*   Implementa Single linked lists e funcoes para o seu manuseamento
*
*   Author:Manuel Soares
*/

#include <stdlib.h>
#include <stdbool.h>

typedef void *Data;
typedef struct _slist slist;

/*returns NULL to initialize an empty list*/
slist*  SL_Initialize();

/*returns true if the list has no elements*/
bool    SL_IsEmpty(slist* head);

/* returns a new allocated element that is storing the passed data*/
slist*  SL_NewElement(Data data);
/*destroys the provided element using the provided function*/
void    SL_FreeElement(slist* element, void (*free_function)(Data data));

/*returns the data stored in element*/
Data   SL_GetData(slist* element);
/*sets the data stored in element*/
void    SL_SetData(slist* element, Data data);

/*returns the element that sucedes the one provided*/
slist*  SL_GetNext(slist* element);
/*returns the element that sucedes the one provided*/
void    SL_SetNext(slist* element, slist* next);

/*adds element at the top of the list head and returns the new head*/
slist*  SL_Prepend(slist* head,slist* element);
/*adds element to the list between element and the one that follows element
 *RETURNS
 *true if postpend was sucessful;
 *false if element was null and was prepended instead;
 */
bool    SL_Pospend(slist* element,slist* new_element);

/*Liberta a lista usando a fucao freefunction Para libertar Data*/
void    SL_FreeList(slist* head, void (*free_function)(Data data));

/* Apply f to data to all elements in list */
void    SL_Apply(slist* head, void (*f)(Data data));