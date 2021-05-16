/* Header File apra implementacao de uma priority queue
 * Para o projeto do 2 semestre de 2020/2021
 * Implemetado com uma beap binaria
 * 
 * Authors:Manuel Soares Last Modified:08/05/2021
 */

#ifndef _PQUEUE_H
#define _PQUEUE_H

typedef struct _pqueue pqueue_t;

/*Aloca Priority Queue*/
pqueue_t*       PQ_Alocar(int maxsize,double* valores,int  (*CompareFunction)(double valorA,double valorB));
/*Liberta a priority queue n liberta o array valores*/
void            PQ_Libertar(pqueue_t* pqueue);
/*Insere no ultimo elemento da lista e NAO atualiza a profundidade*/
void            PQ_InserirFim(pqueue_t* pqueue,int chave,double valor);
/*Insere no ultimo elemento da lista e reordena a fila*/
void            PQ_InserirEUpdate(pqueue_t* pqueue,int chave,double valor);
/*Retorna a chave o primeiro elemento*/
int             PQ_Primeiro(pqueue_t* pqueue);
/*Retorna a chave o primeiro ememento e retira-o da fila*/
int             PQ_PrimeiroEApaga(pqueue_t* pqueue);

/*Muda a prioridade da cahve e reordena na lista*/
void            PQ_MudarPrioridadeEUpdate(pqueue_t* pqueue,int chave, double valor);

/*n de elementos na priority queue*/
int             PQ_Size(pqueue_t* pqueue);

int Less(double A, double B);

void VerifyHeap(pqueue_t* pqueue,int j);
void PrintHeap(pqueue_t* pq);
#endif