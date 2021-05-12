#include "pqueue.h"
#include <stdlib.h>
#include <stdio.h>

#define SWAP(A,B)       {int aux = pqueue->_heap[A];pqueue->_chaves[aux]=B;pqueue->_chaves[pqueue->_heap[B]]=A;pqueue->_heap[A]=pqueue->_heap[B];pqueue->_heap[B]=aux;}
#define INSERIRFIM(A,V)   {pqueue->_heap[pqueue->_n_elementos]=A;pqueue->_chaves[A]=pqueue->_n_elementos;pqueue->_n_elementos++;pqueue->_valores[A]=V;}
#define VALORINDEX(index)   pqueue->_valores[pqueue->_heap[index]]
#define VALORCHAVE(A)       pqueue->_valores[A]


struct _pqueue{
    int  _n_elementos;
    int* _heap;             /*heap de keys ordenadas por valor*/
    int* _chaves;           /*Associa a chave com a sua posicao na queue*/
    double* _valores;          /*guarda os valores para comparacao*/
    int  (*_CompareFunction)(double valorA,double valorB);
};

void        HP_FixUp(pqueue_t* pqueue, int index){
    while(index>0 && pqueue->_CompareFunction(VALORINDEX(index),VALORINDEX((index-1)/2))){ /*Iterativamente troca cada filho com o seu pai se o pai tiver pior prioridade que o filho*/
        SWAP(index, (index-1)/2);
        index = ((index-1)/2);
    }
}

void        HP_FixDown(pqueue_t* pqueue, int index){
    int child=0;
    /*Iterativamente trocamos cada pai com o pior dos seus filhos se o pai for pior que um dos filhos
      fica implicito que se apenas um dos filhos for pior que o pai esse filho vai ser o pior dos filhos*/
    while(2*index< pqueue->_n_elementos-1){
        child = 2*index+1;
        if((child<pqueue->_n_elementos-1)&& (pqueue->_CompareFunction(VALORINDEX(child+1),VALORINDEX(child))))child++; /*Se existem duas folhas comparamos definimos como child a folha com pior prioridade*/
        if(pqueue->_CompareFunction(VALORINDEX(index),VALORINDEX(child)))break; /*Verificada a condicao de acervo, logo podemos sair*/
        SWAP(index, child);
        index=child;
    }
}

pqueue_t*   PQ_Alocar(int maxsize,double* valores,int(*CompareFunction)(double valorA,double valorB)){
    pqueue_t* aux = (pqueue_t*)malloc(sizeof(pqueue_t));
    if(aux==NULL)exit(0);
    aux->_n_elementos=0;
    aux->_heap= (int*)calloc(maxsize,sizeof(int));
    aux->_chaves=(int*)malloc(maxsize*sizeof(int));
    for(int i=0;i<maxsize;i++)aux->_chaves[i]=-1;
    aux->_valores=valores;
    aux->_CompareFunction=CompareFunction;
    return aux;
}


void        PQ_Libertar(pqueue_t* pqueue){
    free(pqueue->_heap);
    free(pqueue->_chaves);
    free(pqueue);
}




void        PQ_InserirFim(pqueue_t* pqueue,int chave,double valor){
    INSERIRFIM(chave,valor);
}

void        PQ_InserirEUpdate(pqueue_t* pqueue,int chave,double valor){
    INSERIRFIM(chave,valor);
    HP_FixUp(pqueue,pqueue->_n_elementos-1);
}

int         PQ_Primeiro(pqueue_t* pqueue){
    return pqueue->_heap[0];
}

int         PQ_PrimeiroEApaga(pqueue_t* pqueue){
    int aux  = pqueue->_heap[0];
    pqueue->_heap[0]=pqueue->_heap[pqueue->_n_elementos-1];
    pqueue->_heap[pqueue->_n_elementos-1]=aux;
    pqueue->_n_elementos--;
    HP_FixDown(pqueue,0);
    return aux;
}

void            PQ_MudarPrioridadeEUpdate(pqueue_t* pqueue,int chave, double valor){
    if(pqueue->_CompareFunction(VALORCHAVE(chave),valor)){
        VALORCHAVE(chave)=valor;
        HP_FixDown(pqueue,pqueue->_chaves[chave]);
    }
    else{
        VALORCHAVE(chave)=valor;
        HP_FixUp(pqueue,pqueue->_chaves[chave]);
    }
}

int             PQ_Size(pqueue_t* pqueue){
    return pqueue->_n_elementos;
}