#include "matrizadjacencia.h"

#include <stdlib.h>
#include <stdio.h>

#include "pqueue.h"


#define CUSTO(maxvertices,a,b) (double)madj->_matriz[((a-1)*(maxvertices))+(b-1)]
#define ADJACENTE(maxvertices,a,b) ((double)madj->_matriz[((a-1)*(maxvertices))+(b-1)])>0

struct _madj
{
    double*         _matriz; /*Matriz de doubles de ajacencia*/
    int*    _grau;  /*Array com os graus dos vertices para reduzir o seu tempo de computacao*/
    double custo;/*guarda o custo da aresta retirada*/
};



madj_t* MA_Alocar(int vertices){
    madj_t* aux = (madj_t*)malloc(sizeof(madj_t));
    if(aux==NULL){exit(1);}
    aux->_matriz=(double*)calloc((vertices)*(vertices),sizeof(double));
    if(aux->_matriz==NULL){exit(1);}
    aux->_grau=(int*)calloc(vertices,sizeof(int));
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
  O(1)
*/
void    MA_InserirAresta(madj_t* madj,int maxvertices, int a , int b, double custo){
    madj->_matriz[((a-1)*(maxvertices))+(b-1)]=custo;
    madj->_matriz[((b-1)*(maxvertices))+(a-1)]=custo;
    madj->_grau[a-1]++;
    madj->_grau[b-1]++;
}

/*O(1)*/
double    MA_Custo(madj_t* madj,int maxvertices, int a, int b){
    return CUSTO(maxvertices,a,b);
}
/*O(1)*/
int     MA_Grau(madj_t* madj, int a){
    return madj->_grau[a-1];
}
/*O(1)*/
bool    MA_Adjacente(madj_t* madj,int maxvertices, int a, int b){
    return ADJACENTE(maxvertices,a,b);
}

/*O(V^2)*/
int      MA_DistanciaExata(madj_t* madj,int maxvertices, int a , int k){
    int leitura=0;
    int escrita = 0;
    int aux;
    int visitado,grauvisitado;
    bool* visitados = (bool*)calloc(maxvertices,sizeof(bool));
    unsigned int* queue     = (unsigned int*)calloc(maxvertices,sizeof(unsigned int));
    queue[escrita++]=a;  /*colocamos a na queue e incrementamos a posicao da escrita na queue*/
    visitados[a-1]=true; /*marcamos a como vizitado*/
    for(int i=0; i< k;i++){    /*ate chegarmos a profundidade definida*/
        aux=escrita-leitura;
        while(aux>0){           /*para todos os elementos da que nesta profundidade*/
            visitado=queue[leitura++]; /*visitado = queue.pop*/
            grauvisitado=0;
            for(int j=1;j<=maxvertices;j++){
                if(ADJACENTE(maxvertices,visitado,j)){  /*marca como visitados e adiciona a queue todos os vizinhos de de visitado*/
                    if(!(visitados[j-1])){
                        queue[escrita++]=j;
                        visitados[j-1]=true;
                    }
                    grauvisitado++;
                }
                if(grauvisitado==madj->_grau[visitado-1])break;
            }
            aux--;
        }
    }
    free(visitados);
    free(queue);
    return escrita-leitura; /*no fim do processo, todos os elementos na queue sao vertices a distancia k de a*/
}

/*retorna um path entre inicio e fim*/
path_t*    MA_DJIKSTRAS(madj_t* madj,int vertices,int inicio,int fim){
   
    pqueue_t* pq;
    int v,u;
    
    /*Inicializacao de path uma estrututra que huarda o array distancia e o array Anterior*/
    path_t* path = (path_t*)calloc(1,sizeof(path_t));
    path->anterior = (int*)malloc(vertices*sizeof(int));
    path->distancia = (double*)malloc(vertices*sizeof(double));
    for(int i=0;i<vertices;i++){
        path->anterior[i]=-1;
        path->distancia[i]=-1;
    }

    /*inicializacao de uma priority queue que usa como prioridade de v,distancia[v-1]*/
    pq = PQ_Alocar(vertices,path->distancia,&Less);
    
    PQ_InserirFim(pq,inicio-1,0); /*Inserimos o vertice inicial na Priority queue como e o unico fica no inicio da queue garantidamente*/
    
    while (PQ_Size(pq)>0){
        v=PQ_PrimeiroEApaga(pq)+1; /*v e o vertce nao visitado cuja distancia a origem e a menor*/
        if(v==fim){
            PQ_Libertar(pq);
            return(path);
        }
        for(u=1;u<=vertices;u++){  /*para todo os vizinhos de v*/
            if(ADJACENTE(vertices,u,v)){
            if(path->distancia[u-1]==-1){                                                                   /*se o vizinho nao esta na priority queue*/
                PQ_InserirEUpdate(pq,u-1,path->distancia[v-1]+CUSTO(vertices,u,v));    /*colocamo-lo na priority queue e definimos v como antecedente de u*/
                path->anterior[u-1]=v;                                                                  
            }
            else if(! Less(path->distancia[u-1],path->distancia[v-1]+CUSTO(vertices,u,v))){ /*se o vizinho estiver na priority queue e a sua prioridade atual for mairo que a nova prioridade*/
                PQ_MudarPrioridadeEUpdate(pq,u-1,path->distancia[v-1]+CUSTO(vertices,u,v)); /*Atualizamos a sua prioridade para ser a nova prioridade*/
                path->anterior[u-1]=v;                                                                           /*definimos v como o antecedente de u*/
            }
            }
        }
    }
    PQ_Libertar(pq);        /*destruimos a queue pois ja nao e necessaria*/
    return path;            /*retornamos a estrutura path*/
}


/*retorna um path entre inicio e fim que nao passa por vertice*/
path_t*     MA_DJIKSTRAS_VERTICE(madj_t* madj,int vertices,int inicio,int fim,int vertice){
   
    pqueue_t* pq;
    int v,u;
    
    /*Inicializacao de path uma estrututra que huarda o array distancia e o array Anterior*/
    path_t* path = (path_t*)calloc(1,sizeof(path_t));
    path->anterior = (int*)malloc(vertices*sizeof(int));
    path->distancia = (double*)malloc(vertices*sizeof(double));
    for(int i=0;i<vertices;i++){
        path->anterior[i]=-1;
        path->distancia[i]=-1;
    }

    /*inicializacao de uma priority queue que usa como prioridade de v,distancia[v-1]*/
    pq = PQ_Alocar(vertices,path->distancia,&Less);
    
    PQ_InserirFim(pq,inicio-1,0); /*Inserimos o vertice inicial na Priority queue como e o unico fica no inicio da queue garantidamente*/
    
    while (PQ_Size(pq)>0){
        v=PQ_PrimeiroEApaga(pq)+1; /*v e o vertce nao visitado cuja distancia a origem e a menor*/
        if(v==vertice)continue;     /*se v for o vertice a evitar, saltamo-lo*/
        if(v==fim){
            PQ_Libertar(pq);
            return(path);
        }
        for(u=1;u<=vertices;u++){  /*para todo os vizinhos de v*/
            
            if(ADJACENTE(vertices,u,v)){
                
            if(path->distancia[u-1]==-1){                                                       /*se o vizinho nao esta na priority queue*/
                PQ_InserirEUpdate(pq,u-1,path->distancia[v-1]+CUSTO(vertices,u,v));    /*colocamo-lo na priority queue e definimos v como antecedente de u*/
                path->anterior[u-1]=v;                                                                  
            }
            else if(! Less(path->distancia[u-1],path->distancia[v-1]+CUSTO(vertices,u,v))){ /*se o vizinho estiver na priority queue e a sua prioridade atual for mairo que a nova prioridade*/
                PQ_MudarPrioridadeEUpdate(pq,u-1,path->distancia[v-1]+CUSTO(vertices,u,v)); /*Atualizamos a sua prioridade para ser a nova prioridade*/
                path->anterior[u-1]=v;                                                                           /*definimos v como o antecedente de u*/
            }
            }
        }
    }
    PQ_Libertar(pq);        /*destruimos a queue pois ja nao e necessaria*/
    return path;            /*retornamos a estrutura path*/    
}