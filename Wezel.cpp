#include "Wezel.hpp"
using namespace std;

/*****************************************************************
 * Konstruktor bezparametryczny
 * tworzy pusty Wezel
 *****************************************************************/
Wezel::Wezel()
{
	waga = 0;
	ile_synow = 0;
	poziom = 0;
	ojciec = NULL;
	synowie = NULL;
}

/*****************************************************************
 * Kopiuje Wezel wraz ze wskaznikami
 *****************************************************************/
Wezel::Wezel(const Wezel &A)
{
	waga = A.waga;
	ile_synow = A.ile_synow;
	poziom = A.poziom;
	ruchy.clear();
	for (unsigned int i = 0; i < A.ruchy.size(); ++i) //kopiowanie ruchow
	{
		ruchy.push_back(A.ruchy[i]);
	}
	if (A.ojciec) // kopiowanie wskaznika do ojca jesli istnieje
	{
		ojciec = new Wezel;
		ojciec = A.ojciec;
	}
	else
		ojciec = NULL;
	if (A.synowie) // kopiowanie adresow do tablicy synow jesli istnieje
	{
		synowie = new Wezel*[ile_synow];
		for (int i = 0; i < ile_synow; i++)
		{
			synowie[i] = A.synowie[i];
		}
	}
	else
		synowie = NULL;
}

/*****************************************************************
 * usuwa wszystkich synow Wezla i zwalnia pamiec
 *****************************************************************/
Wezel::~Wezel()
{
	if (synowie != NULL)
	{
		for (int i = 0; i < ile_synow; i++)
		{
			if (synowie[i])
				delete synowie[i];
		}
		delete synowie;
	}

}

/*****************************************************************
 * przypisuje wage do Wezla
 *****************************************************************/
void Wezel::przypiszWage(int x)
{
	waga = x;
}

/*****************************************************************
 * Zwraca wage Wezla
 *****************************************************************/
int Wezel::Wartosc()
{
	return waga;
}

/*****************************************************************
 * Dodaje syna do Wezla
 * A-wezel ktory ma byc synem
 * a,b-wspolrzedne z ktorych wykonano ruch
 * c,d-wspolrzedne na ktore ruch byl wykonany
 *****************************************************************/
void Wezel::dodajSyna(Wezel *A, int a, int b, int c, int d)
{
	Wezel** tmp = NULL;
	if (synowie) // kopiowanie synow do pomocniczego Wezla
	{
		tmp = this->synowie;
	}
	this->synowie = new Wezel *[++ile_synow]; // powiekszenie tablicy synow
	if (tmp)
	{
		for (int i = 0; i < ile_synow - 1; i++)
		{
			this->synowie[i] = tmp[i]; //przypisanie z Wezla pomoicniczego synow do powiekszonej tablicy
		}
	}
	Ruch temp;
	temp.x1 = a;
	temp.y1 = b;
	temp.x2 = c;
	temp.y2 = d;
	A->ruchy.push_back(temp); // dodanie ruchu do Wezla A
	A->ojciec = this; // dodanie ojca do Wezla A
	A->poziom = poziom + 1; // zwiekszenie poziomu na ktorym wystepuje Wezel A
	this->synowie[ile_synow - 1] = A; // A staje sie synem
}

/*****************************************************************
 * Wyswietla synow tzn. ich wage oraz pierwszy ruch do wykonania
 *****************************************************************/
void Wezel::wyswietl_synow()
{
	for (int i = 0; i < ile_synow; ++i)
	{
		cout << synowie[i]->Wartosc() << ": " << synowie[i]->ruchy[0].x1 << " "
				<< synowie[i]->ruchy[0].y1 << " " << synowie[i]->ruchy[0].x2
				<< " " << synowie[i]->ruchy[0].y2 << endl;
	}
	cout << endl;
}

/*****************************************************************
 * sluzy do odwolania sie do konkretnego syna Wezla
 *****************************************************************/
Wezel Wezel::operator[](int x)
{
	return *synowie[x];
}

/*****************************************************************
 * zwraca ile synow ma dany Wezel
 *****************************************************************/
int Wezel::rozmiar()
{
	return ile_synow;
}

/*****************************************************************
 * Zwraca wartosc syna o minimalnej wadze
 *****************************************************************/
int Wezel::minimalny()
{
	int min;
	min = synowie[0]->Wartosc();
	for (int i = 0; i < ile_synow; ++i)
		if (synowie[i]->Wartosc() < min)
			min = synowie[i]->Wartosc();
	return min;
}

/*****************************************************************
 * Zwraca wartosc syna o maksymalnej wadze
 *****************************************************************/
int Wezel::maksymalny()
{
	int max;
	max = synowie[0]->Wartosc();
	for (int i = 0; i < ile_synow; ++i)
		if (synowie[i]->Wartosc() > max)
			max = synowie[i]->Wartosc();
	return max;
}

/*****************************************************************
 * zwraca poziom na ktorym znajduje sie Wezel
 *****************************************************************/
int Wezel::poz()
{
	return poziom;
}

/*****************************************************************
 * operator przypisania kopiuje Wezel
 *****************************************************************/
Wezel Wezel::operator=(const Wezel &A)
{
	waga = A.waga;
	ile_synow = A.ile_synow;
	poziom = A.poziom;
	ruchy.clear();
	for (unsigned int i = 0; i < A.ruchy.size(); ++i)
	{
		ruchy.push_back(A.ruchy[i]); // dodaje te same ruchy
	}
	if (A.ojciec) // kopiuje wskaznik na ojca jesli istnieje
	{
		ojciec = new Wezel;
		ojciec = A.ojciec;
	}
	else
		ojciec = NULL;
	if (A.synowie) // kopiuje tablice synow
	{
		synowie = new Wezel*[ile_synow];
		for (int i = 0; i < ile_synow; i++)
		{
			synowie[i] = A.synowie[i];
		}
	}
	else
		synowie = NULL;

	return *this;
}

/*****************************************************************
 * Funkcja kopiuje elementy Wezla takie jak ruchy oraz Waga
 *****************************************************************/
void Wezel::kopiujDane(const Wezel *A)
{
	waga = A->waga;
	ruchy.clear();
	for (unsigned int i = 0; i < A->ruchy.size(); ++i)
	{
		ruchy.push_back(A->ruchy[i]);
	}
}
