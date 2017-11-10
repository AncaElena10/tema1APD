/**
*
* Autor: Moisa Anca-Elena
* Grupa: 331CA
* Tema1: Conway's Game of Life
* Varianta seriala
*
**/

#include <stdio.h>
#include <stdlib.h>

char **alocareMatrice(int nrLinii, int nrColoane) {
	int i;
	char **matrice;
	matrice = (char**) malloc((nrLinii + 2) * sizeof(char*));

	for (i = 0; i < nrLinii + 2; i++) {
		matrice[i] = (char*) calloc((nrColoane + 2), sizeof(char));
	}

	return matrice;
}

void eliberareMatrice(char **matrice, int nrLinii) {
	int i;

	/* eliberare linie cu linie */
	for (i = 0; i < nrLinii; i++) {
		free(matrice[i]);
	}
	free(matrice);
}

void bordare(char **aux, int nrLinii, int nrColoane) {
	int i;

	/* bordare matrice toroidala */

	/* bordare sus/jos */
	for (i = 1; i <= nrColoane; i++) {
		aux[0][i] = aux[nrLinii][i];
		aux[nrLinii + 1][i] = aux[1][i];
	}

	/* bordare stanga/dreapta */
	for (i = 1; i <= nrLinii; i++) {
		aux[i][0] = aux[i][nrColoane];
		aux[i][nrColoane + 1] = aux[i][1];
	}

	/* bordare colturi */
	aux[0][0] = aux[nrLinii][nrColoane];
	aux[0][nrColoane + 1] = aux[nrLinii][1];
	aux[nrLinii + 1][nrColoane + 1] = aux[1][1];
	aux[nrLinii + 1][0] = aux[1][nrColoane];
}

void inmultireCelule(char **aux, char **spatiu, int nrLinii, int nrColoane) {
	int sum = 0, i, j;
	char mark = 'X', none = '.';

	/* incepere algoritm */
	for (i = 1; i <= nrLinii; i++) {
		for (j = 1; j <= nrColoane; j++) {
			/* suma vecinilor unei celule */
			sum = aux[i - 1][j - 1] + aux[i - 1][j] + aux[i - 1][j + 1] +
				  aux[i + 1][j - 1] + aux[i + 1][j] + aux[i + 1][j + 1] +
				  aux[i][j - 1] + aux[i][j + 1];

			/* caut elementul cu 3 vecini */
			/* daca exista 3 vecini si casuta e goala, atunci se
			   va crea o noua celula */
			int alive = (int) mark, dead = (int) none;
			if (sum == 3 * alive + 5 * dead && spatiu[i][j] == none) {
				spatiu[i][j] = mark;
			}
			else {
				/* elimin celula care are 0, 1 sau 4 vecini */
				if (sum == 8 * dead || 
					sum < (2 * alive + 6 * dead) || 
					sum > (3 * alive + 5 * dead)) {
					spatiu[i][j] = none;
				}
			}
		}
	}
}

void copiere(char **aux, char **spatiu, int nrLinii, int nrColoane) {
	int i, j;

	/* pastrarea valorilor initiale ale matricei intr-o matrice noua */
	for (i = 0; i <= nrLinii + 1; i++) {
		for (j = 0; j <= nrColoane + 1; j++) {
			aux[i][j] = spatiu[i][j];
		}
	}
}

void afisare(char **spatiu, int nrLinii, int nrColoane, char *argv[]) {
	int i, j;
	FILE *fileOut;

	/* deschidere fisier de scriere */
	fileOut = fopen(argv[3], "w");

	if (fileOut == NULL){
    	printf("error");
    	exit(0);
	}

	for (i = 1; i <= nrLinii; i++) {
		for (j = 1; j <= nrColoane; j++) {
			fprintf(fileOut, "%c ", spatiu[i][j]);
		}	
	fprintf(fileOut, "\n");
	}

	/* inchidere fisier de scriere */
	fclose(fileOut);
}

int main(int argc, char *argv[]) {
	if(argc != 4){
		printf("./g_serial <nume_fisier_input> <numar_iteratii> <nume_fisier_output>\n");
		return 0;
	}

	int nrLinii, nrColoane, nrIteratii, i, j, k;
	char **spatiu, **aux;
	FILE *fileIn;

	/* deschidere fisiere de citire */
	fileIn = fopen(argv[1], "r");

	if (fileIn == NULL){
    	printf("error");
    	exit(0);
	}

	/* citire din fisier numarul de linii */
	fscanf(fileIn, "%d", &nrLinii);

	/* citire din fisier numarul de coloane */
	fscanf(fileIn, "%d", &nrColoane);

	/* alocare spatiu pentru matricea originala */
	spatiu = alocareMatrice(nrLinii, nrColoane);

	/* alocare spatiu pentru maticea auxiliara */
	aux = alocareMatrice(nrLinii, nrColoane);

	/* citire din fisier matricea */
	for (i = 1; i <= nrLinii; i++) {
		for (j = 1; j <= nrColoane; j++) {
			fscanf(fileIn, " %c", &spatiu[i][j]);
		}
	}

	/* extragere numar de iteratii din linia de comanda */
	nrIteratii = atoi(argv[2]);

	for (k = 1; k <= nrIteratii; k++) {
		copiere(aux, spatiu, nrLinii, nrColoane);
		bordare(aux, nrLinii, nrColoane);
		inmultireCelule(aux, spatiu, nrLinii, nrColoane);
	}

	afisare(spatiu, nrLinii, nrColoane, argv);

	/* eliberare spatiu matrice originala */
	eliberareMatrice(spatiu, nrLinii);

	/* eliberare spatiu matrice auxiliara */
	eliberareMatrice(aux, nrLinii);

/* inchidere fisiere de citire */
fclose(fileIn);

return 0;
}
