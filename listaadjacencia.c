#include "listaadjacencia.h"

#include <stdlib.h>

#include "Data.h"
#include "slist.h"
#include <stdio.h>

struct _aresta
{
    int _a;
    int _b;
    double _custo;
};

struct _ladj
{
    unsigned int _n_arestas;
    unsigned int* _grau;
    aresta_t*   _array_arestas;
    slist_t**    _array_listas;
};



void    DoNothing(Data data);
void    DoNothing(Data data){}

ladj_t* LA_Alocar(unsigned int vertices, unsigned int arestas){
    ladj_t* aux = (ladj_t*)malloc(sizeof(ladj_t));
    if(aux==NULL)exit(1);
    aux->_n_arestas=0;
    aux->_array_arestas= (aresta_t*)calloc(arestas,sizeof(aresta_t));
    if(aux->_array_arestas==NULL)exit(1);
    aux->_array_listas=(slist_t**)malloc(vertices*sizeof(slist_t*));
    if(aux->_array_listas==NULL)exit(1);
    for(int i = 0; i<vertices;i++){
        aux->_array_listas[i]=SL_Initialize();
    }
    aux->_grau=(unsigned int*)calloc(vertices,sizeof(unsigned int));
    if(aux->_grau==NULL)exit(1);
    return aux;
}

void    LA_Libertar(ladj_t* ladj,int vertices){
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
    A_Preencher(&ladj->_array_arestas[ladj->_n_arestas],a,b,custo);
    ladj->_array_listas[a-1]= SL_InsertBefore(ladj->_array_listas[a-1],SL_NewElement(&ladj->_array_arestas[ladj->_n_arestas]));
    ladj->_array_listas[b-1]= SL_InsertBefore(ladj->_array_listas[b-1],SL_NewElement(&ladj->_array_arestas[ladj->_n_arestas]));
    ladj->_grau[a-1]++;
    ladj->_grau[b-1]++;
    ladj->_n_arestas++;
}


double  LA_Custo(ladj_t* ladj, int a, int b){
    slist_t* aux;
    if(ladj->_grau[a-1]<ladj->_grau[b-1]){
        for(aux= ladj->_array_listas[a-1];aux !=NULL; aux=SL_GetNext(aux)){
            if(A_Outro((aresta_t*)SL_GetData(aux),a)==b){
                return A_Custo((aresta_t*)SL_GetData(aux));
            }
        }
    }
    else{
        for(aux= ladj->_array_listas[b-1];aux !=NULL; aux=SL_GetNext(aux)){
            if(A_Outro((aresta_t*)SL_GetData(aux),b)==a){
                return A_Custo((aresta_t*)SL_GetData(aux));
            }
        }
    }
    return -1;
}


int     LA_Grau(ladj_t* ladj, int a){
    return ladj->_grau[a-1];
}


/*
 *Aloca uma aresta e coloca nela os valores passados como parametros
 *Faz exit se a allocacao nao ocorrer
 */
void A_Preencher(aresta_t* aresta, int a,int b,double custo){
    aresta->_a=a;
    aresta->_b=b;
    aresta->_custo=custo;
}



/*retorna a de aresta*/
int A_A(aresta_t* aresta){
    return aresta->_a;
}

/*retorna b de aresta*/
int A_B(aresta_t* aresta){
    return aresta->_b;
}

/*retorna custo de aresta*/
double A_Custo(aresta_t* aresta){
    return aresta->_custo;
}

/*Se vertice existe na aresta retorna o outro vertice que esta na aresta
 *Se vertice n existir retorna -1
 */
int       A_Outro(aresta_t* aresta, int vertice){
    if(vertice==aresta->_a)
    {
        return aresta->_b;
    }
    else if(vertice == aresta->_b)
    {
        return aresta->_a;
    }
    else
    { 
        return -1;
    }
}