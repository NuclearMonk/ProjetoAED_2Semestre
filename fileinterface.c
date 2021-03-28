#include <string.h>
#include <stdlib.h>

#include "fileinterface.h"
#include "cabecalho.h"
#include "mapa.h"


/*Modificar, le para variavel auxiliar temporaria e depois escrever para um cabecalho alocado usando o struct cabecalho e retornar o cabecalho ver warnings compilacao*/
/*Ja agora mesmo que n usasses isso cabecalho deveria ser um array de ints onde passavamos a informacao correta*/
cabecalho_t* le_cabecalho_prob(FILE *fpprob){  /*Vai ter que retornar cabecalho*/
    cabecalho_t* cabecalho = C_Aloca();
    char tipo[3];
    int aux;
    if (fscanf(fpprob, "%s", &tipo) != 1){
        exit(0);
    }
    else if (strcmp(tipo, "A0") == 0)
    {   
        C_SetProblema(cabecalho,1);
        if (fscanf(fpprob, "%d", aux) != 1){
            C_SetVInicial(cabecalho,aux);
            exit(0);
        }
    }
    else if (strcmp(tipo, "B0") == 0)
    {   
        C_SetProblema(cabecalho,2);
        if (fscanf(fpprob, "%d", aux) != 1){
            C_SetVInicial(cabecalho,aux);
            exit(0);
        }
        if (fscanf(fpprob, "%d", aux) != 1){
            C_SetVFinal(cabecalho,aux);
            exit(0);
        }
    }
    else if (strcmp(tipo, "C0") == 0)
    {   
        C_SetProblema(cabecalho,3);
        if (fscanf(fpprob, "%d", aux) != 1){
            C_SetVInicial(cabecalho,aux);
            exit(0);
        }
        if (fscanf(fpprob, "%d", aux) != 1){
            C_SetVFinal(cabecalho,aux);
            exit(0);
        }
    }
    else if (strcmp(tipo, "D0") == 0)
    {   
        C_SetProblema(cabecalho,4);
         if (fscanf(fpprob, "%d", aux) != 1){
            C_SetVInicial(cabecalho,aux);
            exit(0);
        }
        if (fscanf(fpprob, "%d", aux) != 1){
            C_SetVFlag(cabecalho,aux);
            exit(0);
        }
    }
    return cabecalho;
}

mapa_t* le_mapa(FILE *fpprob){
    int vertices,arestas;
    if (fscanf(fpprob, "%d %d", vertices, arestas) != 2){
            exit(0);
    }
    mapa_t* mapa= M_Aloca(vertices,arestas);

    return mapa;
}

void le_cidade(FILE *fpprob,mapa_t* mapa){

}

void le_aresta(FILE *fpprob,mapa_t* mapa){

}
