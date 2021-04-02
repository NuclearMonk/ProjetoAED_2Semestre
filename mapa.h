#include <stdbool.h>

typedef struct _mapa mapa_t;

mapa_t* M_Alocar(int vertices, int arestas);
void    M_Libertar(mapa_t* mapa);

void    M_InserirAresta(mapa_t* mapa, int a, int b , double custo);

double  M_Custo(mapa_t* mapa, int a, int b);

int     M_Grau(mapa_t* mapa,int vertice);

int     M_Adjacente(mapa_t* mapa, int a, int b);

int     M_DistanciaExata(mapa_t* mapa, int a , int k);

/*funçao que reorna C0 soluçao*/

int    M_DistanciaExataCerta(mapa_t* mapa, int a , int k);

/*funcao que retorna se dois vertices sao adajacentes recebndo mapa*/
