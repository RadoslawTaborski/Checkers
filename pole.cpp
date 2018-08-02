#include "pole.hpp"
#include <iostream>
#include "grafika.hpp"

using namespace std;

/*****************************************************************
 * nrP=-1 oznacza brak pionka na polu
 * domyslnie pole znajduje sie poza obszarem widocznym
 *****************************************************************/
pole::pole()
{
	P = 0;
	nrP = -1;
	Xmin = SIZEA;
	Ymin = SIZEB-SIZE_PY;
	Xmax = SIZEA+SIZE_PX;
	Ymax = SIZEB;
}

pole::~pole()
{
}

/*****************************************************************
 * Dodaje pion do pola
 * jeli pionek staje sie damka po wejsciu na dane pole to
 * jest oznaczany jako 11 dla gracza 1, a 22 dla gracza drugiego
 *****************************************************************/
void pole::dodajP(int pion)
{
	P = pion;
	if (pion == 1 && Ymin == P1)
		P = pion + 10;
	if (pion == 2 && Ymin == P8)
		P = pion + 20;
}

/*****************************************************************
 * pionek na danym polu przestaje istniec (mogl byc zbity lub przesuniety)
 *****************************************************************/
void pole::usunP()
{
	P = 0;
}

/*****************************************************************
 * tworzy pole okreslane przez Xa, Xb,Ya,Yb
 *****************************************************************/
void pole::utworz(int Xa, int Xb, int Ya, int Yb)
{
	Xmin = Xa;
	Xmax = Xb;
	Ymin = Ya;
	Ymax = Yb;
}

/*****************************************************************
 * Jesli klikniecie myszka odbylo sie w obszar okreslony przez pole
 * to zwraca true
 *****************************************************************/
bool pole::klik(int mx, int my)
{
	if (mx > Xmin && mx < Xmax)
	{
		if (my > Ymin && my < Ymax)
			return true;
	}
	return false;
}

/*****************************************************************
 * Sprawdza czy na danym polu znajduje sie pionek
 *****************************************************************/
bool pole::czyPionek(int index)
{
	if (P == index || P == index + 10 || P == index + 20)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*****************************************************************
* operator porownuje czy na tym samym polu znajduje sie ten sam pion
 *****************************************************************/
bool pole::operator==(pole &tmp)
{
	if (P == tmp.P && X() == tmp.X() && Y() == tmp.Y())
		return true;
	else
		return false;
}
