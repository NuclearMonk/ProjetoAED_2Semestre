#include <stdlib.h>

#include "cabecalho.h"

struct _cabecalho{
    int _problema;
    int _inicial;
    int _final;
    int _flag;
    double _desvio;
};


/*aloca estrutura para guardar cabecalho de problemas*/
cabecalho_t* C_Alocar(){
    cabecalho_t* aux = (cabecalho_t*)malloc(sizeof(cabecalho_t));
    if( aux==NULL ){
        exit(1);
    }
    aux->_problema=0;
    aux->_inicial=0;
    aux->_final=0;
    aux->_flag=0;
    aux->_desvio=0;
    return aux;
}


/*liberta a estrutura de cabecalho*/
void         C_Libertar(cabecalho_t* cabecalho){
    free(cabecalho);
}


/*Retorna 
 1 para A0
 2 para B0
 3 para C0
 4 para D0
 5 para A1
 6 para B1
 7 para C1
 8 para D1
 */
int         C_GetProblema(cabecalho_t* cabecalho){
    return cabecalho->_problema;
}

/*coloca problema em cabecalho*/
void        C_SetProblema(cabecalho_t* cabecalho,int problema){
    cabecalho->_problema=problema;
}

/*Retotna o Vi do problema*/
int         C_GetVInicial(cabecalho_t* cabecalho){
    return cabecalho->_inicial;
}

/*Define o Vi do problema*/
void        C_SetVInicial(cabecalho_t* cabecalho,int inicial){
    cabecalho->_inicial=inicial;
}

/*Retotna o Vj do problema*/
int         C_GetVFinal(cabecalho_t* cabecalho){
    return cabecalho->_final;
}

/*Define o Vj do problema*/
void        C_SetVFinal(cabecalho_t* cabecalho,int final){
    cabecalho->_final=final;
}

/*Retorna 
*k em C0 e D0
*a flag de cidade do problema co a=0 e z=25
*/
int         C_GetFlag(cabecalho_t* cabecalho){
    return cabecalho->_flag;
}

/*Define 
*k em C0 e D0
*a flag de cidade do problema co a=0 e z=25
*/
void        C_SetFlag(cabecalho_t* cabecalho,int flag){
    cabecalho->_flag=flag;
}

/*Retorna o desvio maximo do caminho definido para o problema B1*/
double      C_GetDesvio(cabecalho_t* cabecalho){
    return cabecalho->_desvio;
}

/*Define o desvio maximo do caminho definido para o problema B1*/
void        C_SetDesvio(cabecalho_t* cabecalho,double desvio){
    cabecalho->_desvio=desvio;
}