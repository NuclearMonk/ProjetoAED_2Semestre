#include "mapa.h"

#include <stdlib.h>


struct _mapa
{
    unsigned int _tipo;         /*guarda ea informacao da estrutura usada pelo mapa*/
    void*        _estrutura;    /*pointer para a estrutura*/
};

mapa_t* M_Aloca(int vertices, int arestas){
    mapa_t* aux= (mapa_t*)malloc(sizeof(mapa_t));
    if(aux==NULL){exit(1);}
    return aux;
}

void M_Libertar(mapa_t* mapa){
    /*Todo libertar a estrutura do mapa*/
    free(mapa);
}