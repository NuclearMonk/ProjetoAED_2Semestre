#include "matrizadjacencia.h"

#include <stdlib.h>

struct _madj
{
    double*         _matriz; /*Matriz de doubles de ajacencia*/
    unsigned int*    _grau;  /*Array com os graus dos vertices para reduzir o seu tempo de computacao*/
};



madj_t* MA_Alocar(int vertices){
    madj_t* aux = (madj_t*)malloc(sizeof(madj_t));
    if(aux==NULL){exit(1);}
    aux->_matriz=(double*)calloc((vertices-1)*(vertices-1),sizeof(double));
    if(aux->_matriz==NULL){exit(1);}
    aux->_grau=(unsigned int*)calloc(vertices,sizeof(unsigned int));
    if(aux->_grau==NULL){exit(1);}    
    return aux;
}


void    MA_Libertar(madj_t* madj){
    free(madj->_matriz);
    free(madj->_grau);
    free(madj);
}

/*define matriz[a][b] e matriz[b][a] com o custo fornecido
  incrementa os graus de a e b
*/
void    MA_InserirAresta(madj_t* madj,int maxvertices, int a , int b, double custo){
    madj->_matriz[((a-1)*(maxvertices-1))+(b-1)]=custo;
    madj->_matriz[((b-1)*(maxvertices)-1)+(a-1)]=custo;
    madj->_grau[a-1]++;
    madj->_grau[b-1]++;
}

double    MA_Custo(madj_t* madj,int maxvertices, int a, int b){
    return (double)madj->_matriz[((a-1)*(maxvertices-1))+(b-1)];
}

int     MA_Grau(madj_t* madj, int a){
    return madj->_grau[a-1];
}

bool    MA_Adjacente(madj_t* madj,int maxvertices, int a, int b){
    return ((double)madj->_matriz[((a-1)*(maxvertices-1))+(b-1)]>0);
}