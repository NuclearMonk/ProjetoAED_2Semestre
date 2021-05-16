#ifndef _MAPA_H
#define _MAPA_H

#include <stdbool.h>
#include "pathfinding.h"
/*Tipo abstrato, tanto pode ser uma matriz de adjacencia ou uma lista de adjacencia*/
typedef struct _mapa mapa_t;

mapa_t* M_Alocar(int vertices, int arestas);
void    M_Libertar(mapa_t* mapa);

void    M_InserirAresta(mapa_t* mapa, int a, int b , double custo);

double  M_Custo(mapa_t* mapa, int a, int b);

int     M_Grau(mapa_t* mapa,int vertice);

int     M_Adjacente(mapa_t* mapa, int a, int b);

int     M_NumeroVerticesDistanciaExata(mapa_t* mapa, int a , int k);

int    M_ExistemVerticesDistanciaExata(mapa_t* mapa, int a , int k);

int    M_GetMaxArestas(mapa_t* mapa);

int    M_GetMaxVertices(mapa_t* mapa);

void   M_InsereCaracteristica(mapa_t* mapa, char caracteristica[27], int vertice);

path_t*   M_DJIKSTRAS(mapa_t* mapa, int a,int b);

path_t*   M_DJIKSTRAS_VERTICE(mapa_t* mapa, int a, int b, int vertice);

path_t*   M_DJIKSTRAS_ARESTA(mapa_t* mapa, int a, int b, int vertice1, int vertice2);

#endif