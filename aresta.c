#include <stdlib.h>
#include "aresta.h"

struct _aresta
{
    int _a;
    int _b;
    double _custo;
};


/*
 *Aloca uma aresta e coloca nela os valores passados como parametros
 *Faz exit se a allocacao nao ocorrer
 */
aresta_t* A_Alocar(int a,int b,double custo){
    aresta_t* aux = (aresta_t*)malloc(sizeof(aresta_t));
    if(aux==NULL)exit(1);
    aux->_a=a;
    aux->_b=b;
    aux->_custo=custo;
    return aux;
}


/*Liberta Aresta*/
void A_Libertar(aresta_t* aresta){
    free(aresta);
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