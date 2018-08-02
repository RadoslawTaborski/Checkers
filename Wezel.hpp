#ifndef WEZEL_HPP
#define WEZEL_HPP

#include"Ruch.hpp"
#include<iostream>
#include<vector>

using namespace std;

/*****************************************************************
 * Klasa okresla Wezel drzewa
 * posiada ona wskaznik na "ojca" oraz tablice wskaznikow na "synow"
 * Taki obiekt posiada swoja wage
 * aktualny poziom na ktorym sie znajduje w drzewie
 * liczbe swoich synow
 * oraz przechowuje wektor ruchow wykonywanych
 *****************************************************************/
class Wezel
{
	int waga; //waga
	int ile_synow; // liczba synow
	int poziom; // poziom na ktorym sie znajduje w drzewie
public:
	Wezel *ojciec; //wskaznik na ojca
	Wezel **synowie; //wskaznik na tablice synow
	vector<Ruch> ruchy; //wektor ruchow wykonywanych w tym wezle
	int rozmiar(); //rozmiar tablicy synow
	Wezel();
	Wezel(const Wezel &A);
	~Wezel();
	void przypiszWage(int x); // przypisuje wage do Wezla
	int Wartosc(); // zwraca wage Wezla
	void dodajSyna(Wezel *A,  int a, int b, int c, int d); // dodaje syna do Wezla
	void wyswietl_synow();// wyswietla synow
	int minimalny(); // znajduje syna o minimalnej wartosci
	int maksymalny(); //znajduje syna o maksymalnej wadze
	int poz(); // zwraca poziom
	Wezel operator[](int x); // operator odwoluje sie do konkretnego syna
	Wezel operator=(const Wezel &A); //operator przypisania
	void kopiujDane(const Wezel *A); // kopiuje wage oraz ruchy
};

#endif // WEZEL_HPP
