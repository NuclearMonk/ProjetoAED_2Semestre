#include <stdbool.h>

typedef double* madj_t;

madj_t  MA_Alocar(int vertices);
void    MA_Libertar(madj_t madj);

void    MA_InserirAresta(madj_t madj, int maxvertices, int a , int b, double custo);

double  MA_Custo(madj_t madj,int maxvertices, int a, int b);

bool    MA_Adjacente(madj_t madj,int maxvertices, int a, int b);

