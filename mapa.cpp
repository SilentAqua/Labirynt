#include "mapa.h"
#include <stdio.h>


void stworzenie_mapy() {

}

char** wczytanie_mapy(int* m, int* n, punkt *p1, punkt *p2) {
	FILE* plik = fopen("mapa.txt", "r");
	char** mapa = NULL;
	char ch;
	int i = 0, j = 0;
	fscanf(plik, "%d", m);
	fscanf(plik, "%d", n);
	fscanf(plik, "%d", &p1->x);
	fscanf(plik, "%d", &p1->y);
	fscanf(plik, "%d", &p2->x);
	fscanf(plik, "%d\n", &p2->y);

	int l = *m;
	int k = *n;

	mapa = new char* [l];
	for (int a = 0; a < l; a++) {
		mapa[a] = new char[k];
	}


	while ((ch = fgetc(plik)) != EOF) {
		if (ch == '\n') {
			i++;
			j = 0;
		}
		else {
			switch (ch) {
			case '0':
				mapa[i][j] = ' '; //œcie¿ka
				break;
			case '1':
				mapa[i][j] = '#'; //œciana
				break;
			case '2':
				mapa[i][j] = '@'; //drzwi otwarte
				break;
			case '3':
				mapa[i][j] = '&'; //drzwi zamkniête
				break;
			case '4':
				mapa[i][j] = '%'; //kamieñ
				break;
			case '5':
				mapa[i][j] = '$'; //drzewo
				break;
			}
			j++;
		}
	}

	fclose(plik);
	return mapa;
}

void wypisanie_mapy(char** mapa, int m, int n) {
	textbackground(GREEN);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			gotoxy(X + j, Y + i);
			putch(mapa[i][j]);
		}
	}
}