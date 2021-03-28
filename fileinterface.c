#include "fileinterface.h"

#include <string.h>

#include "cabecalho.h" /*incluido para permitir a utilizacao de structs de cabecalho*/


/*Modificar, le para variavel auxiliar temporaria e depois escrever para um cabecalho alocado usando o struct cabecalho e retornar o cabecalho ver warnings compilacao*/
/*Ja agora mesmo que n usasses isso cabecalho deveria ser um array de ints onde passavamos a informacao correta*/
void le_cabecalho_prob(FILE *fpprob, char *cabeca){  /*Vai ter que retornar cabecalho*/
    if (fscanf(fpprob, "%s", cabeca) != 1){
        exit(0);
    }
    else if (strcmp(cabeca, "A0") == 0)
    {
         if (fscanf(fpprob, "%s", cabeca[2]) != 1){
        exit(0);
        }
    }
    else if (strcmp(cabeca, "B0") == 0)
    {
        if (fscanf(fpprob, "%c %c", cabeca[2], cabeca[3]) != 1){
        exit(0);
        }
    }
    else if (strcmp(cabeca, "C0") == 0)
    {
        if (fscanf(fpprob, "%c %c", cabeca[2], cabeca[3]) != 1){
        exit(0);
        }
    }
    else if (strcmp(cabeca, "D0") == 0)
    {
        if (fscanf(fpprob, "%c %c", cabeca[2], cabeca[3]) != 1){
        exit(0);
        }
    }
}