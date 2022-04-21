#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "conio2.h"
#include <time.h>
#include <stdio.h>
#include "mapa.h"

using namespace std;

#define X 10
#define Y 10

enum kierunek {
	GORA, PRAWO, DOL, LEWO
};

char kursor[4] = { '^', '>', 'v', '<' };


void ruch(punkt *p, int *k, int m, int n, char **mapa, int *liczba_ruchow) {

	int pX = p->x - X, pY = p->y - Y;
	char zn = getch();
	switch (zn) {
		case 0x48:
			switch (*k) {
				case GORA:
					if (p->y > Y) {
						if (mapa[pY - 1][pX] == ' ' || mapa[pY - 1][pX] == '@') {
							(p->y)--;
							(*liczba_ruchow)++;
						}
					}
						
					break;
				case PRAWO:
					if (p->x < X + n - 1) {
						if (mapa[pY][pX + 1] == ' ' || mapa[pY][pX + 1] == '@') {
							(p->x)++;
							(*liczba_ruchow)++;
						}
					}
					break;
				case DOL:
					if (p->y < Y + m - 1) {
						if (mapa[pY + 1][pX] == ' ' || mapa[pY + 1][pX] == '@') {
							(p->y)++;
							(*liczba_ruchow)++;
						}
					}
					break;
				case LEWO:
					if (p->x > X) {
						if (mapa[pY][pX - 1] == ' ' || mapa[pY][pX - 1] == '@') {
							(p->x)--;
							(*liczba_ruchow)++;
						}
					}
					break;
			}
			break;
		case 0x50:
			switch (*k) {
			case GORA:
				if (p->y < Y + m - 1) {
					if (mapa[pY + 1][pX] == ' ' || mapa[pY + 1][pX] == '@') {
						(p->y)++;
						(*liczba_ruchow)++;
					}
				}
				break;
			case PRAWO:
				if (p->x > X) {
					if (mapa[pY][pX - 1] == ' ' || mapa[pY][pX - 1] == '@') {
						(p->x)--;
						(*liczba_ruchow)++;
					}
				}
				break;
			case DOL:
				if (p->y > Y) {
					if (mapa[pY - 1][pX] == ' ' || mapa[pY - 1][pX] == '@') {
						(p->y)--;
						(*liczba_ruchow)++;
					}
				}
				break;
			case LEWO:
				if (p->x < X + n - 1) {
					if (mapa[pY][pX + 1] == ' ' || mapa[pY][pX + 1] == '@') {
						(p->x)++;
						(*liczba_ruchow)++;
					}
				}
				break;
			}
			break;
		case 0x4b:
			if (*k > 0) (*k)--;
			else *k = LEWO;
			break;
		case 0x4d:
			if (*k < 3) (*k)++;
			else *k = GORA;
			break;
	}
}

void drzwi(int *k, char **mapa, punkt *p) {
	switch (*k) {
		case GORA:
			if (mapa[p->y - Y - 1][p->x - X] == '&')
				mapa[p->y - Y - 1][p->x - X] = '@';
			break;
		case PRAWO:
			if (mapa[p->y - Y][p->x - X + 1] == '&')
				mapa[p->y - Y][p->x - X + 1] = '@';
			break;
		case DOL:
			if (mapa[p->y - Y + 1][p->x - X] == '&')
				mapa[p->y - Y + 1][p->x - X] = '@';
			break;
		case LEWO:
			if (mapa[p->y - Y][p->x - X - 1] == '&')
				mapa[p->y - Y][p->x - X - 1] = '@';
			break;
	}
}

void przycisk(char zn) {
	
}

void menu() {
	gotoxy(55, 1);
	cputs("q = wyjscie");
	gotoxy(55, 2);
	cputs("strzalki = poruszanie");
	gotoxy(55, 3);
	cputs("spacja = zmiana koloru");
}


/*int main()
{
	int zn, attr = 7, rozmiar = 0, k = DOL, m = 0, n = 0;
	punkt p, p1, p2;
	p.x = 10; p.y = 10;
	p1.x = 0; p1.y = 0;
	p2.x = 0; p2.y = 0;
	int liczba_ruchow = 0;
	char** mapa = NULL;
	char czas_text[] = "Czas gry wynosi      sekund";
	char znak = kursor[k];

	bool wczytana_mapa = false;
	bool koniec_gry = false;

	settitle("Labirynt");

	clock_t start = clock();
	
	
	do {
		
		textbackground(BLACK);
		clrscr();
		textcolor(7);
		menu();
		gotoxy(10, 1);
		cputs(czas_text);
		
		if (wczytana_mapa) {
			wypisanie_mapy(mapa, m, n);
			clock_t end = clock();
			float seconds = (float)(end - start) / CLOCKS_PER_SEC;
			int sekundy = seconds;

			int l = 0;
			while (sekundy > 0) {
				int temp = sekundy % 10;
				sekundy /= 10;
				czas_text[18 - l] = temp + '0';
			}
		}


		textbackground(BLACK);
		gotoxy(p.x, p.y);
		textcolor(attr);
		putch(kursor[k]);
		zn = getch();


		switch (zn) {
		case 0:
			ruch(&p, &k, m, n, mapa, &liczba_ruchow);
			if (wczytana_mapa) {
				if (p.x == p2.x + X - 1 && p.y == p2.y + Y - 1)
					koniec_gry = true;
			}

			break;
		case ' ':
			attr = (attr + 1) % 16;
			break;
		case 'd':
			drzwi(&k, mapa, &p);
			break;
		case 'i':
			mapa = wczytanie_mapy(&m, &n, &p1, &p2);
			p.x = p1.x + X - 1;
			p.y = p1.y + Y - 1;
			wczytana_mapa = true;
			start = clock();
			break;
		case 'q':
			koniec_gry = true;
			break;
		}
		
	} while (!koniec_gry);

	if (m > 0) {
		for (int i = 0; i < m; i++) {
			delete[] mapa[i];
		}
		delete[] mapa;
	}

	return 0;
}
*/

void rysowanie_(int numer) {
	int x, y;

	if (numer <= 4) {
		x = (numer - 1) * 3 + 1;
		y = numer;
		gotoxy(x, y);
		putch('_');
		gotoxy(x + 1, y);
		putch('_');

		y = 20 - numer;

		gotoxy(x, y);
		putch('_');
		gotoxy(x + 1, y);
		putch('_');
	}
	else if(numer > 4 && numer <= 7){
		x = numer * 2 + 3;
		y = numer;

		gotoxy(x, y);
		putch('_');

		y = 20 - numer;
		gotoxy(x, y);
		putch('_');
	}
	else if (numer >= 8 && numer <= 10) {

	}
	else if (numer >= 11 && numer <= 14) {

	}

	
}

void rysowanie_slash(int numer) {
	int x, y;
	if (numer <= 4) {
		x = numer * 3;
		y = numer + 1;
	}
	else if(numer > 4 && numer <=7) {
		x = numer * 3 + (4 - numer);
		y = numer + 1;
	}
	else if (numer >= 8 && numer <= 10) {
		x = (numer - 2) * 3 + 11 - numer;
		y = numer + 5;
	}
	else if (numer >= 11 && numer <= 14) {
		x = (numer - 2) * 3;
		y = numer + 5;
	}
	gotoxy(x, y);
	putch('\\');
}

void rysowanie_backslash(int numer) {
	int x, y;
	if (numer <= 4) {
		x = numer * 3;
		y = 20 - numer;
	}
	else if (numer > 4 && numer <= 7) {
		x = numer * 3 + (4 - numer);
		y = 20 - numer;
	}
	else if (numer >= 8 && numer <= 10) {
		x = (numer - 2) * 3 + 11 - numer;
		y = 16 - numer;
	}
	else if (numer >= 11 && numer <= 14) {
		x = (numer - 2) * 3;
		y = 16 - numer;
	}
	gotoxy(x, y);
	putch('/');
}

void rysowanie_kreski(int numer) {
	int x, y, y1, y2;
	if (numer <= 4) {
		x = numer * 3;
		y1 = numer + 2;
		y2 = 20 - numer - 1;
	}
	else if (numer > 4 && numer <= 7) {
		x = numer * 3 + (4 - numer);
		y1 = numer + 2;
		y2 = 20 - numer - 1;
	}
	else if (numer >= 8 && numer <= 10) {
		x = (numer - 2) * 3 + 11 - numer;
		y1 = numer - (numer - 7) * 2 + 3;
		y2 = 20 - (numer - (numer - 7) * 2 + 3) - 2;
	}
	else if (numer >= 11 && numer <= 14) {
		x = (numer - 2) * 3;
		y1 = numer - (numer - 7) * 2 + 3;
		y2 = 20 - (numer - (numer - 7) * 2 + 3) - 2;
	}
	for (int i = y1; i <= y2; i++) {
		gotoxy(x, i);
		putch('|');
	}
	
	
}

void rysowanie_sciany(int numer) {
	textcolor(2);
	rysowanie_(numer);
	rysowanie_slash(numer);
	rysowanie_kreski(numer);
	rysowanie_backslash(numer);

}

int main() {
	textbackground(BLACK);
	clrscr();
	rysowanie_sciany(1);
	rysowanie_sciany(2);
	rysowanie_sciany(3);
	rysowanie_sciany(4);
	rysowanie_sciany(5);
	rysowanie_sciany(6);
	rysowanie_sciany(7);
	rysowanie_sciany(8);
	rysowanie_sciany(9);
	char zn = getch();
	return 0;
}
