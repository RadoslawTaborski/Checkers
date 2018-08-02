#ifndef RUCH_HPP
#define RUCH_HPP

#include<iostream>

/*****************************************************************
 * Struktura przechowujaca wspolrzedne ruchu
 * x1,y1 - wspolrzedne pola z ktorego ma byc wykonany ruch
 * x2,y2 - wspolrzedne pola na ktory ma byc wykonany ruch
 *****************************************************************/
struct Ruch
{
	int x1;
	int y1;
	int x2;
	int y2;

	Ruch()
	{
		x1 = 0;
		x2 = 0;
		y1 = 0;
		y2 = 0;
	}
	Ruch(int a, int b, int c, int d)
	{
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}
};

#endif
