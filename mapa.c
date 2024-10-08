#include "mapa.h"

#include <stdlib.h>
#include "matrizadjacencia.h"
#include "listaadjacencia.h"
#include "slist.h"

struct _mapa
{
    int  _tipo;         /*guarda ea informacao da estrutura usada pelo mapa*/
    void*         _estrutura;    /*pointer para a estrutura*/
    int  _maxvertices;
    int  _maxarestas;
    slist_t* _arraycaracteristicas[26]; /*array listas de inteiros indexado a caracteristica*/
};

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
        aux->_arraycaracteristicas[i]=SL_Initialize();
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
    for(int i=0;i<26;i++){                  /*liberta o array de caracteristica*/
    SL_FreeList(mapa->_arraycaracteristicas[i],&free);
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
    case 2:
        return LA_Adjacente((ladj_t*)mapa->_estrutura,a,b);
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

void M_InsereCaracteristica(mapa_t* mapa,char caracteristicas[27],int vertice){
    if(caracteristicas == NULL)return;
    int i=0;
    int* aux;
    /*inserimos o verice na cabeca das respetivas listas*/
    while(caracteristicas[i]!= '\0'){
        if(caracteristicas[i]=='-' ||caracteristicas[i]<'a' || caracteristicas[i]>'z')return;
        aux = (int*)malloc(sizeof(int));
        *aux = vertice;
        mapa->_arraycaracteristicas[((int)caracteristicas[i]-'a')]=SL_InsertBefore(mapa->_arraycaracteristicas[((int)caracteristicas[i]-'a')],SL_NewElement((void*)aux));
        i++;
    }
    return;
}

slist_t*  M_GetCidadesCaracteristica(mapa_t* mapa, int caracteristica){
    return mapa->_arraycaracteristicas[caracteristica];
}

path_t*   M_DJIKSTRAS(mapa_t* mapa, int a, int b){
    if(!((0<a && a<= mapa->_maxvertices) && (0<b && b<=mapa->_maxvertices)))return NULL;
    if(a==b)return NULL;
    switch (mapa->_tipo)
    {
    case 1:
        return MA_DJIKSTRAS((madj_t*)mapa->_estrutura,mapa->_maxvertices,a,b);
        break;
    case 2:
        return LA_DJIKSTRAS((ladj_t*)mapa->_estrutura, mapa->_maxvertices,a,b);
        break;
    
    default:
        break;
    }
    return NULL;
}

path_t*   M_DJIKSTRAS_VERTICE(mapa_t* mapa, int a, int b, int vertice){
    if(!((0<a && a<= mapa->_maxvertices) && (0<b && b<=mapa->_maxvertices)))return NULL;
    if(vertice <=0|| vertice> mapa->_maxvertices)return NULL;
    if(a==b)return NULL;
    if(vertice==a|| vertice == b)return NULL;
    switch (mapa->_tipo)
    {
    case 1:
        return MA_DJIKSTRAS_VERTICE((madj_t*)mapa->_estrutura,mapa->_maxvertices,a,b,vertice);
        break;
    case 2:
        return LA_DJIKSTRAS_VERTICE((ladj_t*)mapa->_estrutura, mapa->_maxvertices,a,b,vertice);
        break;
    default:
        break;
    }
    return NULL;
}

path_t*   M_DJIKSTRAS_ARESTA(mapa_t* mapa, int a, int b, int vertice1, int vertice2){
    double custo;
    path_t* path;
    if(!((0<a && a<= mapa->_maxvertices) && (0<b && b<=mapa->_maxvertices)))return NULL;
    if(vertice1 <=0 || vertice1 > mapa->_maxvertices || vertice2 <=0|| vertice2 > mapa->_maxvertices)return NULL;
    if(a==b)return NULL;
    switch (mapa->_tipo)
    {
    case 1:
        custo=MA_Custo((madj_t*)mapa->_estrutura, mapa->_maxvertices, vertice1, vertice2);          /*Guardamos o custo*/
        MA_InserirAresta((madj_t*)mapa->_estrutura, mapa->_maxvertices, vertice1 , vertice2, 0);    /*retiramos a aresta definindo o seu custo a zero*/
        path = MA_DJIKSTRAS((madj_t*)mapa->_estrutura,mapa->_maxvertices,a,b);                      /*Caminho sem a aresta*/
        MA_InserirAresta((madj_t*)mapa->_estrutura, mapa->_maxvertices, vertice1 , vertice2, custo);/*Repor a aresta*/
        return path;
        break;
    case 2:
        return LA_DJIKSTRAS_ARESTA((ladj_t*)mapa->_estrutura, mapa->_maxvertices, a, b, vertice1, vertice2);
        break;
    default:
        break;
    }
    return NULL;
}

path_t*   M_DJIKSTRAS_DESVIO(mapa_t* mapa, int a,int b,int carateristica){
    if(!((0<a && a<= mapa->_maxvertices) && (0<b && b<=mapa->_maxvertices)))return NULL;
    switch(mapa->_tipo){
        case 1:
            return MA_DJIKSTRAS_DESVIO((madj_t*)mapa->_estrutura,mapa->_maxvertices,a,b,mapa->_arraycaracteristicas[carateristica]);
            break;
        case 2:
            return LA_DJIKSTRAS_DESVIO((ladj_t*)mapa->_estrutura, mapa->_maxvertices, a, b, mapa->_arraycaracteristicas[carateristica]);
            break;
        default:
            break;
    }
    return NULL;
}