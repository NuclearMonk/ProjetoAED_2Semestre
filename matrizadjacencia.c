#include "matrizadjacencia.h"

#include <stdlib.h>
#include <stdio.h>

struct _madj
{
    double*         _matriz; /*Matriz de doubles de ajacencia*/
    unsigned int*    _grau;  /*Array com os graus dos vertices para reduzir o seu tempo de computacao*/
};



madj_t* MA_Alocar(int vertices){
    madj_t* aux = (madj_t*)malloc(sizeof(madj_t));
    if(aux==NULL){exit(1);}
    aux->_matriz=(double*)calloc((vertices)*(vertices),sizeof(double));
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
    madj->_matriz[((a-1)*(maxvertices))+(b-1)]=custo;
    madj->_matriz[((b-1)*(maxvertices))+(a-1)]=custo;
    madj->_grau[a-1]++;
    madj->_grau[b-1]++;
}

double    MA_Custo(madj_t* madj,int maxvertices, int a, int b){
    return (double)madj->_matriz[((a-1)*(maxvertices))+(b-1)];
}

int     MA_Grau(madj_t* madj, int a){
    return madj->_grau[a-1];
}

bool    MA_Adjacente(madj_t* madj,int maxvertices, int a, int b){
    return ((double)madj->_matriz[((a-1)*(maxvertices))+(b-1)]>0);
}

int      MA_DistanciaExata(madj_t* madj,int maxvertices, int a , int k){
    int leitura=0;
    int escrita = 0;
    int aux;
    int visitado;
    bool* visitados = (bool*)calloc(maxvertices,sizeof(bool));
    unsigned int* queue     = (unsigned int*)calloc(maxvertices,sizeof(unsigned int));
    queue[escrita++]=a;  /*colocamos a na queue e incrementamos a posicao da escrita na queue*/
    visitados[a-1]=true; /*marcamos a como vizitado*/
    for(int i=0; i< k;i++){    /*ate chegarmos a profundidade definida*/
        aux=escrita-leitura;
        while(aux>0){           /*para todos os elementos da que nesta profundidade*/
            visitado=queue[leitura++]; /*visitado = queue.pop*/
            for(int j=1;j<=maxvertices;j++){
                if(MA_Adjacente(madj,maxvertices,visitado,j)){  /*marca como visitados e adiciona a queue todos os vizinhos de de visitado*/
                    if(!(visitados[j-1])){
                        queue[escrita++]=j;
                        visitados[j-1]=true;
                    }
                }
            }
            aux--;
        }
    }
    free(visitados);
    free(queue);
    return escrita-leitura; /*no fim do processo, todos os elementos na queue sao vertices a distancia k de a*/
}