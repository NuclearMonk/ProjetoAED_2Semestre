#ifndef _LADJ_H
#define _LADJ_H

#include <stdbool.h>
#include "pathfinding.h"
#include "slist.h"

typedef struct _ladj ladj_t;
typedef struct _aresta aresta_t;

/*funcoes de Listas de adjacencia*/
ladj_t* LA_Alocar(int vertices,int arestas);
void    LA_Libertar(ladj_t* ladj, int vertices);
void    LA_InserirAresta(ladj_t* ladj, int a, int b, double custo);
double  LA_Custo(ladj_t* ladj, int a, int b);
int     LA_DistanciaExata(ladj_t* madj,int maxvertices, int a, int k);
int     LA_Grau(ladj_t* ladj, int a);
bool    LA_Adjacente(ladj_t* ladj, int a, int b);
path_t* LA_DJIKSTRAS(ladj_t* ladj,int vertices,int inicio, int fim);
path_t* LA_DJIKSTRAS_VERTICE(ladj_t* ladj,int vertices,int inicio, int fim,int vertice);
path_t* LA_DJIKSTRAS_ARESTA(ladj_t* ladj,int vertices,int inicio, int fim,int a, int b);
path_t* LA_DJIKSTRAS_DESVIO(ladj_t* ladj,int vertices, int inicio,int destino, slist_t* cidadescategoria);
/*Funcoes de arestas*/
void    A_Preencher(aresta_t* aresta,int a, int b,double custo); 
int     A_A(aresta_t* aresta);
int     A_B(aresta_t* aresta);
double  A_Custo(aresta_t* aresta);
int     A_Outro(aresta_t* aresta, int vertice);

#endif