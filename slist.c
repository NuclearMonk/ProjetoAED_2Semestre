#include "slist.h"

struct _slist
{
    Data _data;
    slist_t* _next;
};

/*returns NULL to initialize an empty list*/
slist_t*  SL_Initialize() {
    return NULL;
}

/*returns true if the list has no elements*/
bool    SL_IsEmpty(slist_t* head){
    if(head==NULL)return true;
    return false;
}

/* returns a new allocated element that is storing the passed data*/
slist_t*  SL_NewElement(Data data){
    slist_t* new_element = (slist_t*)malloc(sizeof(slist_t));
    SL_SetData(new_element,data);
    return new_element;
}

/*destroys the provided element using the provided function*/
void    SL_FreeElement(slist_t* element, void (*free_function)(Data data)){
    free_function(SL_GetData(element));
    free(element);
}

/*returns the data stored in element*/
Data   SL_GetData(slist_t* element){
    return element->_data;
}

/*sets the data stored in element*/
void    SL_SetData(slist_t* element, Data data){
    element->_data= data;
}

/*returns the element that sucedes the one provided*/
slist_t*  SL_GetNext(slist_t* element){
    return element->_next;
}

/*sets the element that sucedes the one provided*/
void    SL_SetNext(slist_t* element, slist_t* next){
    element->_next=next;
}

/*adds element at the top of the list head and returns the new head*/
slist_t*  SL_InsertBefore(slist_t* head,slist_t* element){
    SL_SetNext(element,head);
    return element;
}

/*adds element to the list between element and the one that follows element*/
slist_t*  SL_InsertAfter(slist_t* element,slist_t* new_element){
    SL_SetNext(new_element,SL_GetNext(element));
    SL_SetNext(element,new_element);
    return new_element;
}

/*Liberta a lista usando a fucao freefunction Para libertar Data*/
void    SL_FreeList(slist_t* head, void (*free_function)(Data data)){
    slist_t* next;
    while(head!=NULL){
        next = SL_GetNext(head);
        SL_FreeElement(head,free_function);
        head= next;
    }
}

/* Apply f to data to all elements in list */
void    SL_Apply(slist_t* head, void (*f)(Data data)){
    while(head!=NULL){
        f(SL_GetData(head));
        head= SL_GetNext(head);
    }
}