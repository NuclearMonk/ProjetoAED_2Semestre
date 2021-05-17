#ifndef _MADJ_H
#define _MADJ_H

#include <stdbool.h>
#include "pathfinding.h"
#include "slist.h"

typedef struct _madj madj_t;

madj_t*     MA_Alocar(int vertices);
void        MA_Libertar(madj_t* madj);

void        MA_InserirAresta(madj_t* madj, int maxvertices, int a , int b, double custo);

double      MA_Custo(madj_t* madj,int maxvertices, int a, int b);

int         MA_Grau(madj_t* madj, int a);

bool        MA_Adjacente(madj_t* madj,int maxvertices, int a, int b);

int         MA_DistanciaExata(madj_t* madj,int maxvertices, int a , int k);

path_t*     MA_DJIKSTRAS(madj_t* madj,int vertices,int inicio,int fim);

path_t*     MA_DJIKSTRAS_VERTICE(madj_t* madj,int vertices,int inicio,int fim,int vertice);

path_t*     MA_DJIKSTRAS_DESVIO(madj_t* madj,int vertices, int inicio,int destino, slist_t* cidadescategoria);

#endif