/*DAVID Andrei-Gabriel - 312CB*/
#include "tema1.h"

int main()
{ 
	int i = 0, n = 0;
	char *comanda, *comm_cur;
	TLista temp;

	TBanda B = Init();  //Initializez banda
	if (!B) {
		return -1;
	}

	TCoada C = InitQ();  //Initializez coada
	if (!C) {
		return -1;
	}

	TStiva UNDO = InitS();  //Initializez stiva UNDO
	TStiva REDO = InitS();  //Initializez stiva REDO

	//Golesc fisierul "tema1.out" inainte de a incepe sa scriu din nou in el
	char output_filename[] = "tema1.out";
	FILE *out = fopen(output_filename, "wt");
	if (out == NULL) {
		fprintf(stderr, "ERROR: Can't open file %s", output_filename);
		return -1;
	}
	fclose(out);

	//Deschid fisierul din care citesc
	char input_filename[] = "tema1.in";
	FILE *in = fopen(input_filename, "rt");
	if (in == NULL) {
		fprintf(stderr, "ERROR: Can't open file %s", input_filename);
		return -1;
	}

	//Aloc memorie pentru comanda si comm_cur
	comanda = malloc(MAX * sizeof(char));
	comm_cur = malloc(MAX * sizeof(char));

	fscanf(in, "%d", &n);
	fgets(comanda, MAX, in);
	for (i = 0; i < n; i++) {
		fgets(comanda, MAX, in);
		//Comenzile ce trebuie adaugate in coada de comenzi
		if (comanda[0] == 'W' || comanda[0] == 'M' || comanda[0] == 'I') {
			C = IntrQ(C, comanda);
		}
		if (comanda[0] == 'S' && strlen(comanda) == 5) {
			SHOW(B);  //cazul "SHOW"
		}
		if (comanda[0] == 'S' && strlen(comanda) > 5) {
			SHOW_CURRENT(B);  //cazul "SHOW_CURRENT"
		}
		if (comanda[0] == 'E') {
			//cazul "EXECUTE"
			C = ExtrQ(C, comm_cur);
			if (comm_cur[0] == 'W') {
				//cazul WRITE <C>
				B = WRITE(B, comm_cur[6]);
				DistrS(&UNDO);
			} else if (comm_cur[0] == 'M') {
				temp = B->deget;
				if (strlen(comm_cur) <= 11) {
					if (comm_cur[5] == 'L') {
						B = MOVE_LEFT(B);  //cazul MOVE_LEFT
					} else {
						B = MOVE_RIGHT(B); //cazul MOVE_RIGHT
					}
				} else {
					if (comm_cur[5] == 'L') {
						B = MOVE_LEFT_CHAR(B, comm_cur[15]);  //cazul MOVE_LEFT_CHAR <C>
					} else {
						B = MOVE_RIGHT_CHAR(B, comm_cur[16]);  //cazul MOVE_RIGHT_CHAR <C>
					}
				}
				UNDO = IntrS(UNDO, temp);
			} else if (comm_cur[0] == 'I') {
				if (comm_cur[7] == 'L') {
					B = INSERT_LEFT(B, comm_cur[12]);  //cazul INSERT_LEFT <C>
				} else {
					B = INSERT_RIGHT(B, comm_cur[13]);  //cazul INSERT_RIGHT <C>
				}
				DistrS(&UNDO);
			} 
		}
		if (comanda[0] == 'U') {
			//cazul UNDO
			UNDO = ExtrS(UNDO, &temp);
			REDO = IntrS(REDO, B->deget);
			B->deget = temp;
		}
		if (comanda[0] == 'R') {
			//cazul REDO
			REDO = ExtrS(REDO, &temp);
			UNDO = IntrS(UNDO, B->deget);
			B->deget = temp;
		}
	}
	

	//Eliberez toata memoria alocata
	free(comanda);
	free(comm_cur);
	DistrugeBanda(&B);
	DistrQ(&C);
	DistrS(&UNDO);
	DistrS(&REDO);

	//Inchid fisierul din care citesc
	fclose(in);
	return 0;
}