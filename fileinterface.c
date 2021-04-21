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
        C_SetFlag(cabecalho,aux);
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
        Le_aresta(fpprob, mapa);
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
    if(mapa==NULL)return;
    /*M_VerticeInsere(mapa, a, class);nessessario ainda criar esta funçao*/
}

void Le_aresta(FILE *fpprob,mapa_t* mapa){
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
}

FILE* Abre_ficheiro_prob(char *ficheiroprob){
    FILE *fp;
    char* aux;
    aux = strrchr(ficheiroprob, '.');
    if(strcmp(aux, ".prbs1") != 0){return NULL;}
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
    char aux[8]="queries";
    char* ficheiroout=(char*)calloc((strlen(ficheiromapa)+4),sizeof(char));
    if(ficheiroout==NULL)return NULL;
    strncpy(ficheiroout,ficheiromapa, (strlen(ficheiromapa)-4));
    strcat(ficheiroout, aux);
    fpout=fopen(ficheiroout, "w");
    free(ficheiroout);
    if(fpout == NULL){return NULL;}
    return fpout;
}

void         Resolve_problema(FILE *fp_saida, mapa_t* mapa, cabecalho_t* cabecalho){
    int tipo;
    double aux;
    tipo = C_GetProblema(cabecalho);
    switch (tipo)
    {
    case 1:/*A0*/
        fprintf(fp_saida, "%d %d A0 %d %d\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa), C_GetVInicial(cabecalho), M_Grau(mapa,C_GetVInicial(cabecalho)));
        break;
    case 2:
        aux = M_Custo(mapa, C_GetVInicial(cabecalho), C_GetVFinal(cabecalho));/*B0*/
        if(aux<=0)fprintf(fp_saida, "%d %d B0 %d %d -1\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa), C_GetVInicial(cabecalho), C_GetVFinal(cabecalho));
        else fprintf(fp_saida, "%d %d B0 %d %d %.2f\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa), C_GetVInicial(cabecalho), C_GetVFinal(cabecalho), aux);
        break;
    case 3:/*C0*/
        fprintf(fp_saida, "%d %d C0 %d %d %d\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa), C_GetVInicial(cabecalho), C_GetFlag(cabecalho), M_DistanciaExataCerta(mapa, C_GetVInicial(cabecalho), C_GetFlag(cabecalho)));
        break;
    case 4:/*D0*/
        fprintf(fp_saida, "%d %d D0 %d %d %d\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa), C_GetVInicial(cabecalho), C_GetFlag(cabecalho), M_DistanciaExata(mapa, C_GetVInicial(cabecalho), C_GetFlag(cabecalho)));
        break;
    default:
        break;
    }
    fprintf(fp_saida, "\n");
}