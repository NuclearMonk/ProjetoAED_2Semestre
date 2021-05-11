
#include "heap.h"
#include <stdlib.h>

#define SWAP(A,B) {int aux = heap->_array[A];heap->_chaves[aux]=B;heap->_chaves[heap->array[B]]=A;heap->_array[A]=heap->_array[B];heap->_array[B]=aux;}
#define INSERIRFIM(A) {heap->_array[heap->_size]=A;heap->_chaves[A]=heap->_size;size++;}

struct _heap{
    int  _size;
    int* _array;
    int* _chaves;
    int  (*_CompareFunction)(int keyA,int keyB);
};

void        HP_FixUp(heap_t* heap, int index);
void        HP_FixDown(heap_t* heap, int index);


heap_t*   HP_Alocar(int maxsize,int  (*CompareFunction)(int keyA,int keyB)){
    heap_t* aux = (heap_t*)malloc(sizeof(heap_t));
    if(aux==NULL)exit(0);
    aux->_size=0;
    aux->_array= (int*)calloc(maxsize,sizeof(int));
    aux->_chaves=(int*)malloc(maxsize*sizeof(int));
    for(int i=0;i<maxsize;i++)aux->_chaves[i]=-1;
    aux->_CompareFunction=CompareFunction;
    return aux;
}


void        HP_Libertar(heap_t* heap){
    free(heap->_array);
    free(heap);
}


void        PQ_FixUp(heap_t* heap, int index){
    while(index>0 && heap->_CompareFunction(heap->_array[index],heap->_array[(index-1)/2])){ /*Iterativamente troca cada filho com o seu pai se o pai tiver pior prioridade que o filho*/
        SWAP(index, (index-1)/2);
        index = (index-1/2);
    }
}

void        HP_FixDown(heap_t* heap, int index){
    int child=0;
    /*Iterativamente trocamos cada pai com o pior dos seus filhos se o pai for pior que um dos filhos
      fica implicito que se apenas um dos filhos for pior que o pai esse filho vai ser o pior dos filhos*/
    while(2*index< heap->_size-1){
        child = 2*index+1;
        if(child<heap->_size-1&& heap->_CompareFunction(heap->_array[child],heap->_array[child+1]))child++; /*Se existem duas folhas comparamos definimos como child a folha com pior prioridade*/
        if(heap->_CompareFunction(heap->_array[index],heap->_array[child]))break; /*Verificada a condicao de acervo, logo podemos sair*/
        SWAP(index, child);
        index=child;
    }
}

void        HP_InserirFim(heap_t* heap,int key){
    INSERIRFIM(key);
}

void        PQ_InsertEUpdate(heap_t* heap,int key){
    INSERIRFIM(key);
    PQ_FixUp(heap,heap->_size-1);
}
