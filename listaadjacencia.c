#include "listaadjacencia.h"

#include <stdlib.h>

#include "Data.h"
#include "aresta.h"
#include "slist.h"

struct _ladj
{
    unsigned int _n_arestas;
    aresta_t**   _array_arestas;
    slist_t**    _array_listas;
};

void DoNothing(Data data);

ladj_t* LA_Aloca(unsigned int vertices, unsigned int arestas){
    ladj_t* aux = (ladj_t*)malloc(sizeof(ladj_t));
    if(aux==NULL)exit(1);
    aux->_n_arestas=0;
    aux->_array_arestas= (aresta_t**)malloc(arestas*sizeof(aresta_t*));
    if(aux->_array_arestas==NULL)exit(1);
    aux->_array_listas=(slist_t**)malloc(sizeof(vertices*sizeof(slist_t*)));
    if(aux->_array_listas==NULL)exit(1);
    for(int i = 0; i<vertices;i++){
        aux->_array_listas[i]=SL_Initialize();
    }
    return aux;
}
void    LA_Liberta(ladj_t* ladj,int vertices,int arestas){
    for(int i =0;i<arestas;i++){
        A_Libertar(ladj->_array_arestas[i]);
    }
    free(ladj->_array_arestas);
    for(int i =0;i<vertices;i++){
        SL_FreeList(ladj->_array_listas[i],&DoNothing);
    }
    free(ladj->_array_listas);
    free(ladj);
}
void    LA_InserirAresta(ladj_t* ladj, int a, int b, double custo){
    ladj->_array_arestas[ladj->_n_arestas]= A_Alocar(a,b,custo);
    ladj->_array_listas[a-1]= SL_InsertBefore(ladj->_array_listas[a-1],SL_NewElement(ladj->_array_arestas[ladj->_n_arestas]));
    ladj->_array_listas[b-1]= SL_InsertBefore(ladj->_array_listas[b-1],SL_NewElement(ladj->_array_arestas[ladj->_n_arestas]));
    ladj->_n_arestas++;
}
void DoNothing(Data data){
}