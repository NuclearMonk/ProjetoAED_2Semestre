#include <stdbool.h>

typedef struct _mapa mapa_t;

mapa_t* M_Aloca(int vertices, int arestas);
void    M_Libertar(mapa_t* mapa);

void    M_ArestaInsere(mapa_t* mapa, int a, int b , double custo);

double  M_Custo(mapa_t* mapa, int a, int b);

int     M_Grau(mapa_t* mapa,int vertice);

int    M_Adjacente(mapa_t* mapa, int a, int b);