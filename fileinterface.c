#include <stdlib.h>
#include <string.h>

#include "fileinterface.h"


/*Le o cabecalho do ficheiro fornecido
 *Retorna um struct de tipo cabecalho com os valores do problema lido
 */
cabecalho_t* Le_cabecalho_prob(FILE *fpprob){
    cabecalho_t* cabecalho = C_Alocar();
    char tipo[3];
    int aux;
    char aux1;
    double aux2;
    if (fscanf(fpprob, "%s", tipo) != 1){
        free(cabecalho);
        return NULL;
    }
    else if (strcmp(tipo, "A0") == 0)
    {   
        C_SetProblema(cabecalho,1);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVInicial(cabecalho,aux);
    }
    else if (strcmp(tipo, "B0") == 0)
    {   
        C_SetProblema(cabecalho,2);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVInicial(cabecalho,aux);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVFinal(cabecalho,aux);
    }
    else if (strcmp(tipo, "C0") == 0)
    {   
        C_SetProblema(cabecalho,3);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVInicial(cabecalho,aux);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetFlag(cabecalho,aux);
    }
    else if (strcmp(tipo, "D0") == 0)
    {   
        C_SetProblema(cabecalho,4);
         if (fscanf(fpprob, "%d", &aux) != 1){
            exit(0);
        }
        C_SetVInicial(cabecalho,aux);
        if (fscanf(fpprob, "%d", &aux) != 1){
            exit(0);
        }
        C_SetFlag(cabecalho,aux);
    }
    else if (strcmp(tipo, "A1") == 0)
    {   
        C_SetProblema(cabecalho,5);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVInicial(cabecalho,aux);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVFinal(cabecalho,aux);
    }
    else if (strcmp(tipo, "B1") == 0)
    {   
        C_SetProblema(cabecalho,6);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVInicial(cabecalho,aux);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVFinal(cabecalho,aux);
        if (fscanf(fpprob, " %c", &aux1) != 1){
            return NULL;
        }
        if((int)'a'<=aux1 && aux1<=(int)'z')aux = (int)(aux1 - 'a');
        else return NULL;
        C_SetFlag(cabecalho,aux);
        
        if (fscanf(fpprob, "%lf", &aux2) != 1){
            return NULL;
        }
        C_SetDesvio(cabecalho,aux2);
    }
    else if (strcmp(tipo, "C1") == 0)
    {   
        C_SetProblema(cabecalho,7);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVInicial(cabecalho,aux);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVFinal(cabecalho,aux);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetFlag(cabecalho,aux);
    }
    else if (strcmp(tipo, "D1") == 0)
    {   
        C_SetProblema(cabecalho,8);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVInicial(cabecalho,aux);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetVFinal(cabecalho,aux);
        if (fscanf(fpprob, "%d", &aux) != 1){
            return NULL;
        }
        C_SetFlag(cabecalho,aux);
    }
    return cabecalho;
}


/*Le um mapa e retorna um struct de tipo mapa*/
mapa_t* Le_mapa(FILE *fpprob){
    int vertices,arestas, i;
    if (fscanf(fpprob, "%d", &vertices) != 1){
        return NULL;
    }
    if (fscanf(fpprob, "%d", &arestas) != 1){
        return NULL;
    }
    mapa_t* mapa= M_Alocar(vertices,arestas);
    for(i=0;i<vertices;i++){
    Le_cidade(fpprob, mapa);
    }
    for(i=0;i<arestas;i++){
        Le_aresta(fpprob, mapa);
    }
    return mapa;
}


/*Le apenas o ficheir0, na primeira fase n era preciso fazer nada com as cidades*/
void Le_cidade(FILE *fpprob, mapa_t* mapa){
    int a;
    char caracteristica[27];

    if(mapa==NULL)return;
    if (fscanf(fpprob, "%d", &a) != 1){
        exit(0);
    }
    if (fscanf(fpprob, "%s", caracteristica) != 1){
        exit(0);
    }
    M_InsereCaracteristica(mapa, caracteristica, a);
}


/*Le uma aresta e insere diretamente no mapa*/
void Le_aresta(FILE *fpprob,mapa_t* mapa){
    int a,b;
    double custo;
    if (fscanf(fpprob, "%d", &a) != 1){
        exit(0);
    }
    if (fscanf(fpprob, "%d", &b) != 1){
        exit(0);
    }
    if (fscanf(fpprob, "%lf", &custo) != 1){
        exit(0);
    }
    M_InserirAresta(mapa, a, b, custo);
}

FILE* Abre_ficheiro_prob(char *ficheiroprob){
    FILE *fp;
    char* aux;
    aux = strrchr(ficheiroprob, '.');
    if(strcmp(aux, ".prbs") != 0){return NULL;}
    fp=fopen(ficheiroprob, "r"); 
    if(fp == NULL){return NULL;}
    return fp;
}

FILE* Abre_ficheiro_mapa(char *ficheiromapa){
    char* aux;
    aux = strrchr(ficheiromapa, '.');
    if(strcmp(aux, ".maps") != 0){return NULL;}
    FILE *fp;
    fp=fopen(ficheiromapa, "r");
    if(fp == NULL){return NULL;}
    return fp;
}

FILE* Abre_ficheiro_saida(char *ficheiromapa){
    FILE* fpout;
    int len = strlen(ficheiromapa)-4;
    char aux[8]="routes";
    char* ficheiroout=(char*)calloc(len+7,sizeof(char));
    if(ficheiroout==NULL)return NULL;
    strcpy(ficheiroout,ficheiromapa);
    ficheiroout[len]='\0';
    strcat(ficheiroout, aux);
    fpout=fopen(ficheiroout, "w");
    free(ficheiroout);
    if(fpout == NULL){return NULL;}
    return fpout;
}
/*Dado um mapa e um cabecalho escreve o resultado para o ficheiro de saida*/
void         Resolve_problema(FILE *fp_saida, mapa_t* mapa, cabecalho_t* cabecalho){
    int tipo,a,b,c,d,comprimento;
    double aux;
    path_t* path;
    path_t* pathalternativo;
    slist_t* listacidades;
    tipo = C_GetProblema(cabecalho);
    switch (tipo)
    {
    case 1:/*A0*/
        fprintf(fp_saida, "%d %d A0 %d %d\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa), C_GetVInicial(cabecalho), M_Grau(mapa,C_GetVInicial(cabecalho)));
        break;
    case 2:
        aux = M_Custo(mapa, C_GetVInicial(cabecalho), C_GetVFinal(cabecalho));/*B0*/
        if(aux<=0)fprintf(fp_saida, "%d %d B0 %d %d -1\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa), C_GetVInicial(cabecalho), C_GetVFinal(cabecalho));
        else fprintf(fp_saida, "%d %d B0 %d %d %.2f\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa), C_GetVInicial(cabecalho), C_GetVFinal(cabecalho), aux);
        break;
    case 3:/*C0*/
        fprintf(fp_saida, "%d %d C0 %d %d %d\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa), C_GetVInicial(cabecalho), C_GetFlag(cabecalho), M_ExistemVerticesDistanciaExata(mapa, C_GetVInicial(cabecalho), C_GetFlag(cabecalho)));
        break;
    case 4:/*D0*/
        fprintf(fp_saida, "%d %d D0 %d %d %d\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa), C_GetVInicial(cabecalho), C_GetFlag(cabecalho), M_NumeroVerticesDistanciaExata(mapa, C_GetVInicial(cabecalho), C_GetFlag(cabecalho)));
        break;
    case 5:/*A1 Caminho mais curto*/
        /*procuramos um caminho*/
        path = M_DJIKSTRAS(mapa,C_GetVFinal(cabecalho),C_GetVInicial(cabecalho));
        /*Se o pedido de caminho for invalido*/
        if(path==NULL){
            /*invalido por out of bounds*/
            if(!((0<C_GetVFinal(cabecalho) && C_GetVFinal(cabecalho)<= M_GetMaxVertices(mapa)) && (0<C_GetVInicial(cabecalho) && C_GetVInicial(cabecalho)<=M_GetMaxVertices(mapa)))){
                fprintf(fp_saida, "%d %d A1 %d %d -1\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho), C_GetVFinal(cabecalho));
                break;
            }
            /*invalido porque o caminho tem comprimento 0*/
            if(C_GetVInicial(cabecalho)== C_GetVFinal(cabecalho)){
                fprintf(fp_saida, "%d %d A1 %d %d 0 0.00\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho), C_GetVFinal(cabecalho));
                break;
            }
            /*Nunca deve acontercer*/
            fprintf(fp_saida, "%d %d A1 %d %d -1\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho), C_GetVFinal(cabecalho));
        }
        else{
            /*medimos i comprimento do caminho em numero de arestas*/
            comprimento=0;
            for(a=C_GetVInicial(cabecalho);path->anterior[a-1]>0;a=b){
                b=path->anterior[a-1];
                if(b==-1)continue;
                comprimento++;
            }
            /*Se o caminho existe escrevemos cabecalho*/
            fprintf(fp_saida, "%d %d A1 %d %d %d %.2lf\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho), C_GetVFinal(cabecalho),comprimento,path->distancia[C_GetVInicial(cabecalho)-1]);
            
            /*Escrevemos as arestas que compoe o caminho*/
            for(a=C_GetVInicial(cabecalho);path->anterior[a-1]>0;a=b){
                b=path->anterior[a-1];
                if(b==-1)continue;
                fprintf(fp_saida,"%d %d %.2lf\n",a,b,(path->distancia[a-1])-(path->distancia[b-1]));
            }
            /*libertamos o caminho*/
            FREEPATH(path)
        }
        break;
    case 6:
        /*path de Inicio para fim e todas as cidades de categoria fornecida*/
        path= M_DJIKSTRAS_DESVIO(mapa,C_GetVInicial(cabecalho),C_GetVFinal(cabecalho),C_GetFlag(cabecalho));
        
        
        if(path==NULL){
            /*se o caminho nao existe por out of bounds*/
            if(C_GetDesvio(cabecalho)>=0){
                fprintf(fp_saida, "%d %d B1 %d %d %c %.2lf -1\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho), C_GetVFinal(cabecalho),(char)('a'+C_GetFlag(cabecalho)), C_GetDesvio(cabecalho));
            }
            else{
                fprintf(fp_saida, "%d %d B1 %d %d %c -1 -1\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho), C_GetVFinal(cabecalho),(char)('a'+C_GetFlag(cabecalho)));
            }
            break;
        }
        /*Se o caminho existe*/
        else{ 
            /*path de fim para inicio e todas as cidades com a carateristica definida*/
            pathalternativo = M_DJIKSTRAS_DESVIO(mapa,C_GetVFinal(cabecalho),C_GetVInicial(cabecalho),C_GetFlag(cabecalho));
            
            aux = -1;
            b=-1;                                       /*Procurar a cidade com a carateristica que gera o menor comprmento total*/
            for(listacidades=M_GetCidadesCaracteristica(mapa,C_GetFlag(cabecalho));listacidades!=NULL;listacidades=SL_GetNext(listacidades)){
                a=*(int*)SL_GetData(listacidades);
                if(path->distancia[a-1]>=0 && pathalternativo->distancia[a-1]>=0){
                    if(b==-1){
                        aux = path->distancia[a-1]+pathalternativo->distancia[a-1];
                        b   = a;
                    }
                    else if( aux > path->distancia[a-1]+pathalternativo->distancia[a-1]){
                        aux = path->distancia[a-1]+pathalternativo->distancia[a-1];
                        b   = a;
                    }
                }
            }


            if(b==-1){/*Se nao existe nenhuma cidade assecivel com essa carateristica*/
                if(C_GetDesvio(cabecalho)>=0){
                    fprintf(fp_saida, "%d %d B1 %d %d %c %.2lf -1\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho), C_GetVFinal(cabecalho),(char)('a'+C_GetFlag(cabecalho)), C_GetDesvio(cabecalho));
                }
                else{
                    fprintf(fp_saida, "%d %d B1 %d %d %c -1 -1\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho), C_GetVFinal(cabecalho),(char)('a'+C_GetFlag(cabecalho)));
                }
                FREEPATH(path)
                FREEPATH(pathalternativo)
                break;
            }
            /*Medir o comprimento do inicio para a o meio*/
            comprimento=0;
            for(a=b;path->anterior[a-1]>0;a=c){
                c=path->anterior[a-1];
                if(c==-1)continue;
                comprimento++;
            }
            /*medir o caminho do meio para o inicio*/
            for(a=b;pathalternativo->anterior[a-1]>0;a=c){
                c=pathalternativo->anterior[a-1];
                if(c==-1)continue;
                comprimento++;
            }
            /*calculo do racio do caminho*/
            if(C_GetDesvio(cabecalho)>=0){
                if(aux<0){ /*se o caminho nao existe*/
                    fprintf(fp_saida, "%d %d B1 %d %d %c %.2lf -1\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho), C_GetVFinal(cabecalho),(char)('a'+C_GetFlag(cabecalho)), C_GetDesvio(cabecalho));
                }
                else if(aux==0){ /*caminho de comprimento 0 cumpre todos os racios evita/se a divisao 0/0 */
                    fprintf(fp_saida, "%d %d B1 %d %d %c %.2lf %d %.2lf\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho), C_GetVFinal(cabecalho),(char)('a'+C_GetFlag(cabecalho)), C_GetDesvio(cabecalho),comprimento,aux);
                    EscreveArestasFimInicio(fp_saida,mapa,path,b);
                    for(a=b;pathalternativo->anterior[a-1]>0;a=c){
                        c=pathalternativo->anterior[a-1];
                        if(c==-1)continue;
                        fprintf(fp_saida,"%d %d %.2lf\n",a,c,(pathalternativo->distancia[a-1])-(pathalternativo->distancia[c-1]));
                    }     
                }
                /*Se nao se excede o racio maximo*/
                else if(((aux-path->distancia[C_GetVFinal(cabecalho)-1])/path->distancia[C_GetVFinal(cabecalho)-1])<=C_GetDesvio(cabecalho)){
                    fprintf(fp_saida, "%d %d B1 %d %d %c %.2lf %d %.2lf\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho), C_GetVFinal(cabecalho),(char)('a'+C_GetFlag(cabecalho)), C_GetDesvio(cabecalho),comprimento,aux);
                    EscreveArestasFimInicio(fp_saida,mapa,path,b);
                    for(a=b;pathalternativo->anterior[a-1]>0;a=c){
                        c=pathalternativo->anterior[a-1];
                        if(c==-1)continue;
                        fprintf(fp_saida,"%d %d %.2lf\n",a,c,(pathalternativo->distancia[a-1])-(pathalternativo->distancia[c-1]));
                    }                        
                }
                else{/*excede-se o racio maximo*/
                    fprintf(fp_saida, "%d %d B1 %d %d %c %.2lf -1\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho), C_GetVFinal(cabecalho),(char)('a'+C_GetFlag(cabecalho)), C_GetDesvio(cabecalho));
                }
            }
            else{/*se o desvio maximo for negatico nao e preciso fazer calculos de racio*/
                fprintf(fp_saida, "%d %d B1 %d %d %c -1 %d %.2lf\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho), C_GetVFinal(cabecalho),(char)('a'+C_GetFlag(cabecalho)),comprimento,aux);
                EscreveArestasFimInicio(fp_saida,mapa,path,b);
                for(a=b;pathalternativo->anterior[a-1]>0;a=c){
                    c=pathalternativo->anterior[a-1];
                    if(c==-1)continue;
                    fprintf(fp_saida,"%d %d %.2lf\n",a,c,(pathalternativo->distancia[a-1])-(pathalternativo->distancia[c-1]));
                }         
            } 
            FREEPATH(pathalternativo)
            FREEPATH(path)
        }
        break;
    case 7: /*C1 caminho alternatico sem incluir um vertice*/

        path = M_DJIKSTRAS(mapa,C_GetVFinal(cabecalho),C_GetVInicial(cabecalho));
        
        if(path==NULL){         /*Se o Djikstras for invalido*/
            /*Se o caminho for invalido n existir porque um dos vertices esta fora dos limites*/
            if(!((0<C_GetVFinal(cabecalho) && C_GetVFinal(cabecalho)<= M_GetMaxVertices(mapa)) && (0<C_GetVInicial(cabecalho) && C_GetVInicial(cabecalho)<=M_GetMaxVertices(mapa)))){
                fprintf(fp_saida, "%d %d C1 %d %d %d -1\n",  M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),
                                                         C_GetVFinal(cabecalho),C_GetFlag(cabecalho));
                break;
            }
            /*o caminho e de V para V*/
            if(C_GetVFinal(cabecalho)==C_GetVInicial(cabecalho)){
                fprintf(fp_saida, "%d %d C1 %d %d %d 0 0.00 -1\n",  M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),
                                                                    C_GetVFinal(cabecalho),C_GetFlag(cabecalho));
                break;           
            }
            /*Invalido porque nao existe*/
            fprintf(fp_saida, "%d %d C1 %d %d %d -1\n",  M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),
                                                         C_GetVFinal(cabecalho),C_GetFlag(cabecalho));
        }
        else{
            /*procuramos o comprimento do caminho e procuramos o vertice a distancia k da origem, este vertice fica guardado em c*/
            comprimento=0;
            c=-1;
            for(a=C_GetVInicial(cabecalho);path->anterior[a-1]>0;a=b){
                b=path->anterior[a-1];
                if(comprimento ==C_GetFlag(cabecalho)-1)c=a;
                if(b==-1)continue;
                comprimento++;
            }
            /*Se o caminho original n tem comprimento nao*/
            if(comprimento==0){
                fprintf(fp_saida, "%d %d C1 %d %d %d -1\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),
                                                            C_GetVFinal(cabecalho),C_GetFlag(cabecalho));
            }
            /*se n existir o vertice a k vertices de distancia da origem*/
            else if(c==-1){
                fprintf(fp_saida, "%d %d C1 %d %d %d %d %.2lf -1\n",  M_GetMaxVertices(mapa),M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),C_GetVFinal(cabecalho),C_GetFlag(cabecalho),comprimento,path->distancia[C_GetVInicial(cabecalho)-1]);
            }
            else{
                /*Se o vertice existe procuramos um caminho que nao o contem*/
                pathalternativo=M_DJIKSTRAS_VERTICE(mapa,C_GetVFinal(cabecalho),C_GetVInicial(cabecalho),c);
                
                if(pathalternativo==NULL) /*se a funcao Djikstras_Vertice falha*/
                    fprintf(fp_saida, "%d %d C1 %d %d %d %d %.2lf -1\n",    M_GetMaxVertices(mapa),M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),
                                                                            C_GetVFinal(cabecalho),C_GetFlag(cabecalho),comprimento,path->distancia[C_GetVInicial(cabecalho)-1]);
                
                else if( pathalternativo->anterior[C_GetVInicial(cabecalho)-1]==-1){ /*Se um caminho alternativo nao existe*/
                    fprintf(fp_saida, "%d %d C1 %d %d %d %d %.2lf -1\n",    M_GetMaxVertices(mapa),M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),
                                                                            C_GetVFinal(cabecalho),C_GetFlag(cabecalho),comprimento,path->distancia[C_GetVInicial(cabecalho)-1]);
                FREEPATH(pathalternativo); /*Libertamos o caminho alternativo*/
                }
                /*Se um caminho existe*/
                else {
                    fprintf(fp_saida, "%d %d C1 %d %d %d %d %.2lf %.2lf\n",M_GetMaxVertices(mapa),M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),
                                                                            C_GetVFinal(cabecalho),C_GetFlag(cabecalho),comprimento,path->distancia[C_GetVInicial(cabecalho)-1],
                                                                            pathalternativo->distancia[C_GetVInicial(cabecalho)-1]-path->distancia[C_GetVInicial(cabecalho)-1]);
                FREEPATH(pathalternativo);/*Libertamos o caminho alternativo*/
                }
               
                
            }

            /*escrevemos as arestas que formam o caminho original*/
            for(a=C_GetVInicial(cabecalho);path->anterior[a-1]>0;a=b){
                b=path->anterior[a-1];
                if(b==-1)continue;
                fprintf(fp_saida,"%d %d %.2lf\n",a,b,(path->distancia[a-1])-(path->distancia[b-1]));
            }
            /*Libertamos o caminho*/
            FREEPATH(path)
        }
        break;
    case 8:
        /*procuramos um caminho*/
        path = M_DJIKSTRAS(mapa,C_GetVFinal(cabecalho),C_GetVInicial(cabecalho));
        
        if(path==NULL){         /*Se o Djikstras for invalido*/
            /*Se um dos vertices nao pertence ao mapa*/
            if(!((0<C_GetVFinal(cabecalho) && C_GetVFinal(cabecalho)<= M_GetMaxVertices(mapa)) && (0<C_GetVInicial(cabecalho) && C_GetVInicial(cabecalho)<=M_GetMaxVertices(mapa)))){
                fprintf(fp_saida, "%d %d D1 %d %d %d -1\n",  M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),
                                                         C_GetVFinal(cabecalho),C_GetFlag(cabecalho));
                break;
            }
            /*Se o caminho for de V para V*/
            if(C_GetVFinal(cabecalho)==C_GetVInicial(cabecalho)){
                fprintf(fp_saida, "%d %d D1 %d %d %d 0 0.00 -1\n",  M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),
                                                                    C_GetVFinal(cabecalho),C_GetFlag(cabecalho));
                break;           
            }
            /*Se o caminho Nao Existe*/           
            fprintf(fp_saida, "%d %d D1 %d %d %d -1\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),
                                                        C_GetVFinal(cabecalho),C_GetFlag(cabecalho));
                                
        }
        else{
            /*Mede o caminho e descobre a aresta a restringir*/
            comprimento=0;
            c=-1;
            d=-1;
            for(a=C_GetVInicial(cabecalho);path->anterior[a-1]>0;a=b){
                b=path->anterior[a-1];
                if(comprimento ==C_GetFlag(cabecalho)-1){
                    c=a;
                    d=b;
                }
                if(b==-1)continue;
                comprimento++;
            }

            /*Se o caminho original n existir*/
            if(comprimento==0){
                fprintf(fp_saida, "%d %d D1 %d %d %d -1\n", M_GetMaxVertices(mapa), M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),
                                                            C_GetVFinal(cabecalho),C_GetFlag(cabecalho));
            }
            /*se n existir o vertice a k vertices de distancia da origem*/
            else if(c==-1||d==-1){
                fprintf(fp_saida, "%d %d D1 %d %d %d %d %.2lf -1\n",  M_GetMaxVertices(mapa),M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),C_GetVFinal(cabecalho),C_GetFlag(cabecalho),comprimento,path->distancia[C_GetVInicial(cabecalho)-1]);
            }
            else{
                pathalternativo = M_DJIKSTRAS_ARESTA(mapa,C_GetVFinal(cabecalho),C_GetVInicial(cabecalho),c,d);
                if(pathalternativo==NULL) /*se a funcao Djikstras_Aresta falha*/
                    fprintf(fp_saida, "%d %d D1 %d %d %d %d %.2lf -1\n",    M_GetMaxVertices(mapa),M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),
                                                                            C_GetVFinal(cabecalho),C_GetFlag(cabecalho),comprimento,path->distancia[C_GetVInicial(cabecalho)-1]);
                
                else if( pathalternativo->anterior[C_GetVInicial(cabecalho)-1]==-1) /*Se um caminho alternativo nao existe*/
                    fprintf(fp_saida, "%d %d D1 %d %d %d %d %.2lf -1\n",    M_GetMaxVertices(mapa),M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),
                                                                            C_GetVFinal(cabecalho),C_GetFlag(cabecalho),comprimento,path->distancia[C_GetVInicial(cabecalho)-1]);
                else fprintf(fp_saida, "%d %d D1 %d %d %d %d %.2lf %.2lf\n",M_GetMaxVertices(mapa),M_GetMaxArestas(mapa),C_GetVInicial(cabecalho),
                                                                            C_GetVFinal(cabecalho),C_GetFlag(cabecalho),comprimento,path->distancia[C_GetVInicial(cabecalho)-1],
                                                                            pathalternativo->distancia[C_GetVInicial(cabecalho)-1]-path->distancia[C_GetVInicial(cabecalho)-1]);
                
                /*Libertamos o caminho alternativo*/
                FREEPATH(pathalternativo);                    
            }
            /*escrevemos as arestas que formam o caminho original*/
            for(a=C_GetVInicial(cabecalho);path->anterior[a-1]>0;a=b){
                b=path->anterior[a-1];
                if(b==-1)continue;
                fprintf(fp_saida,"%d %d %.2lf\n",a,b,(path->distancia[a-1])-(path->distancia[b-1]));
            }
            /*Libertamos o caminho*/
            FREEPATH(path)
        }

    break;
    default:
        break;
    }
    fprintf(fp_saida, "\n");
}

void         EscreveArestasFimInicio(FILE* fp_saida,mapa_t* mapa,path_t* path, int fim){
    if(path->distancia[fim-1]==0)return;
    EscreveArestasFimInicio(fp_saida,mapa,path,path->anterior[fim-1]);
    fprintf(fp_saida,"%d %d %.2lf\n", path->anterior[fim-1],fim, (path->distancia[fim-1])-(path->distancia[path->anterior[fim-1]-1]));
}