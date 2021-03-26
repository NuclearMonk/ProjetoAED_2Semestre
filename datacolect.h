#include <stdlib.h>
#include "Data.h"

void le_cabecalho_prob(FILE *fpprob, char *cabeca){
    if (fscanf(fpprob, "%s", cabeca) != 1){
        exit(0);
    }
    else if (strcmp(cabeca, "A0") == 0)
    {
         if (fscanf(fpprob, "%c", cabeca[2]) != 1){
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