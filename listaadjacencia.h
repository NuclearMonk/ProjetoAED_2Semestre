#include <stdbool.h>

typedef struct _ladj ladj_t;

ladj_t* LA_Alocar(unsigned int vertices, unsigned int arestas);
void    LA_Libertar(ladj_t* ladj, int vertices, int arestas);

void    LA_InserirAresta(ladj_t* ladj, int a, int b, double custo);

double  LA_Custo(ladj_t* ladj, int a, int b);

int     LA_Grau(ladj_t* ladj, int a);

bool    LA_Adjacente(ladj_t ladj, int a, int b);