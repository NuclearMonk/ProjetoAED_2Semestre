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
    if (fscanf(fpprob, "%s", tipo) != 1){
        exit(0);
    }
    else if (strcmp(tipo, "A0") == 0)
    {   
        C_SetProblema(cabecalho,1);
        if (fscanf(fpprob, "%d", &aux) != 1){
            exit(0);
        }
        C_SetVInicial(cabecalho,aux);
    }
    else if (strcmp(tipo, "B0") == 0)
    {   
        C_SetProblema(cabecalho,2);
        if (fscanf(fpprob, "%d", &aux) != 1){
            exit(0);
        }
        C_SetVInicial(cabecalho,aux);
        if (fscanf(fpprob, "%d", &aux) != 1){
            exit(0);
        }
        C_SetVFinal(cabecalho,aux);
    }
    else if (strcmp(tipo, "C0") == 0)
    {   
        C_SetProblema(cabecalho,3);
        if (fscanf(fpprob, "%d", &aux) != 1){
            exit(0);
        }
        C_SetVInicial(cabecalho,aux);
        if (fscanf(fpprob, "%d", &aux) != 1){
            exit(0);
        }
        C_SetVFinal(cabecalho,aux);
    }
    else if (strcmp(tipo, "D0") == 0)
    {   
        C_SetProblema(cabecalho,4);
         if (fscanf(fpprob, "%d", &aux) != 1){
            exit(0);
        }
        C_SetVInicial(cabecalho,aux);
        if (fscanf(fpprob, "%d", &aux) != 1){
            exit(0);
        }
        C_SetFlag(cabecalho,aux);
    }
    return cabecalho;
}

mapa_t* le_mapa(FILE *fpprob){
    int vertices,arestas, i;
    if (fscanf(fpprob, "%d", &vertices) != 1){
        exit(0);
    }
    if (fscanf(fpprob, "%d", &arestas) != 1){
        exit(0);
    }
    mapa_t* mapa= M_Aloca(vertices,arestas);
    for(i=0;i<vertices;i++){
    le_cidade(fpprob, mapa);
    }
    for(i=0;i<arestas;i++){
        le_aresta(fpprob, mapa);
    }
    return mapa;
}

void le_cidade(FILE *fpprob,mapa_t* mapa){
    int a;
    char class[26];
    if (fscanf(fpprob, "%d", &a) != 1){
        exit(0);
    }
    if (fscanf(fpprob, "%s", class) != 1){
        exit(0);
    }
    /*M_VerticeInsere(mapa, a, class);*/
}

void le_aresta(FILE *fpprob,mapa_t* mapa){
    int a,b;
    double custo;
    if (fscanf(fpprob, "%d", &a) != 1){
        exit(0);
    }
    if (fscanf(fpprob, "%d", &b) != 1){
        exit(0);
    }
    if (fscanf(fpprob, "%lf", &custo) != 1){ /*Exige %lf para ler doubles*/
        exit(0);
    }
    M_ArestaInsere(mapa, a, b, custo);
}
