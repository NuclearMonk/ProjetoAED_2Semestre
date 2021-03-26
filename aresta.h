

typedef struct _aresta aresta_t;

aresta_t* A_Alocar(int a, int b,double custo);
void      A_Libertar(aresta_t* aresta);

int       A_A(aresta_t* aresta);
int       A_B(aresta_t* aresta);
double    A_Custo(aresta_t* aresta);
int       A_Outro(aresta_t* aresta, int vertice);



