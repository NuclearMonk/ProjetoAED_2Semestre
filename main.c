#include <stdio.h>

#include "slist.h"
#include "stack.h"
#include "dlist.h"
#include "fileinterface.h"


int main(){
    int i =0;
    cabecalho_t* cabecalho;
    FILE *fp;
    fp=fopen("problema.txt", "r");
    while(i<4){
    cabecalho = le_cabecalho_prob(fp);
    printf("tipo: %d Vincio: %d Vfinal: %d Vflag: %d \n", C_GetProblema(cabecalho), C_GetVInicial(cabecalho), C_GetVFinal(cabecalho), C_GetFlag(cabecalho));
    i++;
    C_Liberta(cabecalho);
    }
    fclose(fp);

    return 0;
}

