#ifndef _MAPA_H
#define _MAPA_H

#include <stdbool.h>

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

#endif