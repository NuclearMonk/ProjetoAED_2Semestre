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


    if (argc != 4){exit(0);}            /*verifica se existem 4 argumentos ./aedmaps -opcao problemas.prbs mapas.maps*/

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

    fp_saida = Abre_ficheiro_saida(argv[3]);
     if(fp_saida == NULL){
        fclose(fp_problemas);
        fclose(fp_mapas);
        exit(0);
    }

    fprintf(fp_saida, "%s %s %s\n\n", argv[1], argv[2], argv[3]); /*Escreve a primeira linha do ficheiro de saida "opcao ficheiroproblemas ficheiromapas"*/

    if(strcmp(argv[1], "-1oo") == 0){/*executa uma vez sem loops o programa, executando so o primeiro problema no primeiro mapa*/
        cabecalho = Le_cabecalho_prob(fp_problemas);
        if(cabecalho == NULL){
            fclose(fp_problemas);
            fclose(fp_mapas);
            fclose(fp_saida);
            exit(0);
        }
        mapa = Le_mapa(fp_mapas);
        if(mapa == NULL){
            fclose(fp_problemas);
            fclose(fp_mapas);
            fclose(fp_saida);
            exit(0);
        }
        Resolve_problema(fp_saida, mapa, cabecalho);
        C_Libertar(cabecalho);
        M_Libertar(mapa);
    }
    else if(strcmp(argv[1], "-1oa") == 0){/*Le um cabecalho, e exxecuta-o para todos os mapas*/
        cabecalho = Le_cabecalho_prob(fp_problemas);
        if(cabecalho == NULL){
            fclose(fp_problemas);
            fclose(fp_mapas);
            fclose(fp_saida);
            exit(0);
        }
        while((mapa=Le_mapa(fp_mapas)) != NULL){
            Resolve_problema(fp_saida, mapa, cabecalho);
            M_Libertar(mapa);
        }
        C_Libertar(cabecalho);
        
    }
    else if(strcmp(argv[1], "-1ao") == 0){/*Le um mapa, e exxecuta-o para todos os cabecalhos*/
        mapa=Le_mapa(fp_mapas);
        if(mapa == NULL){
            fclose(fp_problemas);
            fclose(fp_mapas);
            fclose(fp_saida);
            exit(0);
        }
        while((cabecalho = Le_cabecalho_prob(fp_problemas)) != NULL){
            Resolve_problema(fp_saida, mapa, cabecalho);
            C_Libertar(cabecalho);
        }
        M_Libertar(mapa);
    }
    else if(strcmp(argv[1], "-1aa") == 0){/*Le um mapa, e exxecuta-o para todos os cabecalhos, le outro mapa ate n ter mapas*/
        while((mapa=Le_mapa(fp_mapas)) != NULL){
            while((cabecalho = Le_cabecalho_prob(fp_problemas)) != NULL){
                Resolve_problema(fp_saida, mapa, cabecalho);
                C_Libertar(cabecalho);
            }
            M_Libertar(mapa);
            rewind(fp_problemas);
        }
    }else{
        exit(0);
    }

    fclose(fp_mapas);
    fclose(fp_problemas);
    fclose(fp_saida);
    return 0;
}

