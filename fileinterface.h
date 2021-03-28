#include <stdio.h>  /*necessario para usar files*/

#include "cabecalho.h"
#include "mapa.h"

cabecalho_t* le_cabecalho_prob(FILE *fpprob);
mapa_t*      le_mapa(FILE *fpprob);
void         le_cidade(FILE *fpprob,mapa_t* mapa);
void         le_aresta(FILE *fpprob,mapa_t* mapa);

