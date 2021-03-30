#include <stdio.h>

#include "fileinterface.h"
#include "mapa.h"


int main(){
    /*int i =0;*/
    mapa_t* mapa;
    /*cabecalho_t* cabecalho;
    FILE *fp;
    fp=fopen("problema.txt", "r");
    while(i<4){
    cabecalho = le_cabecalho_prob(fp);
    printf("tipo: %d Vincio: %d Vfinal: %d Vflag: %d \n", C_GetProblema(cabecalho), C_GetVInicial(cabecalho), C_GetVFinal(cabecalho), C_GetFlag(cabecalho));
    i++;
    C_Liberta(cabecalho);
    }
    fclose(fp);*/
    FILE *fpm;
    fpm=fopen("teste.txt", "r");
    mapa=le_mapa(fpm);
    fclose(fpm);
    return 0;
}

