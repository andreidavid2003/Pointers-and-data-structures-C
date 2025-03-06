/*DAVID Andrei-Gabriel - 312CB*/
#include "tema1.h"

//Aloc un element de tip TCelula si returnez pointerul aferent
TLista AlocCelula()  //testat
{
	TLista aux = (TLista)malloc(sizeof(TCelula));
	if (!aux) {
		return NULL;
	}
	aux->info = '#';
	aux->urm = NULL;
	aux->pre = NULL;
	return aux;
}

//Initializez banda
TBanda Init()  //testat
{
	TBanda B = (TBanda)malloc(sizeof(TBandaCelula));
	if (!B) {
		return NULL;
	}
	B->s = AlocCelula();
	B->deget = AlocCelula();
	B->s->urm = B->deget;
	B->deget->pre = B->s;
	return B;
}

//Mut pozitia degetului la stanga, daca este posibil
TBanda MOVE_LEFT(TBanda B)  //testat
{
	if (B->deget->pre != B->s) {
		B->deget = B->deget->pre;
	}
	return B;
}

//Mut pozitia degetului la dreapta si adaug o noua celula daca este cazul
TBanda MOVE_RIGHT(TBanda B)  //testat
{
	if (B->deget->urm == NULL) {
		TLista aux = AlocCelula();
		if (!aux) {
			return NULL;
		}
		B->deget->urm = aux;
		aux->pre = B->deget;
		B->deget = aux;
	} else {
		B->deget = B->deget->urm;
	}
	return B;
}

//Mut pozitia degetului pe prima pozitie din stanga care contine caracterul dat
//In caz contrar, afisez eroare
TBanda MOVE_LEFT_CHAR(TBanda B, char caracter)  //testat
{
	char output_filename[] = "tema1.out";
	FILE *out = fopen(output_filename, "at");
	if (out == NULL) {
		fprintf(stderr, "ERROR: Can't open file %s", output_filename);
		return NULL;
	}
	TLista aux;
	for (aux = B->deget; aux->pre != B->s; aux = aux->pre) {
		if (aux->info == caracter) {
			break;
		}
	}
	if (aux->pre == B->s && aux->info != caracter) {
		fprintf(out, "ERROR\n");
		fclose(out);
		return B;
	}
	B->deget = aux;
	return B;
}

//Mut pozitia degetului pe prima pozitie din dreapta care contine caracterul dat
//In caz contrar, creez o noua celula la final cu caracterul cerut
TBanda MOVE_RIGHT_CHAR(TBanda B, char caracter)  //testat
{
	TLista aux;
	for (aux = B->deget; aux->urm != NULL; aux = aux->urm) {
		if (aux->info == caracter) {
			break;
		}
	}
	if (aux->urm == NULL && aux->info != caracter) {
		TLista auxiliar = AlocCelula();
		if (!auxiliar) {
			return NULL;
		}
		aux->urm = auxiliar;
		auxiliar->pre = aux;
		B->deget = auxiliar;
		return B;
	}
	B->deget = aux;
	return B;
}

//Suprascriu un caracter in celula de pe pozitia degetului
TBanda WRITE(TBanda B, char caracter)  //testat
{
	B->deget->info = caracter;
	return B;
}

//Daca nu ma aflu pe cea mai din stanga pozitie, inserez la stanga o noua celula care contine caracterul dat
//si mut degetul pe celula inserata
TBanda INSERT_LEFT(TBanda B, char caracter)  //testat
{
	char output_filename[] = "tema1.out";
	FILE *out = fopen(output_filename, "at");
	if (out == NULL) {
		fprintf(stderr, "ERROR: Can't open file %s", output_filename);
		return NULL;
	}
	if (B->deget->pre == B->s) {
		fprintf(out, "ERROR\n");
	} else {
		TLista aux = AlocCelula();
		aux->info = caracter;
		aux->pre = B->deget->pre;
		aux->urm = B->deget;
		B->deget->pre->urm = aux;
		B->deget->pre = aux;
		B->deget = aux;
	}
	fclose(out);
	return B;
}

//Inserez la dreapta o noua celula care contine caracterul dat
TBanda INSERT_RIGHT(TBanda B, char caracter)  //testat
{ 
	TLista aux = AlocCelula();
	aux->info = caracter;
	if (B->deget->urm == NULL) {
		aux->pre = B->deget;
		B->deget->urm = aux;
	} else {
		aux->pre = B->deget;
		aux->urm = B->deget->urm;
		B->deget->urm->pre = aux;
		B->deget->urm = aux;
	}
	B->deget = aux;
	return B;
}

//Scriu in fisier informatia din pozitia curenta
void SHOW_CURRENT(TBanda B) //testat
{
	char output_filename[] = "tema1.out";
	FILE *out = fopen(output_filename, "at");
	if (out == NULL) {
		fprintf(stderr, "ERROR: Can't open file %s", output_filename);
		return;
	}
	fprintf(out, "%c\n", B->deget->info);
	fclose(out);
	return;
}

//Scriu in fisier informatia din banda, tinand cont de pozitia degetului
void SHOW(TBanda B) //testat
{
	char output_filename[] = "tema1.out";
	FILE *out = fopen(output_filename, "at");
	if (out == NULL) {
		fprintf(stderr, "ERROR: Can't open file %s", output_filename);
		return;
	}
	TLista aux = B->s->urm;
	while (aux != NULL) {
		if (aux == B->deget) {
			fprintf(out, "|%c|", aux->info);
		} else {
			fprintf(out, "%c", aux->info);
		}
		aux = aux->urm;
	}
	fprintf(out, "\n");
	fclose(out);
	return;
}

//Distrug banda
void DistrugeBanda(TBanda *B)  //testat
{
	TLista p, aux;
	p = (*B)->s;
	while (p != NULL) {
		aux = p;
		p = p->urm;
		free(aux);
	}
	free(*B);
	*B = NULL;
}

//Aloc o celula de tip TListaQ si returnez pointerul aferent
TListaQ AlocCelulaQ()  //testat
{
	TListaQ aux = (TListaQ)malloc(sizeof(TCelulaQ));
	if (!aux) {
		return NULL;
	}
	aux->urmQ = NULL;
	return aux;
}

//Initializez coada
TCoada InitQ()  //testat
{
	TCoada C = (TCoada)malloc(sizeof(TCoadaCelula));
	if (!C) {
		return NULL;
	}
	C->inc = NULL;
	C->sf = NULL;
	return C;
}

//Introduc element in coada
TCoada IntrQ(TCoada C, char *comanda)  //testat
{
	TListaQ aux = AlocCelulaQ();
	if (!aux) {
		return NULL;
	}
	aux->infoQ = malloc(MAX * sizeof(char));
	strcpy(aux->infoQ, comanda);
	if (C->sf == NULL) {
		C->inc = aux;
	} else {
		C->sf->urmQ = aux;
	}
	C->sf = aux;
	return C;
}

//Extrag elementul de la inceputul cozii
TCoada ExtrQ(TCoada C, char *comm_cur)  //testat
{
	strcpy(comm_cur, C->inc->infoQ);
	TListaQ aux = C->inc;
	if (C->inc->urmQ != NULL) {
		C->inc = C->inc->urmQ;
	} else {
		C->inc = NULL;
		C->sf = NULL;
	}
	free(aux->infoQ);
	free(aux);
	return C;
}

//Distrug coada
void DistrQ(TCoada *C)  //testat
{
	TListaQ p, aux;
	p = (*C)->inc;
	while (p != NULL) {
		aux = p;
		p = p->urmQ;
		free(aux->infoQ);
		free(aux);
	}
	free(*C);
	*C = NULL;
}

//Aloc o celula de tipul TStiva
TStiva AlocCelulaS()  //testat
{
	TStiva aux = (TStiva)malloc(sizeof(TStivaCelula));
	if (!aux) {
		return NULL;
	}
	aux->preS = NULL;
	aux->urmS = NULL;
	return aux;
}

//Initializez Stiva
TStiva InitS()  //testat
{
	TStiva S = NULL;
	return S;
}

//Introduc o adresa in stiva
TStiva IntrS(TStiva S, TLista temp)  //testat
{
	TStiva aux = AlocCelulaS();
	if (!aux) {
		return NULL;
	}
	aux->infoS = temp;
	if (S != NULL) {
		S->urmS = aux;
		aux->preS = S;
	}
	S = aux;
	return S;
}

//Extrag adresa din varful stivei
TStiva ExtrS(TStiva S, TLista *temp) //testat
{
	(*temp) = S->infoS;
	TStiva aux = S;
	S = S->preS;
	free (aux);
	return S;
}

//Distrug stiva
void DistrS(TStiva *S)  //testat
{
	TStiva p, aux;
	p = (*S);
	while (p != NULL) {
		aux = p;
		p = p->preS;
		free(aux);
	}
	*S = NULL;
}