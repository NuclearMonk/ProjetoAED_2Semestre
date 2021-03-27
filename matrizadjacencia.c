#include "matrizadjacencia.h"

#include <stdlib.h>



madj_t MA_Alocar(int vertices){
    madj_t aux = (madj_t)sizeof((vertices-1)*(vertices-1)*sizeof(double));
    if(aux==NULL){
        exit(1);
    }
    return aux;
}
void    MA_Libertar(madj_t madj){
    free(madj);
}

void    MA_InserirAresta(madj_t madj,int maxvertices, int a , int b, double custo){
    madj[((a-1)/(maxvertices))+(b-1)]=custo;
    madj[((b-1)/(maxvertices))+(a-1)]=custo;
}

double    MA_Custo(madj_t madj,int maxvertices, int a, int b){
    return (double)madj[((a-1)/(maxvertices))+(b-1)];
}
bool    MA_Adjacente(madj_t madj,int maxvertices, int a, int b){
    return ((double)madj[((a-1)/(maxvertices))+(b-1)]>0);
}