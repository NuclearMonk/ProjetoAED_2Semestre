#include "matrizadjacencia.h"

#include <stdlib.h>

struct _madj
{
    int _maxvertices;
    double* _matriz;
};


madj_t* MA_Alocar(int vertices){
    madj_t* aux = (madj_t*)malloc(sizeof(madj_t));
    if(aux==NULL){
        exit(1);
    }
    aux->_maxvertices=vertices;
    aux->_matriz= (double*)sizeof((vertices-1)*(vertices-1)*sizeof(double));
    if(aux->_matriz==NULL){
        exit(1);
    }
    return aux;
}
void    MA_Libertar(madj_t* madj){
    free(madj->_matriz);
    free(madj);
}

void    MA_InserirAresta(madj_t* madj, int a , int b, double custo){
    madj->_matriz[((a-1)/(madj->_maxvertices))+(b-1)]=custo;
    madj->_matriz[((b-1)/(madj->_maxvertices))+(a-1)]=custo;
}

double    MA_Custo(madj_t* madj, int a, int b){
    return (madj->_matriz[((a-1)/(madj->_maxvertices))+(b-1)]);
}
bool    MA_Adjacente(madj_t* madj, int a, int b){
    return (madj->_matriz[((a-1)/(madj->_maxvertices))+(b-1)]>0);
}