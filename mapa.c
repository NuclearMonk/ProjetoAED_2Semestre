#include "mapa.h"

#include <stdlib.h>
#include "matrizadjacencia.h"

struct _mapa
{
    unsigned int _tipo;         /*guarda ea informacao da estrutura usada pelo mapa*/
    void*        _estrutura;    /*pointer para a estrutura*/
    unsigned int _maxvertices;
    unsigned int _maxarestas;
};

mapa_t* M_Aloca(int vertices, int arestas){
    mapa_t* aux= (mapa_t*)malloc(sizeof(mapa_t));
    aux->_tipo=1;
    aux->_estrutura= MA_Alocar(vertices);
    aux->_maxvertices=vertices;
    aux->_maxarestas=arestas;
    if(aux==NULL){exit(1);}
    return aux;
}

void M_Libertar(mapa_t* mapa){
    /*Todo libertar a estrutura do mapa*/
    free(mapa);
}

void    M_ArestaInsere(mapa_t* mapa, int a, int b , double custo){
    switch (mapa->_tipo)
    {
    case 1:
        MA_InserirAresta((madj_t)mapa->_estrutura,mapa->_maxvertices,a,b,custo);
        break;
    
    default:
        break;
    }
}


bool    M_Adjacente(mapa_t* mapa, int a, int b){
    switch (mapa->_tipo)
    {
    case 1:
        return MA_Adjacente((madj_t)mapa->_estrutura,mapa->_maxvertices,a,b);
        break;
    
    default:
        break;
    }
}