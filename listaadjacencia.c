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
    int _n_arestas;
    int* _grau;
    aresta_t*   _array_arestas;
    slist_t**    _array_listas;
};



void    DoNothing(Data data);
void    DoNothing(Data data){data=data;}

ladj_t* LA_Alocar(int vertices,int arestas){
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
    aux->_grau=(int*)calloc(vertices,sizeof(int));
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
  O(1)
 */
void    LA_InserirAresta(ladj_t* ladj, int a, int b, double custo){
    A_Preencher(&ladj->_array_arestas[ladj->_n_arestas],a,b,custo);
    ladj->_array_listas[a-1]= SL_InsertBefore(ladj->_array_listas[a-1],SL_NewElement(&ladj->_array_arestas[ladj->_n_arestas]));
    ladj->_array_listas[b-1]= SL_InsertBefore(ladj->_array_listas[b-1],SL_NewElement(&ladj->_array_arestas[ladj->_n_arestas]));
    ladj->_grau[a-1]++;
    ladj->_grau[b-1]++;
    ladj->_n_arestas++;
}

/*O(V) pode ser mitigado quando se keem todos os vizinhoss*/
double  LA_Custo(ladj_t* ladj, int a, int b){
    slist_t* aux;
    aresta_t* auxaresta=NULL;
    if(ladj->_grau[a-1]<ladj->_grau[b-1]){
        for(aux= ladj->_array_listas[a-1];aux !=NULL; aux=SL_GetNext(aux)){
            auxaresta= (aresta_t*)SL_GetData(aux);
            if(A_Outro(auxaresta,a)==b){
                return A_Custo(auxaresta);
            }
        }
    }
    else{
        for(aux= ladj->_array_listas[b-1];aux !=NULL; aux=SL_GetNext(aux)){
            auxaresta= (aresta_t*)SL_GetData(aux);
            if(A_Outro(auxaresta,b)==a){
                return A_Custo(auxaresta);
            }
        }
    }
    return -1;
}
/*O(V*E)*/
int      LA_DistanciaExata(ladj_t* ladj, int maxvertices, int verticeinicial,int k){
    int leitura=0;
    int escrita = 0;
    int aux;
    int b;
    int v=0;
    slist_t* auxlista;
    bool* visitados = (bool*)calloc(maxvertices,sizeof(bool));
    unsigned int* queue = (unsigned int*)calloc(maxvertices,sizeof(unsigned int));
    queue[escrita++]=verticeinicial;  /*colocamos a na queue e incrementamos a posicao da escrita na queue*/
    visitados[verticeinicial-1]=true; /*marcamos a como vizitado*/
    for(int i=0; i< k;i++){    /*ate chegarmos a profundidade definida*/
        aux=escrita-leitura;
        while(aux>0){     
            v=queue[leitura++];/*para todos os elementos da que nesta profundidade*/
            for(auxlista=ladj->_array_listas[v-1]; auxlista != NULL; auxlista=SL_GetNext(auxlista)){
                b = A_Outro((aresta_t*)SL_GetData(auxlista),v);
                if(visitados[b-1] == false){
                    queue[escrita++]=b;
                    visitados[b-1]=true;
                }
            }
            aux--;
        }
    }
    free(visitados);
    free(queue);
    return escrita-leitura;
}

int     LA_Grau(ladj_t* ladj, int a){
    return ladj->_grau[a-1];
}

bool    LA_Adjacente(ladj_t* ladj, int a, int b){
    if(LA_Custo(ladj, a, b)!=-1){return true;}
    return false;
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