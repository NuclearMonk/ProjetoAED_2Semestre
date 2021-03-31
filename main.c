#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fileinterface.h"


int main(int argc,char* argv[]){
    mapa_t* mapa=NULL;
    cabecalho_t* cabecalho=NULL;
    FILE *fp_problemas=NULL;
    FILE *fp_mapas=NULL;
    FILE *fp_saida=NULL;


    if (argc != 4){exit(0);}

    fp_problemas = Abre_ficheiro_prob(argv[2]);
    if(fp_problemas == NULL)
    {
        exit(0);
    }

    fp_mapas = Abre_ficheiro_mapa(argv[3]);
    if(fp_mapas == NULL){
        fclose(fp_problemas);
        exit(0);
    }

    if(strcmp(argv[1], "-oo") == 0){
        cabecalho = Le_cabecalho_prob(fp_problemas);
        mapa = Le_mapa(fp_mapas);
        fp_saida = Abre_ficheiro_saida(argv[3]);
        Resolve_problema(fp_saida, mapa, cabecalho);
        C_Libertar(cabecalho);
        M_Libertar(mapa);
        /*executa uma vez sem loops o programa, executando so o primeiro problema no primeiro mapa*/
    }
    else if(strcmp(argv[1], "-oa") == 0){
        cabecalho = Le_cabecalho_prob(fp_problemas);
        while((mapa=Le_mapa(fp_mapas)) != NULL){
            fp_saida = Abre_ficheiro_saida(argv[3]);
            Resolve_problema(fp_saida, mapa, cabecalho);
            /*executa programa*/
        }
        C_Libertar(cabecalho);
        M_Libertar(mapa);
    }
    else if(strcmp(argv[1], "-ao") == 0){
        mapa=Le_mapa(fp_mapas);
        while((cabecalho = Le_cabecalho_prob(fp_problemas)) != NULL){
            fp_saida = Abre_ficheiro_saida(argv[3]);
            Resolve_problema(fp_saida, mapa, cabecalho);
            /*executa programa*/
        }
        C_Libertar(cabecalho);
        M_Libertar(mapa);
    }
    else if(strcmp(argv[1], "-aa") == 0){
        while((cabecalho = Le_cabecalho_prob(fp_problemas)) != NULL){
            while((mapa=Le_mapa(fp_mapas)) != NULL){
                fp_saida = Abre_ficheiro_saida(argv[3]);
                Resolve_problema(fp_saida, mapa, cabecalho);
                /*executa programa*/
            }
        }
        C_Libertar(cabecalho);
        M_Libertar(mapa);
    }else{
        exit(0);
    }

    fclose(fp_mapas);
    fclose(fp_problemas);
    fclose(fp_saida);
    return 0;
}

