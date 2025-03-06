/*DAVID Andrei-Gabriel - 312CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct celula
{
	char info;
	struct celula *pre, *urm;
} TCelula, *TLista;

typedef struct banda
{
	TLista s, deget;
} TBandaCelula, *TBanda;


typedef struct celulaQ
{
	char *infoQ;
	struct celulaQ *urmQ;
} TCelulaQ, *TListaQ;

typedef struct coada
{
	TListaQ inc, sf;
} TCoadaCelula, *TCoada;

typedef struct celulaS
{
	TLista infoS;
	struct celulaS *preS, *urmS;
} TStivaCelula, *TStiva;

TLista AlocCelula();
TBanda Init();
TBanda MOVE_LEFT(TBanda B);
TBanda MOVE_RIGHT(TBanda B);
TBanda MOVE_LEFT_CHAR(TBanda B, char caracter);
TBanda MOVE_RIGHT_CHAR(TBanda B, char caracter);
TBanda INSERT_LEFT(TBanda B, char caracter);
TBanda INSERT_RIGHT(TBanda B, char caracter);
TBanda WRITE(TBanda B, char caracter);
void SHOW_CURRENT(TBanda B);
void SHOW(TBanda B);
void DistrugeBanda(TBanda *B);
TListaQ AlocCelulaQ();
TCoada InitQ();
TCoada IntrQ(TCoada C, char *comanda);
TCoada ExtrQ(TCoada C, char *comm_cur);
void DistrQ(TCoada *C);
TStiva AlocCelulaS();
TStiva InitS();
TStiva IntrS(TStiva S, TLista temp);
TStiva ExtrS(TStiva S, TLista *temp);
void DistrS(TStiva *S);