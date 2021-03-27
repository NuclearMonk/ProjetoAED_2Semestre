#include <stdbool.h>

typedef struct _mapa mapa_t;

mapa_t* M_Aloca(int vertices, int arestas);
void    M_Libertar(mapa_t* mapa);

void    M_ArestaInsere(mapa_t* mapa, int a, int b , double custo);

int     M_Grau(mapa_t* mapa,int vertice);
bool    M_Adjacente(mapa_t* mapa, int a, int b);