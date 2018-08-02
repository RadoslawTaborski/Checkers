#include "komputer.hpp"
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "grafika.hpp"

using namespace std;
/************************************************************
 * konstruktor bezparametryczny
 * tworzy dynamiczna dwuwymiarowa tablice Wezlow, ktore
 * pierwszy indeks tablicy oznacza Wezly znajdujace sie na
 * danym poziomie drzewa
 ***********************************************************/
komputer::komputer()
{
	korzen = NULL;
	vector<Wezel*> *A;
	for (int i = 0; i < POZIOM; ++i)
	{
		A = new vector<Wezel*>;
		drzewo.push_back(*A);
	}
}

komputer::~komputer()
{
}

/************************************************************
 * funkcja oceniajaca stan partii
 * znalezienie stanu konca gry zwraca KONIEC
 * stan gry oceniany jest poprzez sume punktow za ilosc
 * pionkow i damek (damki maja znacznie wieksza wage niz pionki)
 * oraz polozenie pionkow na planszy
 * Plansza zostala podzielona na 4 poziomy
 * za znajdowanie pionka na danym poziomie przyznawane sa
 * dodatkowe punkty. Premiuje to ruchy do przodu oraz nie
 * poruszanie sie pionkami broniacymi sie przed zdobyciem damki
 * przez przeciwnika
 ***********************************************************/
int komputer::ocen(partia tmp)
{
	if (tmp.A.brakRuchow())
		return -KONIEC; // sytuacja gdy gracz wygrywa
	if (tmp.B.brakRuchow())
		return KONIEC; // sytuacja gdy komputer wygrywa
	int ocena = 0;
	for (unsigned int i = 0; i < 12; ++i)
	{
		if (tmp.A.lista[i].x != SIZEA)
		{
			if (!tmp.A.lista[i].damka)
			{
				ocena += PIONEK; // sumowanie punktow za zwykly pionek komputera
				if (!(tmp.A.lista[i].y >= P8) && !(tmp.A.lista[i].y <= P7))
				{
					ocena += STREFA0; // punkty za przebywanie w STREFIE0
				}
				else if (!(tmp.A.lista[i].y >= P6) && !(tmp.A.lista[i].y <= P5))
				{
					ocena += STREFA1; // punkty za przebywanie w STREFIE1
				}
				else if (!(tmp.A.lista[i].y >= P4) && !(tmp.A.lista[i].y <= P3))
				{
					ocena += STREFA2; // punkty za przebywanie w STREFIE2
				}
				else if (!(tmp.A.lista[i].y >= P2) && !(tmp.A.lista[i].y <= P5))
				{
					ocena += STREFA3; // punkty za przebywanie w STREFIE0
				}
			}
			else
			{
				ocena += DAMKA; // dodawanie punktow za damki komputera
			}
		}
		if (tmp.B.lista[i].x != SIZEA)
		{
			if (!tmp.B.lista[i].damka)
			{
				ocena -= PIONEK; //odejmowanie punktow za pionki gracza
				if (!(tmp.B.lista[i].y >= P8) && !(tmp.B.lista[i].y <= P7))
				{
					ocena -= STREFA3; // ujemne punkty za przebywanie pionka gracza w STREFIE3
				}
				else if (!(tmp.B.lista[i].y >= P6) && !(tmp.B.lista[i].y <= P5))
				{
					ocena -= STREFA2; // ujemne punkty za przebywanie pionka gracza w STREFIE2
				}
				else if (!(tmp.B.lista[i].y >= P4) && !(tmp.B.lista[i].y <= P3))
				{
					ocena -= STREFA1; // ujemne punkty za przebywanie pionka gracza w STREFIE1
				}
				else if (!(tmp.B.lista[i].y >= P2) && !(tmp.B.lista[i].y <= P1))
				{
					ocena -= STREFA0; // ujemne punkty za przebywanie pionka gracza w STREFIE0
				}
			}
			else
			{
				ocena -= DAMKA; //odejmowanie punktow za damki gracza
			}
		}
	}
	return ocena;
}

/************************************************************
 * Funkcja ta tworzy drzewo przyszlych stadiow gry
 * oraz uzupelnia dwuwymiarowa tablice Wezlami znajdujocymi sie
 * danym poziomie
 * Funkcja ta tworzy dwa poziomy drzewa a dziêki zwiekszeniu
 * poziomu rekurencji mozliwe jest uzyskanie wielokrotnosci tej
 * liczby tzn. 4 ruchy w przod, 6 , 8.
 * poziom- oznacza poziom rekurencji
 * Partia- obecny stan gry
 * podstawa- korzen drzewa
 ***********************************************************/
void komputer::utworzDrzewo(int poziom, const partia &Partia, Wezel *podstawa)
{
	bool bicie = false;
	Wezel *galaz;
	partia tmp, tmp2; //pomocnicze zmienne typu Partia
	tmp = Partia; // kopiowanie stanu gry

	int index = 0;
	//przegladanie wszystkich mozliwych ruchow gracza A
	for (unsigned int i = 0; i < Partia.A.lista.size(); ++i)
	{
		for (unsigned int j = 0; j < Partia.A.lista[i].wektor.size(); ++j)
		{
			bicie = false;
			tmp = Partia;
			int x1, x2, y1, y2, t;
			int a, b, c, d;
			a = tmp.A.lista[i].wektor[j].x1; //przypisanie wspolrzednych ruchu
			b = tmp.A.lista[i].wektor[j].y1;
			c = tmp.A.lista[i].wektor[j].x2;
			d = tmp.A.lista[i].wektor[j].y2;
			do //petla wykonujaca sie poki istnieja bicia danym pionkiem
			{
				if (bicie == true) // jesli wykonano juz jeden ruch ktory byl biciem
				{
					int c1 = c;
					int d1 = d;
					int nr = 0;
					a = tmp.A.lista[tmp.PL.pl[c1][d1].nrP].wektor[nr].x1; //przypisanie wspolrzednych ruchu
					b = tmp.A.lista[tmp.PL.pl[c1][d1].nrP].wektor[nr].y1;
					c = tmp.A.lista[tmp.PL.pl[c1][d1].nrP].wektor[nr].x2;
					d = tmp.A.lista[tmp.PL.pl[c1][d1].nrP].wektor[nr].y2;

					Ruch R(a, b, c, d);
					podstawa->synowie[index - 1]->ruchy.push_back(R);
				}
				else
				{
					galaz = new Wezel;
					podstawa->dodajSyna(galaz, a, b, c, d); // dodanie Wezla do drzewa przechowujacego wykonany ruch
					index++;
				}
				tmp.A.lista[tmp.PL.pl[a][b].nrP].zmien_pole(tmp.PL.pl[c][d].X(),
						tmp.PL.pl[c][d].Y()); //przeniesienie pionka we wskazane miejsce
				tmp.PL.pl[c][d].dodajP(tmp.PL.pl[a][b].P); //dodanie pionka do nowego miejsca
				tmp.PL.pl[a][b].usunP(); //usuniecie pionka z poprzedniego miejsca
				tmp.PL.pl[c][d].nrP = tmp.PL.pl[a][b].nrP; //przeniesienie pionka
				tmp.PL.pl[a][b].nrP = -1;
				/* poni¿sze 5 linii okresla po wzdluz jakiej przekatnej odbywa sie ruch*/
				t = ((a > c && b > d) || (a < c && b < d)) ? 1 : 0;
				x1 = (a > c) ? a : c;
				x2 = (a > c) ? c : a;
				y1 = t ? (b > d) ? b : d:(b > d) ? d : b;
				y2 = t ? (b > d) ? d : b:(b > d) ? b : d;
				while ((x1 > x2 + 1 && y1 > y2 + 1 && t)
						|| (x1 > x2 + 1 && y2 > y1 && !t))
				{
					t ? (x1-- && y1--) : (x1-- && y1++); // inkrementacja w zaleznosci od przekatnej po ktorej odbywa sie ruch
					if (tmp.PL.pl[x1][y1].nrP != -1) // komendy usuwajace zbity pionek z planszy
					{
						tmp.B.ilosc--;
						bicie = true;
						tmp.PL.pl[x1][y1].usunP();
						tmp.B.lista[tmp.PL.pl[x1][y1].nrP].zmien_pole(SIZEA,
								SIZEB);
						tmp.PL.pl[x1][y1].nrP = -1;
					}
				}
				tmp.ruchyA(); //aktualizacja sytuacji gracza A na planszy poprzez znajdowanie nowych mozliwosci ruchu
				tmp.ruchyADamka();
				tmp.A.liczbaRuchow();
			} while (bicie && tmp.A.lista[tmp.PL.pl[c][d].nrP].czyBicie()); //poki badany pionek ma bicia to petla trwa
			bicie = false;
			podstawa->synowie[index - 1]->przypiszWage(ocen(tmp)); // ocenia sytuajcjê i ocene przypisuje do Wezla
			drzewo[galaz->poz()].push_back(galaz); // dodanie Wezla na odpowiedni poziom tablicy
			tmp.ruchyB();  //aktualizacja sytuacji gracza B na planszy poprzez znajdowanie nowych mozliwosci ruchu
			tmp.ruchyBDamka();
			tmp.B.liczbaRuchow();
			tmp2 = tmp; // kopiowanie sytuacji uzyskanej przed chwila
			for (unsigned int k = 0; k < tmp2.B.lista.size(); ++k) //przegladanie ruchow gracza B
			{
				for (unsigned int l = 0; l < tmp2.B.lista[k].wektor.size(); ++l)
				{
					bicie = false;
					tmp = tmp2;

					int x1, x2, y1, y2, t;

					a = tmp.B.lista[k].wektor[l].x1; //przypisanie wspolrzednych ruchu
					b = tmp.B.lista[k].wektor[l].y1;
					c = tmp.B.lista[k].wektor[l].x2;
					d = tmp.B.lista[k].wektor[l].y2;
					do //poki badany pionek ma bicia
					{
						if (bicie == true) // jesli odbylo sie juz bicie to przypisuje wspolrzedne nastepnego bicia
						{
							int c1 = c;
							int d1 = d;
							int nr = 0;
							a =
									tmp.B.lista[tmp.PL.pl[c1][d1].nrP].wektor[nr].x1; //przypisanie wspolrzednych ruchu
							b =
									tmp.B.lista[tmp.PL.pl[c1][d1].nrP].wektor[nr].y1;
							c =
									tmp.B.lista[tmp.PL.pl[c1][d1].nrP].wektor[nr].x2;
							d =
									tmp.B.lista[tmp.PL.pl[c1][d1].nrP].wektor[nr].y2;
							Ruch R(a, b, c, d);
							podstawa->synowie[index - 1]->synowie[podstawa->synowie[index
									- 1]->rozmiar() - 1]->ruchy.push_back(R); // dodanie "wnuka" sytuacji z poczatku funkcji
						}
						else
						{
							galaz = new Wezel;
							podstawa->synowie[index - 1]->dodajSyna(galaz, a, b,
									c, d);
						}
						tmp.B.lista[tmp.PL.pl[a][b].nrP].zmien_pole(
								tmp.PL.pl[c][d].X(), tmp.PL.pl[c][d].Y()); //przeniesienie pionka we wskazane miejsce
						tmp.PL.pl[c][d].dodajP(tmp.PL.pl[a][b].P);
						tmp.PL.pl[a][b].usunP();
						tmp.PL.pl[c][d].nrP = tmp.PL.pl[a][b].nrP; //usuniecie pionka z poprzedniego miejsca
						tmp.PL.pl[a][b].nrP = -1;
						//okreslenie przekatnej po ktorej odywa sie ruch
						t = ((a > c && b > d) || (a < c && b < d)) ? 1 : 0;
						x1 = (a > c) ? a : c;
						x2 = (a > c) ? c : a;
						y1 = t ? (b > d) ? b : d:(b > d) ? d : b;
						y2 = t ? (b > d) ? d : b:(b > d) ? b : d;
						while ((x1 > x2 + 1 && y1 > y2 + 1 && t)
								|| (x1 > x2 + 1 && y2 > y1 && !t))
						{
							t ? (x1-- && y1--) : (x1-- && y1++); // iteruje pola w zaleznosci od przekatnej ruchu
							if (tmp.PL.pl[x1][y1].nrP != -1) // gdy bicie
							{
								tmp.A.ilosc--;
								tmp.PL.pl[x1][y1].usunP();
								tmp.A.lista[tmp.PL.pl[x1][y1].nrP].zmien_pole(
										SIZEA, SIZEB);
								tmp.PL.pl[x1][y1].nrP = -1;
								bicie = true;
							}
						}
						tmp.ruchyB(); // aktualizacja mozliwych ruchow gracza B
						tmp.ruchyBDamka();
						tmp.B.liczbaRuchow();
					} while (bicie
							&& tmp.B.lista[tmp.PL.pl[c][d].nrP].czyBicie()); //poki badany pionek ma bicie
					bicie = false;
					podstawa->synowie[index - 1]->synowie[podstawa->synowie[index
							- 1]->rozmiar() - 1]->przypiszWage(ocen(tmp)); // przypisanie "wnukowi" wagi
					drzewo[galaz->poz()].push_back(galaz); // dodanie wezla do tablicy na danym poziomie

					if (poziom > 3) //wywolanie rekurencyjne budujace drzewo o wiekszym poziomie zlozonosci
					{
						tmp.ruchyA();
						tmp.ruchyADamka();
						tmp.A.liczbaRuchow();
						utworzDrzewo(poziom - 2, tmp,
								podstawa->synowie[index - 1]->synowie[podstawa->synowie[index
										- 1]->rozmiar() - 1]);
					}
				}
			}
		}
	}
}

/************************************************************
 * Funkcja ocenia drzewo zaczynajac od badania synow przed-
 * ostatniego poziomu, Funkcja kolejno przypisuje wartoœci
 * wg zasady MINMAX az dojdzie do korzenia
 ***********************************************************/
void komputer::ocen_drzewo()
{
	cout << "LISCIE: " << drzewo[POZIOM - 1].size() << endl;
	for (unsigned i = POZIOM - 2; i > 0; --i)
		for (unsigned int j = 0; j < drzewo[i].size(); ++j)
			if (drzewo[i][j]->rozmiar() != 0)
			{
				if (i % 2) // jesli poziom parzysty
				{
					drzewo[i][j]->przypiszWage(drzewo[i][j]->minimalny()); //znajduje minimalnego syna
				}
				else //jesli nieparzysty
				{
					drzewo[i][j]->przypiszWage(drzewo[i][j]->maksymalny()); //znajduje maksymalnego syna
				}
			}
}

/************************************************************
 * Funkcja spoœród synów korzenia wybiera tego o najwiêkszej
 * wartoœci i przypisuje ruch ktory przechowywal jako swoj ruch
 ***********************************************************/
void komputer::wybor_ruchu()
{
	int index = 0;
	int max = 0;
	if (korzen)
		max = korzen->synowie[0]->Wartosc();
	for (int i = 0; i < korzen->rozmiar(); i++) // znalezienie syna o najwiekszej Wartosci
		if (korzen->synowie[i]->Wartosc() > max)
		{
			max = korzen->synowie[i]->Wartosc();
			index = i;
		}
	korzen->kopiujDane(korzen->synowie[index]); // kopiowanie ruchu wraz z Wartoœci¹
}

/************************************************************
 * Funkcja wykonuje ruch, poprzez stworzenie i ocenienie drzewa
 * a nastepnie poprzez wykonanie ruchu znajdujacego sie
 * w korzeniu drzewa
 ***********************************************************/
void komputer::wykonaj_ruch(partia &PART)
{
	for (unsigned int i = 0; i < drzewo.size(); ++i)
		drzewo[i].clear(); // czyœci zawartosc tablicy dynamicznej drzewo

	int a, b, c, d, t, x1, x2, y2, y1;
	PART.ruchyA(); //aktualizuje sytuacje na planszy poprzez znalezienie aktualnie mozliwych ruchow
	PART.ruchyADamka();
	PART.ruchyB();
	PART.ruchyBDamka();
	PART.A.liczbaRuchow();
	PART.B.liczbaRuchow();

	korzen = new Wezel; //utworzenie korzenia

	utworzDrzewo(POZIOM, PART, korzen); //utworzenie drzewa
	ocen_drzewo(); //ocenienie drzewa
	wybor_ruchu();
	for (unsigned int i = 0; i < korzen->ruchy.size(); ++i) //wykonuje ruch badz kombinacje ruchow bijacych
	{
		a = korzen->ruchy[i].x1; //przypisanie ruchu
		b = korzen->ruchy[i].y1;
		c = korzen->ruchy[i].x2;
		d = korzen->ruchy[i].y2;

		PART.A.lista[PART.PL.pl[a][b].nrP].zmien_pole(PART.PL.pl[c][d].X(), //przeniesienie pionka
				PART.PL.pl[c][d].Y());
		PART.PL.pl[c][d].dodajP(PART.PL.pl[a][b].P);
		PART.PL.pl[a][b].usunP(); //usuniecie pionka z aktualnej pozycji
		PART.PL.pl[c][d].nrP = PART.PL.pl[a][b].nrP;
		PART.PL.pl[a][b].nrP = -1;
		PART.bezBicia++; // zwiekszenie ilosci ruchow bez bicia

		// okreslenie po jakiej przekatnej odbywa sie ruch
		t = ((a > c && b > d) || (a < c && b < d)) ? 1 : 0;
		x1 = (a > c) ? a : c;
		x2 = (a > c) ? c : a;
		y1 = t ? (b > d) ? b : d:(b > d) ? d : b;
		y2 = t ? (b > d) ? d : b:(b > d) ? b : d;

		while ((x1 > x2 + 1 && y1 > y2 + 1 && t)
				|| (x1 > x2 + 1 && y2 > y1 + 1 && !t))
		{
			t ? (x1-- && y1--) : (x1-- && y1++); // iterowanie wspolrzednych w zaleznosci od przekatnej
			if (PART.PL.pl[x1][y1].nrP != -1) // jesli znajduje sie na drodze pionek/damka
			{
				PART.B.ilosc--;
				PART.PL.pl[x1][y1].usunP(); //usuwa pionka/damke z planszy
				PART.B.lista[PART.PL.pl[x1][y1].nrP].zmien_pole(SIZEA, SIZEB);
				PART.PL.pl[x1][y1].nrP = -1;
				PART.bezBicia = 0;
			}
		}
	}
	PART.ruchyA(); //aktualizuje sytuacje na planszy
	PART.ruchyADamka();
	PART.ruchyB();
	PART.ruchyBDamka();
	PART.A.liczbaRuchow();
	PART.B.liczbaRuchow();
	cout << endl << "PO ZIELONYCH!!!!!!!!!!!!!" << endl;
	for (int h = 0; h < 8; ++h)
	{
		for (int g = 0; g < 8; ++g)
			cout << PART.PL.pl[g][h].P << "\t";
		cout << endl;
	}
	cout << endl;

	delete korzen;
}
