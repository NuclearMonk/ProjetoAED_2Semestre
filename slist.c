#include "slist.h"

struct _slist
{
    Data _data;
    slist* _next;
};

slist*  SL_Initialize() {
    return NULL;
}

bool    SL_IsEmpty(slist* head){
    if(head==NULL)return true;
    return false;
}

slist*  SL_NewElement(Data data){
    slist* new_element = malloc(sizeof(slist));
    SL_SetData(new_element,data);
}

void    SL_FreeElement(slist* element, void (*free_function)(Data data)){
    free_function(SL_GetData(element));
    free(element);
}

Data   SL_GetData(slist* element){
    return element->_data;
}

void    SL_SetData(slist* element, Data data){
    element->_data= data;
}

slist*  SL_GetNext(slist* element){
    return element->_next;
}

void    SL_SetNext(slist* element, slist* next){
    element->_next=next;
}

slist*  SL_Prepend(slist* head,slist* element){
    SL_SetNext(element,head);
    return element;
}

bool  SL_Pospend(slist* element,slist* new_element){
    if(element==NULL){
        SL_Prepend(element,new_element);
        return false;
    }
    SL_SetNext(new_element,SL_GetNext(element));
    SL_SetNext(element,new_element);
    return true;
}

void    SL_FreeList(slist* head, void (*free_function)(Data data)){
    slist* next;
    while(head!=NULL){
        next = SL_GetNext(head);
        SL_FreeElement(head,free_function);
        head= next;
    }
}

void    SL_Apply(slist* head, void (*f)(Data data)){
    while(head!=NULL){
        f(SL_GetData(head));
        head= SL_GetNext(head);
    }
}