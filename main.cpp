#include <iostream>
#include "conio2.h"

/* Uwaga: w docelowym programie nalezy zadeklarowac odpowiednie
   stale, na przyklad po to, aby wyeliminowac z programu
   wartosci numeryczne umieszczajac w ich miejsce 
   dobrze dobrane identyfikatory */

using namespace std;
int main()
{
	int zn, x = 40, y = 12, attr = 7;	
	settitle("imie nazwisko nr_indeksu");
	textbackground(BLACK);
	do {
		clrscr();
		textcolor(7);
		gotoxy(55, 1);
		cputs("q = wyjscie");
		gotoxy(55, 2);
		cputs("strzalki = poruszanie");
		gotoxy(55, 3);
		cputs("spacja = zmiana koloru");
		gotoxy(x, y);
		textcolor(attr);
		putch('*');
		zn = getch();
		if(zn == 0) {
			zn = getch();
			if(zn == 0x48) y--;
			else if(zn == 0x50) y++;
			else if(zn == 0x4b) x--;
			else if(zn == 0x4d) x++;
		} else if(zn == ' ') attr = (attr + 1) % 16;
	} while (zn != 'q');

	return 0;
}

