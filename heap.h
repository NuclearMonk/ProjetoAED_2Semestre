/* Header File apra implementacao de uma priority queue
 * Para o projeto do 2 semestre de 2020/2021
 * Implemetado com uma beap binaria
 * 
 * Authors:Manuel Soares Last Modified:08/05/2021
 */

#ifndef _HEAP_H
#define _HEAP_H
typedef struct _heap heap_t;

heap_t*     HP_Alocar(int maxsize,int  (*CompareFunction)(int keyA,int keyB));
void        HP_Libertar(heap_t* heap);
void        HP_InserirFim(heap_t* heap,int key);
void        HP_InserirEUpdate(heap_t* heap,int key);

#endif