

typedef struct _cabecalho cabecalho_t;

cabecalho_t* C_Aloca();
void         C_Liberta(cabecalho_t* cabecalho);

int         C_GetProblema(cabecalho_t* cabecalho);
void        C_SetProblema(cabecalho_t* cabecalho,int problema);

int         C_GetVInicial(cabecalho_t* cabecalho);
void        C_SetVInicial(cabecalho_t* cabecalho,int inicial);

int         C_GetVFinal(cabecalho_t* cabecalho);
void        C_SetVFinal(cabecalho_t* cabecalho,int inicial);

int         C_GetFlag(cabecalho_t* cabecalho);
void        C_SetFlag(cabecalho_t* cabecalho,int flag);

double      C_GetDesvio(cabecalho_t* cabecalho);
void        C_SetDesvio(cabecalho_t* cabecalho,double desvio);