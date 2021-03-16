#include "dlist.h"
#include <stdio.h>


struct _dlist
{
    Data _data;
    t_dlist* _next;
    t_dlist* _previous;
};

/*returns NULL to initialize an empty list*/
t_dlist* DL_Initialize(){
    return NULL;
}

/*returns true if the list has no elements*/
bool     DL_IsEmpty(t_dlist* head){
    return(head==NULL);
}

/* returns a new allocated element that is storing the passed data*/
t_dlist* DL_NewElement(Data data){
    t_dlist* aux = malloc(sizeof(t_dlist));
    aux->_data    = data;
    aux->_next    = DL_Initialize();
    aux->_previous= DL_Initialize();
    return aux;
}

/*destroys the provided element using the provided function*/
void     DL_FreeElement(t_dlist* element, void (*free_function)(Data data)){
    free_function(DL_GetData(element));
    free(element);
}

/*returns the data stored in element*/
Data     DL_GetData(t_dlist* element){
    return element->_data;
}

/*sets the data stored in element*/
void     DL_SetData(t_dlist* element, Data data){
    data = element->_data;
}

/*returns the element that sucedes the one provided*/
t_dlist* DL_GetNext(t_dlist* element){
    return element->_next;
}

/*returns the element that sucedes the one provided*/
void     DL_SetNext(t_dlist* element, t_dlist* next){
    element->_next=next;
}

/*returns the element that precedes the one provided*/
t_dlist* DL_GetPrevious(t_dlist* element){
    return element->_previous;
}
/*returns the element that precedes the one provided*/
void     DL_SetPrevious(t_dlist* element, t_dlist* previous){
    element->_previous= previous;
}

/*adds new_element at the top of the list head and returns the new_element*/
t_dlist*  DL_InsertBefore(t_dlist* element,t_dlist* new_element){
    if(element==NULL){
        DL_SetNext(new_element,NULL);
        return new_element;
    }
    DL_SetPrevious(new_element,DL_GetPrevious(element));
    if(DL_GetPrevious(element)!=NULL)   DL_SetNext(DL_GetPrevious(element),new_element);
    DL_SetPrevious(element,new_element);
    DL_SetNext(new_element,element);
    return new_element;
}

/*adds element to the list between element and the one that follows element
 *Returns new_element*/
t_dlist* DL_InsertAfter(t_dlist* element,t_dlist* new_element){
    if(element==NULL){
        DL_SetPrevious(new_element,NULL);
        return new_element;
    }
    DL_SetNext(new_element,DL_GetNext(element));
    if(DL_GetNext(new_element)!=NULL)   DL_SetPrevious(DL_GetNext(new_element),new_element);
    DL_SetNext(element,new_element);
    DL_SetPrevious(new_element,element);
    return new_element;
}

/*Liberta a lista comecando na head usando a fucao freefunction Para libertar Data*/
void    DL_FreeListHead(t_dlist* head, void (*free_function)(Data data)){
    t_dlist* next;
    while(head!=NULL){
        next = DL_GetNext(head);
        DL_FreeElement(head,free_function);
        head= next;
    }
}

/*Liberta a lista comecando na head usando a fucao freefunction Para libertar Data*/
void    DL_FreeListTail(t_dlist* tail, void (*free_function)(Data data)){
    t_dlist* prev;
    while(tail!=NULL){
        prev = DL_GetPrevious(tail);
        DL_FreeElement(tail,free_function);
        tail= prev;
    }
}

/* Apply f to data to all elements in list */
void    DL_Apply(t_dlist* head, void (*f)(Data data)){
    while(head!=NULL){
        f(DL_GetData(head));
        head= DL_GetNext(head);
    }
}