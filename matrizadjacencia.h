#include <stdbool.h>

typedef struct _madj madj_t;

madj_t*  MA_Alocar(int vertices);
void     MA_Libertar(madj_t* madj);

void     MA_InserirAresta(madj_t* madj, int maxvertices, int a , int b, double custo);

double   MA_Custo(madj_t* madj,int maxvertices, int a, int b);

int      MA_Grau(madj_t* madj, int a);

bool     MA_Adjacente(madj_t* madj,int maxvertices, int a, int b);

int      MA_DistanciaExata(madj_t* madj,int maxvertices, int a , int k);

