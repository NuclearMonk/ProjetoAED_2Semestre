#include "debug.h"

#include <stdlib.h>
#include <stdio.h>

#include "pqueue.h"

void TestHeaps(){
    pqueue_t* pq;
    int* distancia=calloc(100,sizeof(int));
    pq= PQ_Alocar(8,distancia,&Less);
    for(int i =0 ; i<8;i++)PQ_InserirEUpdate(pq,i,i);
    for(int i =0 ; i<8;i++)printf("%d\n",PQ_PrimeiroEApaga(pq));
    PQ_Libertar(pq);
    free(distancia);
}

int Less(int A, int B){
    return A<B;
}
int More(int A, int B){
    return A>B;
}