#include "slist.h"

struct _slist
{
    Data _data;
    t_slist* _next;
};

/*returns NULL to initialize an empty list*/
t_slist*  SL_Initialize() {
    return NULL;
}

/*returns true if the list has no elements*/
bool    SL_IsEmpty(t_slist* head){
    if(head==NULL)return true;
    return false;
}

/* returns a new allocated element that is storing the passed data*/
t_slist*  SL_NewElement(Data data){
    t_slist* new_element = (t_slist*)malloc(sizeof(t_slist));
    SL_SetData(new_element,data);
    return new_element;
}

/*destroys the provided element using the provided function*/
void    SL_FreeElement(t_slist* element, void (*free_function)(Data data)){
    free_function(SL_GetData(element));
    free(element);
}

/*returns the data stored in element*/
Data   SL_GetData(t_slist* element){
    return element->_data;
}

/*sets the data stored in element*/
void    SL_SetData(t_slist* element, Data data){
    element->_data= data;
}

/*returns the element that sucedes the one provided*/
t_slist*  SL_GetNext(t_slist* element){
    return element->_next;
}

/*sets the element that sucedes the one provided*/
void    SL_SetNext(t_slist* element, t_slist* next){
    element->_next=next;
}

/*adds element at the top of the list head and returns the new head*/
t_slist*  SL_InsertBefore(t_slist* head,t_slist* element){
    SL_SetNext(element,head);
    return element;
}

/*adds element to the list between element and the one that follows element*/
t_slist*  SL_InsertAfter(t_slist* element,t_slist* new_element){
    SL_SetNext(new_element,SL_GetNext(element));
    SL_SetNext(element,new_element);
    return new_element;
}

/*Liberta a lista usando a fucao freefunction Para libertar Data*/
void    SL_FreeList(t_slist* head, void (*free_function)(Data data)){
    t_slist* next;
    while(head!=NULL){
        next = SL_GetNext(head);
        SL_FreeElement(head,free_function);
        head= next;
    }
}

/* Apply f to data to all elements in list */
void    SL_Apply(t_slist* head, void (*f)(Data data)){
    while(head!=NULL){
        f(SL_GetData(head));
        head= SL_GetNext(head);
    }
}