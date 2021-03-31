#include <stdio.h>

#include "fileinterface.h"
#include "mapa.h"


int main(int argc,char* argv[]){
    mapa_t* mapa;
    cabecalho_t* cabecalho;
    if (argc != 3){exit(0);}
    FILE *problema;
    FILE *mapa;
    FILE *Fsaida;
    if((problema = abre_ficheiro_prob(argv[1])) == NULL){exit(0);}
    if((mapa = abre_ficheiro_mapa(argv[2])) == NULL){exit(0);}
    if(strcmp(argv[0], "-oo") == 0){
        cabecalho = le_cabecalho_prob(problema);
        mapa = le_mapa(mapa);
        Fsaida = abre_ficheiro_saida(mapa);
        resolve_problema(Fsaida, mapa, cabecalho);
        /*executa uma vez sem loops o programa, executando so o primeiro problema no primeiro mapa*/
    }
    else if(strcmp(argv[0], "-oa") == 0){
        cabecalho = le_cabecalho_prob(problema);
        while((mapa=le_mapa(mapa)) != NULL){
            Fsaida = abre_ficheiro_saida(mapa);
            resolve_problema(Fsaida, mapa, cabecalho);
            /*executa programa*/
        }
    }
    else if(strcmp(argv[0], "-ao") == 0){
        mapa=le_mapa(mapa);
        while((cabecalho = le_cabecalho_prob(problema)) != NULL){
            Fsaida = abre_ficheiro_saida(mapa);
            resolve_problema(Fsaida, mapa, cabecalho);
            /*executa programa*/
        }
    }
    else if(strcmp(argv[0], "-aa") == 0){
        while((cabecalho = le_cabecalho_prob(problema)) != NULL){
            while((mapa=le_mapa(mapa)) != NULL){
                Fsaida = abre_ficheiro_saida(mapa);
                resolve_problema(Fsaida, mapa, cabecalho);
                /*executa programa*/
            }
        }
    }else{
        exit(0);
    }
    /*int i =0;
    FILE *fp;
    fp=fopen("problema.txt", "r");
    while(i<4){
    cabecalho = le_cabecalho_prob(fp);
    printf("tipo: %d Vincio: %d Vfinal: %d Vflag: %d \n", C_GetProblema(cabecalho), C_GetVInicial(cabecalho), C_GetVFinal(cabecalho), C_GetFlag(cabecalho));
    i++;
    C_Liberta(cabecalho);
    }
    fclose(fp);
    FILE *fpm;
    fpm=fopen("teste.txt", "r");
    mapa=le_mapa(fpm);
    printmapa(mapa, 1,4 );
    fclose(fpm);*/
    fclose(mapa);
    fclose(problema);
    return 0;
}

