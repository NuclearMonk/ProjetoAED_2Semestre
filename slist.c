#include "slist.h"

struct _slist
{
    Data _data;
    t_slist* _next;
};

t_slist*  SL_Initialize() {
    return NULL;
}

bool    SL_IsEmpty(t_slist* head){
    if(head==NULL)return true;
    return false;
}

t_slist*  SL_NewElement(Data data){
    t_slist* new_element = malloc(sizeof(t_slist));
    SL_SetData(new_element,data);
    return new_element;
}

void    SL_FreeElement(t_slist* element, void (*free_function)(Data data)){
    free_function(SL_GetData(element));
    free(element);
}

Data   SL_GetData(t_slist* element){
    return element->_data;
}

void    SL_SetData(t_slist* element, Data data){
    element->_data= data;
}

t_slist*  SL_GetNext(t_slist* element){
    return element->_next;
}

void    SL_SetNext(t_slist* element, t_slist* next){
    element->_next=next;
}

t_slist*  SL_Prepend(t_slist* head,t_slist* element){
    SL_SetNext(element,head);
    return element;
}

bool  SL_InsertAfter(t_slist* element,t_slist* new_element){
    if(element==NULL){
        SL_Prepend(element,new_element);
        return false;
    }
    SL_SetNext(new_element,SL_GetNext(element));
    SL_SetNext(element,new_element);
    return true;
}

void    SL_FreeList(t_slist* head, void (*free_function)(Data data)){
    t_slist* next;
    while(head!=NULL){
        next = SL_GetNext(head);
        SL_FreeElement(head,free_function);
        head= next;
    }
}

void    SL_Apply(t_slist* head, void (*f)(Data data)){
    while(head!=NULL){
        f(SL_GetData(head));
        head= SL_GetNext(head);
    }
}