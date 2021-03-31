#include "listaadjacencia.h"

#include <stdlib.h>

#include "Data.h"
#include "aresta.h"
#include "slist.h"

struct _ladj
{
    unsigned int _n_arestas;
    unsigned int* _grau;
    aresta_t**   _array_arestas;
    slist_t**    _array_listas;
};

void    DoNothing(Data data);
void    DoNothing(Data data){}

ladj_t* LA_Alocar(unsigned int vertices, unsigned int arestas){
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
    aux->_grau=(unsigned int*)calloc(vertices,sizeof(unsigned int));
    if(aux->_grau==NULL)exit(1);
    return aux;
}

void    LA_Libertar(ladj_t* ladj,int vertices,int arestas){
    for(int i =0;i<arestas;i++){
        A_Libertar(ladj->_array_arestas[i]);
    }
    free(ladj->_array_arestas);
    for(int i =0;i<vertices;i++){
        SL_FreeList(ladj->_array_listas[i],&DoNothing);
    }
    free(ladj->_array_listas);
    free(ladj->_grau);
    free(ladj);
}

/*Cria uma aresta e insere no array de arestas
  Coloca essa aresta nas listas de adjacencia de a e de b
  incrementa o grau de a e de b
 */
void    LA_InserirAresta(ladj_t* ladj, int a, int b, double custo){
    ladj->_array_arestas[ladj->_n_arestas]= A_Alocar(a,b,custo);
    ladj->_array_listas[a-1]= SL_InsertBefore(ladj->_array_listas[a-1],SL_NewElement(ladj->_array_arestas[ladj->_n_arestas]));
    ladj->_array_listas[b-1]= SL_InsertBefore(ladj->_array_listas[b-1],SL_NewElement(ladj->_array_arestas[ladj->_n_arestas]));
    ladj->_grau[a-1]++;
    ladj->_grau[b-1]++;
    ladj->_n_arestas++;
}

int     LA_Grau(ladj_t* ladj, int a){
    return ladj->_grau[a-1];
}

