#include <stdlib.h>
#include <string.h>

#include "fileinterface.h"


/*Modificar, le para variavel auxiliar temporaria e depois escrever para um cabecalho alocado usando o struct cabecalho e retornar o cabecalho ver warnings compilacao*/
/*Ja agora mesmo que n usasses isso cabecalho deveria ser um array de ints onde passavamos a informacao correta*/
cabecalho_t* Le_cabecalho_prob(FILE *fpprob){  /*Vai ter que retornar cabecalho*/
    cabecalho_t* cabecalho = C_Alocar();
    char tipo[3];
    int aux;
    if (fscanf(fpprob, "%s", tipo) != 1){
        free(cabecalho);
        return NULL;
    }
    else if (strcmp(tipo, "A0") == 0)
    {   
        C_SetProblema(cabecalho,1);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVInicial(cabecalho,aux);
    }
    else if (strcmp(tipo, "B0") == 0)
    {   
        C_SetProblema(cabecalho,2);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVInicial(cabecalho,aux);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVFinal(cabecalho,aux);
    }
    else if (strcmp(tipo, "C0") == 0)
    {   
        C_SetProblema(cabecalho,3);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVInicial(cabecalho,aux);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
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

mapa_t* Le_mapa(FILE *fpprob){
    int vertices,arestas, i;
    if (fscanf(fpprob, "%d", &vertices) != 1){
        return NULL;
    }
    if (fscanf(fpprob, "%d", &arestas) != 1){
        return NULL;
    }
    mapa_t* mapa= M_Alocar(vertices,arestas);
    for(i=0;i<vertices;i++){
    Le_cidade(fpprob, mapa);
    }
    for(i=0;i<arestas;i++){
        Le_aresta(fpprob, mapa, vertices);
    }
    return mapa;
}

void Le_cidade(FILE *fpprob,mapa_t* mapa){
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

void Le_aresta(FILE *fpprob,mapa_t* mapa, int maxvertices){
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
    M_InserirAresta(mapa, a, b, custo);
    Printmapa(mapa, a, b);
}

void Printmapa(mapa_t *mapa, int a, int b){
    double custo;
     custo = M_Custo(mapa, a, b);
     printf("primeiro verice:%d e segundo: %d e o custo:%f\n", a, b, custo);
}


FILE* Abre_ficheiro_prob(char *ficheiroprob){
    FILE *fp;
    char* aux;
    aux = strrchr(ficheiroprob, '.');
    if(strcmp(aux, ".prbs") != 0){return NULL;}
    fp=fopen(ficheiroprob, "r"); 
    if(fp == NULL){return NULL;}
    return fp;
}

FILE* Abre_ficheiro_mapa(char *ficheiromapa){
    char* aux;
    aux = strrchr(ficheiromapa, '.');
    if(strcmp(aux, ".maps") != 0){return NULL;}
    FILE *fp;
    fp=fopen(ficheiromapa, "r");
    if(fp == NULL){return NULL;}
    return fp;
}

FILE* Abre_ficheiro_saida(char *ficheiromapa){
    FILE* fpout;
    char aux[7]="routes";
    char* ficheiroout=(char*)calloc((strlen(ficheiromapa)+3),sizeof(char));
    if(ficheiroout==NULL)return NULL;
    strncpy(ficheiroout,ficheiromapa, (strlen(ficheiromapa)-4));
    strcat(ficheiroout, aux);
    fpout=fopen(ficheiroout, "w");
    free(ficheiroout);
    if(fpout == NULL){return NULL;}
    return fpout;
}

void         Resolve_problema(FILE *Fsaida, mapa_t* mapa, cabecalho_t* cabecalho){
    int tipo, grau, aux;
    tipo = C_GetProblema(cabecalho);
    switch (tipo)
    {
    case 1:
        grau = M_Grau(mapa,C_GetVInicial(cabecalho));/*A0*/
        break;
    case 2:
        /*B0*/
        break;
    case 3:
        M_DistanciaExataCerta(mapa, C_GetVInicial(cabecalho), C_GetFlag(cabecalho));/*C0*/
        break;
    case 4:
        aux = M_DistanciaExata(mapa, C_GetVInicial(cabecalho), C_GetFlag(cabecalho));/*D0*/
        break;
    default:
        break;
    }
}