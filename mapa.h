#ifndef MAPA_H
#define MAPA_H

#define _CRT_SECURE_NO_WARNINGS

#include "conio2.h"

#define X 10
#define Y 10

struct punkt {
	int x;
	int y;
};

void stworzenie_mapy();
char** wczytanie_mapy(int* m, int* n, punkt *p1, punkt *p2);
void wypisanie_mapy(char** mapa, int m, int n);


#endif