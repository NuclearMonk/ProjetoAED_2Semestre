#include <stdlib.h>
#include <string.h>

#include "fileinterface.h"


/*Le o cabecalho do ficheiro fornecido
 *Retorna um struct de tipo cabecalho com os valores do problema lido
 */
cabecalho_t* Le_cabecalho_prob(FILE *fpprob){
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
    else if (strcmp(tipo, "A1") == 0)
    {   
        C_SetProblema(cabecalho,5);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVInicial(cabecalho,aux);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVFinal(cabecalho,aux);
    }
    return cabecalho;
}


/*Le um mapa e retorna um struct de tipo mapa*/
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


/*Le apenas o ficheir0, na primeira fase n era preciso fazer nada com as cidades*/
void Le_cidade(FILE *fpprob, mapa_t* mapa){
    int a;
    char caracteristica[27];

    if(mapa==NULL)return;
    if (fscanf(fpprob, "%d", &a) != 1){
        exit(0);
    }
    if (fscanf(fpprob, "%s", caracteristica) != 1){
        exit(0);
    }
    M_InsereCaracteristica(mapa, caracteristica, a);
}


/*Le uma aresta e insere diretamente no mapa*/
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
    int len = strlen(ficheiromapa)-4;
    char aux[8]="routes";
    char* ficheiroout=(char*)calloc(len+7,sizeof(char));
    if(ficheiroout==NULL)return NULL;
    strcpy(ficheiroout,ficheiromapa);
    ficheiroout[len]='\0';
    strcat(ficheiroout, aux);
    fpout=fopen(ficheiroout, "w");
    free(ficheiroout);
    if(fpout == NULL){return NULL;}
    return fpout;
}
/*Dado um mapa e um cabecalho escreve o resultado para o ficheiro de saida*/
void         Resolve_problema(FILE *fp_saida, mapa_t* mapa, cabecalho_t* cabecalho){
    int tipo,a,b,comprimento;
    double aux;
    path_t* path;
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
        fprintf(fp_saida, "%d %d C0 %d %d %d\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa), C_GetVInicial(cabecalho), C_GetFlag(cabecalho), M_ExistemVerticesDistanciaExata(mapa, C_GetVInicial(cabecalho), C_GetFlag(cabecalho)));
        break;
    case 4:/*D0*/
        fprintf(fp_saida, "%d %d D0 %d %d %d\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa), C_GetVInicial(cabecalho), C_GetFlag(cabecalho), M_NumeroVerticesDistanciaExata(mapa, C_GetVInicial(cabecalho), C_GetFlag(cabecalho)));
        break;
    case 5:
        path = M_DJIKSTRAS(mapa,C_GetVFinal(cabecalho),C_GetVInicial(cabecalho));
        if(path==NULL){
            fprintf(fp_saida, "%d %d A1 %d %d -1\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho), C_GetVFinal(cabecalho));
        }
        else{
            comprimento=0;
            for(a=C_GetVInicial(cabecalho);path->anterior[a-1]>0;a=b){
                b=path->anterior[a-1];
                if(b==-1)continue;
                comprimento++;
            }
            fprintf(fp_saida, "%d %d A1 %d %d %d %.2lf\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho), C_GetVFinal(cabecalho),comprimento,path->distancia[C_GetVInicial(cabecalho)-1]);
            for(a=C_GetVInicial(cabecalho);path->anterior[a-1]>0;a=b){
                b=path->anterior[a-1];
                if(b==-1)continue;
                fprintf(fp_saida,"%d %d %.2lf\n",a,b,(path->distancia[a-1])-(path->distancia[b-1]));
            }
            FREEPATH(path)
        }
        break;
    default:
        break;
    }
    fprintf(fp_saida, "\n");
}