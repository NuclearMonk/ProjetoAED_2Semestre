#include <stdio.h>  /*necessario para usar files*/

#include "cabecalho.h"
#include "mapa.h"

cabecalho_t* le_cabecalho_prob(FILE *fpprob);
mapa_t*      le_mapa(FILE *fpprob);
void         le_cidade(FILE *fpprob,mapa_t* mapa);
void         le_aresta(FILE *fpprob,mapa_t* mapa, int maxvertices);
void         printmapa(mapa_t* mapa, int a, int b);
FILE*        abre_ficheiro_prob(char *ficheiroprob);
FILE*        abre_ficheiro_mapa(char *ficheiromapa);
FILE*        abre_ficheiro_saida(char *ficheiromapa);
void         resolve_problema(FILE *Fsaida, mapa_t* mapa, cabecalho_t* cabecalho);

