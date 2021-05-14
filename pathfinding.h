#ifndef _PATH_H
#define _PATH_H

typedef struct _path{
    double* distancia;
    int*    anterior;
}path_t;

#define FREEPATH(A) {free(A->anterior); free(A->distancia);free(A);}

#endif