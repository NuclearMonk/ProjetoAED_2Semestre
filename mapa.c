#include "mapa.h"

#include <stdlib.h>
#include "matrizadjacencia.h"
#include "listaadjacencia.h"
#include "slist.h"
#include <stdio.h>

struct _mapa
{
    int  _tipo;         /*guarda ea informacao da estrutura usada pelo mapa*/
    void*         _estrutura;    /*pointer para a estrutura*/
    int  _maxvertices;
    int  _maxarestas;
    slist_t* arraycaract[26]; /*array listas de inteiros indexado a caracteristica*/
};
void  printvertice(void* vertice);

mapa_t* M_Alocar(int vertices, int arestas){
    mapa_t* aux= (mapa_t*)malloc(sizeof(mapa_t));
    if(aux==NULL){exit(1);}
    if((8*vertices*vertices)<(12+48*arestas+8*vertices)){
    aux->_tipo=1;
    aux->_estrutura= MA_Alocar(vertices);
    }
    else{
    aux->_tipo=2;
    aux->_estrutura=LA_Alocar(vertices,arestas);
    }
    for(int i = 0; i<26;i++){
        aux->arraycaract[i]=SL_Initialize();
    }
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
    case 2:
        LA_Libertar((ladj_t*)mapa->_estrutura,mapa->_maxvertices);
        break;
    default:
        break;
    }
    for(int i=0;i<26;i++){
    SL_Apply(mapa->arraycaract[i], &printvertice);
    printf("\n%d ", i);
    SL_FreeList(mapa->arraycaract[i],&free);
    }
    free(mapa);
}

void    M_InserirAresta(mapa_t* mapa, int a, int b , double custo){
    if(!((0<a && a<= mapa->_maxvertices) && (0<b && b<=mapa->_maxvertices)))return;
    switch (mapa->_tipo)
    {
    case 1:
        MA_InserirAresta((madj_t*)mapa->_estrutura,mapa->_maxvertices,a,b,custo);
        break;
    case 2:
        LA_InserirAresta((ladj_t*)mapa->_estrutura,a,b,custo);
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
    case 2:
        return LA_Grau((ladj_t*)mapa->_estrutura,vertice);
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
    case 2:
        return LA_Custo((ladj_t*)mapa->_estrutura,a,b);
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

/*modo D0 retorna o numero de vertices a distancia exata k de verticeinicial
 *retorna -1 se o verticeinicial nao pertencer ao mapa;
 */
int     M_NumeroVerticesDistanciaExata(mapa_t* mapa, int verticeinicial , int k){
    if(!(0<verticeinicial && verticeinicial<= mapa->_maxvertices))return -1;
    if(k<0)return 0;
    switch (mapa->_tipo)
    {
    case 1:
        return MA_DistanciaExata((madj_t*)mapa->_estrutura, mapa->_maxvertices, verticeinicial, k);
        break;
     case 2:
        return LA_DistanciaExata((ladj_t*)mapa->_estrutura, mapa->_maxvertices, verticeinicial, k);
    default:
        break;
    }
    return -1;
}

/*Retorna 1 se existem vertices a distancia exata k de verticeinicial
 *Retorna 0 se nao existirem
 *Retorna -1 se verticeinicial nao pertencer ao mapa 
 */
int    M_ExistemVerticesDistanciaExata(mapa_t* mapa, int verticeinicial , int k){
    if(!(0<verticeinicial && verticeinicial<= mapa->_maxvertices))return -1;
    if (M_NumeroVerticesDistanciaExata(mapa, verticeinicial, k) >= 1)return 1;
    return 0; 
}

int    M_GetMaxArestas(mapa_t* mapa){
    return mapa->_maxarestas;
}

int    M_GetMaxVertices(mapa_t* mapa){
    return mapa->_maxvertices;
}

void M_InsereCarateristica(mapa_t* mapa,char caracteristicas[27],int vertice){
    if(caracteristicas != NULL)return;
    int i=0, aux;
    printf("%s", caracteristicas);
    while(caracteristicas[i]!= '\0'){
        if(caracteristicas[i]=='-' ||caracteristicas[i]<'a' || caracteristicas[i]>'z')return;
        aux = malloc(sizeof(int));
        aux = vertice;
        mapa->arraycaract[(int)caracteristicas[i]-'a']=SL_InsertBefore(mapa->arraycaract[(int)caracteristicas[i]-'a'],SL_NewElement(aux));
        i++;
    }
    return;
}

void  printvertice(void* vertice){
    printf("%d", vertice);
}