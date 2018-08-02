#include "partia.hpp"
#include <fstream>
#include <iomanip>

/**************************************************************
 * Konstruktor bezparametryczny
 * przypisuje indeksy graczom
 *************************************************************/
partia::partia()
{
	A.index = 1;
	B.index = 2;
	bezBicia = 0;
}

partia::~partia()
{
}

/**************************************************************
 * Funkcja utworz
 * dodaje pionki do planszy w poczatkowym ustawieniu
 * tzn. po trzy rzedy pionkow dla kazdego gracza
 *************************************************************/
void partia::utworz()
{
	int k = 0;
	int b = 0;
	for (int j = 0; j < 3; ++j)
	{
		b = (!b);
		for (int i = b; i < 8; i += 2)
		{
			PL.pl[i][j].nrP = k;
			A.utworz(PL.pl[i][j]);
			PL.pl[i][j].dodajP(1);
			k++;
		}
	}

	k = 0;
	for (int j = 7; j >= 5; --j)
	{
		b = (!b);
		for (int i = b; i < 8; i += 2)
		{
			PL.pl[i][j].nrP = k;
			B.utworz(PL.pl[i][j]);
			PL.pl[i][j].dodajP(2);
			k++;
		}
	}

	for (int i = 0; i < 8; i += 2)
		PL.pl[i][3].nrP = -1;
	for (int i = 1; i < 8; i += 2)
		PL.pl[i][4].nrP = -1;
}

/**************************************************************
 * Funkcja znajduje mozliwe ruchy pionkami gracza A
 *************************************************************/
void partia::ruchyA()
{
	int b = 0;

	for (int j = 0; j < 8; ++j) // poczatkowo zeruje wszystkie mozliwoscli ruchowe
	{
		b = (!b);
		for (int i = b; i < 8; i += 2)
			if (PL.pl[i][j].P == 1)
				A.lista[PL.pl[i][j].nrP].zeruj();
	}

	b = 0;
//dla kazdego pionka badane jest jego otoczenie i przypisywane jest do specjalen tablicy
	for (int j = 0; j < 8; ++j)
	{
		b = (!b);
		for (int i = b; i < 8; i += 2)
		{
			if (PL.pl[i][j].P == 1)
			{
				A.lista[PL.pl[i][j].nrP].ruchy[i][j] = 1;
				if (j + 1 < 8 && i - 1 >= 0 && PL.pl[i - 1][j + 1].P == 0) //zaznaczenie pustego pola
					A.lista[PL.pl[i][j].nrP].ruchy[i - 1][j + 1] = 2;
				if (j + 1 < 8 && i + 1 < 8 && PL.pl[i + 1][j + 1].P == 0) //zaznaczenie pustego pola
					A.lista[PL.pl[i][j].nrP].ruchy[i + 1][j + 1] = 2;
				if (j - 1 >= 0 && i + 1 < 8
						&& (PL.pl[i + 1][j - 1].P == 2
								|| PL.pl[i + 1][j - 1].P == 22)) //zaznaczenie wroga
					A.lista[PL.pl[i][j].nrP].ruchy[i + 1][j - 1] = 3;
				if (j + 1 < 8 && i + 1 < 8
						&& (PL.pl[i + 1][j + 1].P == 2
								|| PL.pl[i + 1][j + 1].P == 22)) //zaznaczenie wroga
					A.lista[PL.pl[i][j].nrP].ruchy[i + 1][j + 1] = 3;
				if (j - 1 >= 0 && i - 1 >= 0
						&& (PL.pl[i - 1][j - 1].P == 2
								|| PL.pl[i - 1][j - 1].P == 22)) //zaznaczenie wroga
					A.lista[PL.pl[i][j].nrP].ruchy[i - 1][j - 1] = 3;
				if (j + 1 < 8 && i - 1 >= 0
						&& (PL.pl[i - 1][j + 1].P == 2
								|| PL.pl[i - 1][j + 1].P == 22)) //zaznaczenie wroga
					A.lista[PL.pl[i][j].nrP].ruchy[i - 1][j + 1] = 3;
				znajdzBiciaA(); //znajduje bicia
			}
		}
	}
}

/**************************************************************
 * Funkcja znajduje mozliwe ruchy pionkami gracza B
 *************************************************************/
void partia::ruchyB()
{
	int b = 0;

	for (int j = 0; j < 8; ++j) // poczatkowo zeruje wszystkie mozliwoscli ruchowe
	{
		b = (!b);
		for (int i = b; i < 8; i += 2)
			if (PL.pl[i][j].P == 2)
				B.lista[PL.pl[i][j].nrP].zeruj();
	}
	b = 0;
	//dla kazdego pionka badane jest jego otoczenie i przypisywane jest do specjalen tablicy
	for (int j = 0; j < 8; ++j)
	{
		b = (!b);
		for (int i = b; i < 8; i += 2)
		{
			if (PL.pl[i][j].P == 2)
			{
				B.lista[PL.pl[i][j].nrP].ruchy[i][j] = 1;
				if (j - 1 >= 0 && i - 1 >= 0 && PL.pl[i - 1][j - 1].P == 0) //zaznaczenie pustego pola
					B.lista[PL.pl[i][j].nrP].ruchy[i - 1][j - 1] = 2;
				if (j - 1 >= 0 && i + 1 < 8 && PL.pl[i + 1][j - 1].P == 0) //zaznaczenie pustego pola
					B.lista[PL.pl[i][j].nrP].ruchy[i + 1][j - 1] = 2;
				if (j - 1 >= 0 && i + 1 < 8
						&& (PL.pl[i + 1][j - 1].P == 1
								|| PL.pl[i + 1][j - 1].P == 11)) //zaznaczenie wroga
					B.lista[PL.pl[i][j].nrP].ruchy[i + 1][j - 1] = 3;
				if (j + 1 < 8 && i + 1 < 8
						&& (PL.pl[i + 1][j + 1].P == 1
								|| PL.pl[i + 1][j + 1].P == 11)) //zaznaczenie wroga
					B.lista[PL.pl[i][j].nrP].ruchy[i + 1][j + 1] = 3;
				if (j - 1 >= 0 && i - 1 >= 0
						&& (PL.pl[i - 1][j - 1].P == 1
								|| PL.pl[i - 1][j - 1].P == 11)) //zaznaczenie wroga
					B.lista[PL.pl[i][j].nrP].ruchy[i - 1][j - 1] = 3;
				if (j + 1 < 8 && i - 1 >= 0
						&& (PL.pl[i - 1][j + 1].P == 1
								|| PL.pl[i - 1][j + 1].P == 11)) //zaznaczenie wroga
					B.lista[PL.pl[i][j].nrP].ruchy[i - 1][j + 1] = 3;
				znajdzBiciaB();
			}
		}
	}
}

/**************************************************************
 * Znajduje bicia do wykonania przez pionki gracza A
 *************************************************************/
void partia::znajdzBiciaA()
{
	int a = 0, b = 0;
	//przegladanie otoczenia kazdego pionka
	for (int j = 0; j < 8; ++j)
	{
		b = (!b);
		for (int i = b; i < 8; i += 2)
		{
			if (PL.pl[i][j].P == 1)
				for (int l = 0; l < 8; ++l)
				{
					a = (!a);
					for (int k = a; k < 8; k += 2)
					{
						if (A.lista[PL.pl[i][j].nrP].ruchy[k][l] == 3) //jesli wrog
						{
							if (i > k && j < l && k - 1 >= 0 && l + 1 < 8
									&& k + 1 < 8 && l - 1 >= 0)
								if (PL.pl[k - 1][l + 1].P == 0 // jesli za wrogiem znajduje sie puste miejsce
										&& A.lista[PL.pl[i][j].nrP].ruchy[k + 1][l
												- 1] == 1)
									A.lista[PL.pl[i][j].nrP].ruchy[k - 1][l + 1] =
											4; //przypisuje do odpowiedniego pola tablicy otoczenia pionka liczbe 4
							if (i < k && j < l && k - 1 >= 0 && l + 1 < 8
									&& k + 1 < 8 && l - 1 >= 0)
								if (PL.pl[k + 1][l + 1].P == 0
										&& A.lista[PL.pl[i][j].nrP].ruchy[k - 1][l
												- 1] == 1)
									A.lista[PL.pl[i][j].nrP].ruchy[k + 1][l + 1] =
											4;
							if (i > k && j > l && k - 1 >= 0 && l + 1 < 8
									&& k + 1 < 8 && l - 1 >= 0)
								if (PL.pl[k - 1][l - 1].P == 0
										&& A.lista[PL.pl[i][j].nrP].ruchy[k + 1][l
												+ 1] == 1)
									A.lista[PL.pl[i][j].nrP].ruchy[k - 1][l - 1] =
											4;
							if (i < k && j > l && k - 1 >= 0 && l + 1 < 8
									&& k + 1 < 8 && l - 1 >= 0)
								if (PL.pl[k + 1][l - 1].P == 0
										&& A.lista[PL.pl[i][j].nrP].ruchy[k - 1][l
												+ 1] == 1)
									A.lista[PL.pl[i][j].nrP].ruchy[k + 1][l - 1] =
											4;
						}
					}
				}
		}
	}
}

/**************************************************************
 * Znajduje bicia do wykonania przez pionki gracza B
 *************************************************************/
void partia::znajdzBiciaB()
{
	int a = 0, b = 0;
	//przegladanie otoczenia kazdego pionka
	for (int j = 0; j < 8; ++j)
	{
		b = (!b);
		for (int i = b; i < 8; i += 2)
		{
			if (PL.pl[i][j].P == 2)
				for (int l = 0; l < 8; ++l)
				{
					a = (!a);
					for (int k = a; k < 8; k += 2)
					{
						if (B.lista[PL.pl[i][j].nrP].ruchy[k][l] == 3) // jesli wrog
						{
							if (i > k && j < l && k - 1 >= 0 && l + 1 < 8
									&& k + 1 < 8 && l - 1 >= 0)
								if (PL.pl[k - 1][l + 1].P == 0 // jesli za wrogiem znajduje sie puste miejsce
										&& B.lista[PL.pl[i][j].nrP].ruchy[k + 1][l
												- 1] == 1)
									B.lista[PL.pl[i][j].nrP].ruchy[k - 1][l + 1] =
											4; //przypisuje do odpowiedniego pola tablicy otoczenia pionka liczbe 4
							if (i < k && j < l && k - 1 >= 0 && l + 1 < 8
									&& k + 1 < 8 && l - 1 >= 0)
								if (PL.pl[k + 1][l + 1].P == 0
										&& B.lista[PL.pl[i][j].nrP].ruchy[k - 1][l
												- 1] == 1)
									B.lista[PL.pl[i][j].nrP].ruchy[k + 1][l + 1] =
											4;
							if (i > k && j > l && k - 1 >= 0 && l + 1 < 8
									&& k + 1 < 8 && l - 1 >= 0)
								if (PL.pl[k - 1][l - 1].P == 0
										&& B.lista[PL.pl[i][j].nrP].ruchy[k + 1][l
												+ 1] == 1)
									B.lista[PL.pl[i][j].nrP].ruchy[k - 1][l - 1] =
											4;
							if (i < k && j > l && k - 1 >= 0 && l + 1 < 8
									&& k + 1 < 8 && l - 1 >= 0)
								if (PL.pl[k + 1][l - 1].P == 0
										&& B.lista[PL.pl[i][j].nrP].ruchy[k - 1][l
												+ 1] == 1)
									B.lista[PL.pl[i][j].nrP].ruchy[k + 1][l - 1] =
											4;
						}
					}
				}
		}
	}
}

/**************************************************************
 * Znajduje bicia  oraz ruchy mozliwe do wykonania przez damki
 * gracza A
 *************************************************************/
void partia::ruchyADamka()
{
	int b = 0, k, l, przeciwnik;
//zeruje poprzednie mozliwosci ruchowe damkami
	for (int j = 0; j < 8; ++j)
	{
		b = (!b);
		for (int i = b; i < 8; i += 2)
			if (PL.pl[i][j].P == 11)
				A.lista[PL.pl[i][j].nrP].zeruj();
	}

	b = 0;
	for (int j = 0; j < 8; ++j)
	{
		b = (!b);
		for (int i = b; i < 8; i += 2)
		{
			if (PL.pl[i][j].P == 11) //jesli znalezino damke badane sa mozliwe ruchy w kazda kolejna strone
			{
				A.lista[PL.pl[i][j].nrP].ruchy[i][j] = 1;
				k = i;
				l = j;
				przeciwnik = 0;
				while (k > 0 && l > 0 && PL.pl[--k][--l].P != 1
						&& PL.pl[k][l].P != 11)
					if (PL.pl[k][l].P == 0 && !przeciwnik)
						A.lista[PL.pl[i][j].nrP].ruchy[k][l] = 2;
					else if (PL.pl[k][l].P == 0 && przeciwnik)
						A.lista[PL.pl[i][j].nrP].ruchy[k][l] = 4;
					else if (PL.pl[k][l].P == 2 || PL.pl[k][l].P == 22)
					{
						przeciwnik++; // wykryto przeciwnika na drodze
						A.lista[PL.pl[i][j].nrP].ruchy[k][l] = 3;
						if (przeciwnik == 2) // jesli dwa pionki przeciwnika jeden za drugim
							break;
					}
				k = i;
				l = j;
				//analogicznie dla pozostalych kierunkow ruchu
				przeciwnik = 0;
				while (k < 7 && l < 7 && PL.pl[++k][++l].P != 1
						&& PL.pl[k][l].P != 11)
					if (PL.pl[k][l].P == 0 && !przeciwnik)
						A.lista[PL.pl[i][j].nrP].ruchy[k][l] = 2;
					else if (PL.pl[k][l].P == 0 && przeciwnik)
						A.lista[PL.pl[i][j].nrP].ruchy[k][l] = 4;
					else if (PL.pl[k][l].P == 2 || PL.pl[k][l].P == 22)
					{
						przeciwnik++;
						A.lista[PL.pl[i][j].nrP].ruchy[k][l] = 3;
						if (przeciwnik == 2)
							break;

					}
				k = i;
				l = j;
				przeciwnik = 0;
				while (k < 7 && l > 0 && PL.pl[++k][--l].P != 1
						&& PL.pl[k][l].P != 11)
					if (PL.pl[k][l].P == 0 && !przeciwnik)
						A.lista[PL.pl[i][j].nrP].ruchy[k][l] = 2;
					else if (PL.pl[k][l].P == 0 && przeciwnik)
						A.lista[PL.pl[i][j].nrP].ruchy[k][l] = 4;
					else if (PL.pl[k][l].P == 2 || PL.pl[k][l].P == 22)
					{
						przeciwnik++;
						A.lista[PL.pl[i][j].nrP].ruchy[k][l] = 3;
						if (przeciwnik == 2)
							break;
					}
				k = i;
				l = j;
				przeciwnik = 0;
				while (k > 0 && l < 7 && PL.pl[--k][++l].P != 1
						&& PL.pl[k][l].P != 11)
					if (PL.pl[k][l].P == 0 && !przeciwnik)
						A.lista[PL.pl[i][j].nrP].ruchy[k][l] = 2;
					else if (PL.pl[k][l].P == 0 && przeciwnik)
						A.lista[PL.pl[i][j].nrP].ruchy[k][l] = 4;
					else if (PL.pl[k][l].P == 2 || PL.pl[k][l].P == 22)
					{
						przeciwnik++;
						A.lista[PL.pl[i][j].nrP].ruchy[k][l] = 3;
						if (przeciwnik == 2)
							break;
					}
			}
		}
	}
}

/**************************************************************
 * Znajduje bicia  oraz ruchy mozliwe do wykonania przez damki
 * gracza A
 *************************************************************/
void partia::ruchyBDamka()
{
	int b = 0, k, l, przeciwnik;
	//zeruje poprzednie mozliwosci ruchowe damkami
	for (int j = 0; j < 8; ++j)
	{
		b = (!b);
		for (int i = b; i < 8; i += 2)
			if (PL.pl[i][j].P == 22)
				B.lista[PL.pl[i][j].nrP].zeruj();
	}

	b = 0;
	for (int j = 0; j < 8; ++j)
	{
		b = (!b);
		for (int i = b; i < 8; i += 2)
		{
			if (PL.pl[i][j].P == 22) //jesli znalezino damke badane sa mozliwe ruchy w kazda kolejna strone
			{
				B.lista[PL.pl[i][j].nrP].ruchy[i][j] = 1;
				k = i;
				l = j;
				przeciwnik = 0;
				while (k > 0 && l > 0 && PL.pl[--k][--l].P != 2
						&& PL.pl[k][l].P != 22)
					if (PL.pl[k][l].P == 0 && !przeciwnik)
						B.lista[PL.pl[i][j].nrP].ruchy[k][l] = 2;
					else if (PL.pl[k][l].P == 0 && przeciwnik)
						B.lista[PL.pl[i][j].nrP].ruchy[k][l] = 4;
					else if (PL.pl[k][l].P == 1 || PL.pl[k][l].P == 11)
					{
						przeciwnik++; // wykryto pion przeciwnika na drodze
						B.lista[PL.pl[i][j].nrP].ruchy[k][l] = 3;
						if (przeciwnik == 2) // jesli dwa pionki przeciwnika jeden za drugim
							break;
					}
				k = i;
				l = j;
				przeciwnik = 0;
				//analogicznie dla pozostalych mozliwych kierunkow ruchu
				while (k < 7 && l < 7 && PL.pl[++k][++l].P != 2
						&& PL.pl[k][l].P != 22)
					if (PL.pl[k][l].P == 0 && !przeciwnik)
						B.lista[PL.pl[i][j].nrP].ruchy[k][l] = 2;
					else if (PL.pl[k][l].P == 0 && przeciwnik)
						B.lista[PL.pl[i][j].nrP].ruchy[k][l] = 4;
					else if (PL.pl[k][l].P == 1 || PL.pl[k][l].P == 11)
					{
						przeciwnik++;
						B.lista[PL.pl[i][j].nrP].ruchy[k][l] = 3;
						if (przeciwnik == 2)
							break;

					}
				k = i;
				l = j;
				przeciwnik = 0;
				while (k < 7 && l > 0 && PL.pl[++k][--l].P != 2
						&& PL.pl[k][l].P != 22)
					if (PL.pl[k][l].P == 0 && !przeciwnik)
						B.lista[PL.pl[i][j].nrP].ruchy[k][l] = 2;
					else if (PL.pl[k][l].P == 0 && przeciwnik)
						B.lista[PL.pl[i][j].nrP].ruchy[k][l] = 4;
					else if (PL.pl[k][l].P == 1 || PL.pl[k][l].P == 11)
					{
						przeciwnik++;
						B.lista[PL.pl[i][j].nrP].ruchy[k][l] = 3;
						if (przeciwnik == 2)
							break;
					}
				k = i;
				l = j;
				przeciwnik = 0;
				while (k > 0 && l < 7 && PL.pl[--k][++l].P != 2
						&& PL.pl[k][l].P != 22)
					if (PL.pl[k][l].P == 0 && !przeciwnik)
						B.lista[PL.pl[i][j].nrP].ruchy[k][l] = 2;
					else if (PL.pl[k][l].P == 0 && przeciwnik)
						B.lista[PL.pl[i][j].nrP].ruchy[k][l] = 4;
					else if (PL.pl[k][l].P == 1 || PL.pl[k][l].P == 11)
					{
						przeciwnik++;
						B.lista[PL.pl[i][j].nrP].ruchy[k][l] = 3;
						if (przeciwnik == 2)
							break;
					}
			}
		}
	}
}

/**************************************************************
 * Funkcja rozpoznaje stan konca gry
 * mozliwe sa trzy rodzaje zakonczenia
 * zwyciestwo - zwyciestwo gracza B
 * porazka - porazka gracza B
 * remis- gdy wystapi zbyt duzo ruchow bez bicia
 *************************************************************/
int partia::Koniec()
{
	if (A.ilosc == 0 || A.brakRuchow())
		return 1;
	if (B.ilosc == 0 || B.brakRuchow())
		return 2;
	if (bezBicia == 30)
		return 3;
	return 0;
}
