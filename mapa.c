#include "mapa.h"

#include <stdlib.h>
#include "matrizadjacencia.h"
#include <stdio.h>

struct _mapa
{
    unsigned int  _tipo;         /*guarda ea informacao da estrutura usada pelo mapa*/
    void*         _estrutura;    /*pointer para a estrutura*/
    unsigned int  _maxvertices;
    unsigned int  _maxarestas;
};

mapa_t* M_Aloca(int vertices, int arestas){
    mapa_t* aux= (mapa_t*)malloc(sizeof(mapa_t));
    if(aux==NULL){exit(1);}
    aux->_tipo=1;
    aux->_estrutura= MA_Alocar(vertices);
    aux->_maxvertices=vertices;
    aux->_maxarestas=arestas;
    return aux;
}

void M_Libertar(mapa_t* mapa){
    switch (mapa->_tipo)
    {
    case 1:
        MA_Libertar((madj_t*)mapa->_estrutura);
        break;
    
    default:
        break;
    }
    free(mapa);
}

void    M_ArestaInsere(mapa_t* mapa, int a, int b , double custo){
    if(!((0<a && a<= mapa->_maxvertices) && (0<b && b<=mapa->_maxvertices)))return;
    switch (mapa->_tipo)
    {
    case 1:
        MA_InserirAresta((madj_t*)mapa->_estrutura,mapa->_maxvertices,a,b,custo);
        break;
    
    default:
        break;
    }
}

/*Retorna -1 quando o vertice nao pertence ao grafo
  Retorna grau do vertice em todos os outros casos  
*/
int     M_Grau(mapa_t* mapa,int vertice){
    if(!((0<vertice && vertice<= mapa->_maxvertices)))return -1;
    switch (mapa->_tipo)
    {
    case 1:
        return MA_Grau((madj_t*)mapa->_estrutura,vertice);
        break;
    
    default:
        return -1;
        break;
    }
}

/*retorna -1 caso os vertices nao pertencam ao grafo*/
double  M_Custo(mapa_t* mapa, int a, int b){
    if(!((0<a && a<= mapa->_maxvertices) && (0<b && b<=mapa->_maxvertices)))return -1;
    switch (mapa->_tipo)
    {
    case 1:
        return MA_Custo((madj_t*)mapa->_estrutura,mapa->_maxvertices,a,b);
        break;
    
    default:
        return -1;
        break;
    }
    return -1;
}


/*retorna -1 quando um dos vertices nao pertence ao grafo
  retorna  0 se pertencem mas nao sao adjacentes
  retorna  1 se sao ajacentes
*/
int    M_Adjacente(mapa_t* mapa, int a, int b){
    if(!((0<a && a<= mapa->_maxvertices) && (0<b && b<=mapa->_maxvertices)))return -1;
    switch (mapa->_tipo)
    {
    case 1:
        return MA_Adjacente((madj_t*)mapa->_estrutura,mapa->_maxvertices,a,b);
        break;
    
    default:
        break;
    }
    return false;
}

int     M_DistanciaExata(mapa_t* mapa, int a , int k){
    if(!(0<a && a<= mapa->_maxvertices))return -1;
    switch (mapa->_tipo)
    {
    case 1:
        return MA_DistanciaExata((madj_t*)mapa->_estrutura, mapa->_maxvertices, a, k);
        break;
    
    default:
        break;
    }
    return -1;
}