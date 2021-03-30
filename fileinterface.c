#include <string.h>
#include <stdlib.h>

#include "fileinterface.h"
#include "cabecalho.h"
#include "mapa.h"
#include "matrizadjacencia.h"


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
        le_aresta(fpprob, mapa, vertices);
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
    /*M_VerticeInsere(mapa, a, class);nessessario ainda criar esta funçao*/
}

void le_aresta(FILE *fpprob,mapa_t* mapa, int maxvertices){
    int a,b;
    double custo;
    if (fscanf(fpprob, "%d", &a) != 1){
        exit(0);
    }
    if (fscanf(fpprob, "%d", &b) != 1){
        exit(0);
    }
    if (fscanf(fpprob, "%lf", &custo) != 1){
        exit(0);
    }
    M_ArestaInsere(mapa, a, b, custo);
    printmapa(mapa, a, b);
}

void printmapa(mapa_t *mapa, int a, int b){
    double custo;
     custo = M_Custo(mapa, a, b);
     printf("primeiro verice:%d e segundo: %d e o custo:%f\n", a, b, custo);
}

FILE* abre_ficheiro_prob(char *ficheiroprob){
    if(ficheiroprob = NULL){exit(0);}
    FILE *fp;
    fp=fopen(ficheiroprob, "r");
    return fp;
}

FILE* abre_ficheiro_mapa(char *ficheiromapa){
    if(ficheiromapa = NULL){exit(0);}
    FILE *fp;
    fp=fopen(ficheiromapa, "r");
    return fp;
}

FILE* abre_ficheiro_saida(char *ficheiromapa){
    char aux[]="routes";
    char* ficheiroout=(char*)malloc((strlen(ficheiromapa)+3)*sizeof(char));
    strncpy(ficheiroout,ficheiromapa, (strlen(ficheiromapa)-4));
    strcat(ficheiroout, aux);
    FILE fpout;
    fpout=fopen(ficheiroout, "r+");
    return fpout;
}