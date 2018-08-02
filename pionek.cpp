#include<string>
#include<iostream>
#include "pionek.hpp"
#include<cstring>
#include <fstream>
#include <iomanip>
#include "grafika.hpp"

using namespace std;

/**************************************************************
 * Konstruktor bezparametryczny
 * otoczenie pionka jest wyzerowane
 * domyslnie pionek nie jest damka
 *************************************************************/
pionek::pionek()
{
	x = 0;
	y = 0;
	team = 0;
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			ruchy[i][j] = 0;
	damka = false;
}

/**************************************************************
 * Konstruktor parametryczny
 * przypisuje do pionka takie elementy jak polozenie, adres
 * grafiki, oraz indeks zawodnika do ktorego nalezy
 *************************************************************/
pionek::pionek(int a, int b, char txt[50], int t)
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			ruchy[i][j] = 0;
	x = a;
	y = b;
	okreslGrafike(txt);
	team = t;
	damka = false;
}

pionek::~pionek()
{
	wektor.clear();
}

/**************************************************************
* Funkcja zeruje otoczenie pionka
 *************************************************************/
void pionek::zeruj()
{
	for (int j = 0; j < 8; ++j)
		for (int i = 0; i < 8; ++i)
			ruchy[i][j] = 0;
}

/**************************************************************
 * Funkcja przypisuje grafike do pionka
 *************************************************************/
void pionek::okreslGrafike(const char txt[50])
{
	strcpy(grafika, txt);
}

/**************************************************************
 * Funkcja przypisuje indeks zawodnika do pionka
 *************************************************************/
void pionek::dTeam(int t)
{
	team = t;
}

/**************************************************************
 * Funkcja zmienia wspolrzedne polorzenia pionka, a gdy okaze
 * sie ze pionek znajduje sie na polu czyniacym z niego damke,
 * zamienia go w damke
 *************************************************************/
void pionek::zmien_pole(int a, int b)
{
	x = a;
	y = b;
	if (team == 1 && y == P1) // gdy pion dotrze do pola damki
	{
		char txt[] =
		{ "img/p_krol.bmp" };
		okreslGrafike(txt); // ustawia grafike damki
		damka = true;
	}
	if (team == 2 && y == P8) // gdy pion dotrze do pola damki
	{
		char txt[] =
		{ "img/z_krol.bmp" };
		okreslGrafike(txt); // ustawia grafike damki
		damka = true;
	}
}

/**************************************************************
 * Funkcja wyswietla wszystkie mozliwe ruchy danego pionka
 *************************************************************/
void pionek::wyswietl_ruchy()
{
	for (int j = 0; j < 8; ++j)
	{
		for (int i = 0; i < 8; ++i)
			cout << ruchy[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

/**************************************************************
 * Funkcja sprawdza czy wystepuje bicie danym pionkiem
 *************************************************************/
bool pionek::czyBicie()
{
	for (int j = 0; j < 8; ++j)
		for (int i = 0; i < 8; ++i)
			if (ruchy[i][j] == 4)
				return true;
	return false;
}

/**************************************************************
 * Funkcja sprawdza istnieje ruch danym pionkiem
 *************************************************************/
bool pionek::czyRuch()
{
	for (int j = 0; j < 8; ++j)
		for (int i = 0; i < 8; ++i)
			if ((ruchy[i][j] == 2 || ruchy[i][j] == 4) && x != SIZEA)
				return true;
	return false;
}

/**************************************************************
 * Funkcja zwraca ilosc ruchow mozliwych do wykonania danym
 * pionkiem, przy okazji dodajac znalezione ruchy do tablicy wektor
 *************************************************************/
int pionek::ileRuchow(int A)
{
	int tmp = 0;
	Ruch tmp2;
	wektor.clear();
	for (int j = 0; j < 8; ++j)
		for (int i = 0; i < 8; ++i)
			if (ruchy[i][j] == 1 && x != SIZEA)
			{
				tmp2.x1 = i;
				tmp2.y1 = j;
			}
	if (A == 1) // jeœli sa znajduje ruchy z biciami
		for (int j = 0; j < 8; ++j)
			for (int i = 0; i < 8; ++i)
				if (ruchy[i][j] == 4 && x != SIZEA)
				{
					tmp++;
					tmp2.x2 = i;
					tmp2.y2 = j;
					wektor.push_back(tmp2);
				}

	if (A == 0) // jesli nie ma bicia znajduje pozostale ruchy
		for (int j = 0; j < 8; ++j)
			for (int i = 0; i < 8; ++i)
				if (ruchy[i][j] == 2 && x != SIZEA)
				{
					tmp++;
					tmp2.x2 = i;
					tmp2.y2 = j;
					wektor.push_back(tmp2);
				}

	return tmp;
}
