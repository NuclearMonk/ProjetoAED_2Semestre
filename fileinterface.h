#ifndef _FILEINTERFACE_H
#define _FILEINTERFACE_H
#include <stdio.h> 

#include "cabecalho.h"
#include "mapa.h"

cabecalho_t* Le_cabecalho_prob(FILE *fpprob);
mapa_t*      Le_mapa(FILE *fpprob);
void         Le_cidade(FILE *fpprob,mapa_t* mapa);
void         Le_aresta(FILE *fpprob,mapa_t* mapa, int maxvertices);
FILE*        Abre_ficheiro_prob(char *ficheiroprob);
FILE*        Abre_ficheiro_mapa(char *ficheiromapa);
FILE*        Abre_ficheiro_saida(char *ficheiromapa);
void         Resolve_problema(FILE *fp_saida, mapa_t* mapa, cabecalho_t* cabecalho);

#endif