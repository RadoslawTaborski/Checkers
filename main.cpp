#include <allegro.h>
#include <iostream>
#include "partia.hpp"
#include "komputer.hpp"
#include <math.h>
#include "grafika.hpp"

using namespace std;

BITMAP * kursor;

int mx = 0, my = 0, mb = 0; //polozenie kursora myszy, mb- odpowiada kliknieciu w lewy klawisz

// przypisanie polozenia myszy
void myszka()
{
	if (mx != mouse_x || my != mouse_y || mb != mouse_b)
	{
		mx = mouse_x;
		my = mouse_y;
		mb = mouse_b;
	}
}

// funkcja wczytuje kursor myszy
void laduj_kursor()
{
	kursor = load_bitmap("img/kursor.bmp", NULL);
	if (!kursor) // gdy plik nie zostal wczytany
	{
		set_gfx_mode( GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Nie moge zaladowac grafiki kursor.bmp");
		allegro_exit();
	}
}

/*************************************************************
 * funkcja wczytuje grafiki pionkow do gry
 * part- aktualny stan partii
 * Z1,Z2 - wskazniki na tablice bitmap
 * zwraca false gdy ktorejs bitmapy nie udalo sie otworzyc
 ************************************************************/
bool utworz_pola(partia &part, BITMAP **z1, BITMAP **z2)
{
	for (int i = 0; i < 12; ++i) // dla kazdego pionka
	{
		z1[i] = load_bmp(part.A.lista[i].grafika, default_palette); //wczytanie bitmapy
		if (!z1[i]) // jesli pliku nie udalo sie otworzyc
		{
			set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
			allegro_message("Nie moge zaladowac grafiki p_pionek.bmp");
			allegro_exit();
			return false;
		}
		z2[i] = load_bmp(part.B.lista[i].grafika, default_palette); //wczytanie bitmapy
		if (!z2[i]) // jesli pliku nie udalo sie otworzyc
		{
			set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
			allegro_message("Nie moge zaladowac grafiki pionek.bmp!");
			allegro_exit();
			return false;
		}
	}
	return true;
}

/*************************************************************
 * funkcja ustawia w trybie graficznym pionki na planszy
 * part- aktualny stan partii
 * Z1,Z2 - wskazniki na tablice bitmap
 * bufor - przechowuje tlo (plansze do gry)
 ************************************************************/
void wyswietl_grafike(partia &part, BITMAP **z1, BITMAP **z2, BITMAP *bufor)
{
	for (int i = 0; i < 12; ++i)
		masked_blit(z1[i], bufor, 0, 0, part.A.lista[i].x, part.A.lista[i].y,
				SIZE_PX, SIZE_PY);

	for (int i = 0; i < 12; ++i)
		masked_blit(z2[i], bufor, 0, 0, part.B.lista[i].x, part.B.lista[i].y,
				SIZE_PX, SIZE_PY);
}

/**********************************************************************************************************
 |**********************************************************************************************************/

int main()
{
	BITMAP *z1[12]; // wskaznik na tablice bitmap pionkow gracza pierwszego
	BITMAP *z2[12]; // wskaznik na tablice bitmap pionkow gracza pierwszego
	komputer A;
	int index = 1; // indeks gracza od ktorego zaczyna sie gra
	partia PART; // Partia ktora bedzie rozgrywana
	PART.utworz(); // utworzenie sytuacji poczatkowej
	pole tmp, tmp2; // zmienne pomocnicze do typu pole
	pionek tmp3; // zmienne pomocnicza do typu pionek
	bool esc = false; // wcisniecie klawisza Esc konczacego program

	allegro_init(); // zainicjalizowanie trybu graficznego
	install_keyboard(); // dodanie obslugi klawiatury
	set_color_depth(16); // glebia kolorow w trybie graficznym to 16

	set_gfx_mode(GFX_AUTODETECT_WINDOWED, SIZEA, SIZEB, 0, 0); // utworzenie okna

	laduj_kursor(); // wczytanie kursora
	install_mouse(); // dodanie obslugi myszki
	show_mouse(screen);
	set_mouse_sprite(kursor); // ustawienie wczytanego kursora jako tego wyswietlanego
	unscare_mouse();

	// deklarujemy wzkazniki do obrazkow
	if (!utworz_pola(PART, z1, z2))
		return 0; // gdy nie udalo sie wczytac poczatkowego ustawienia planszy z powodu braku jakiegos pliku graficznego

	BITMAP *bufor = NULL;
	BITMAP *znacznik = NULL;
	znacznik = load_bmp("img/zaznacz.bmp", default_palette); // wczytranie grafiki ktora podswietla wybrany pionek
	int znacznik_x, znacznik_y; // wspolzedne polozenia grafiki zaznacz

	PART.ruchyA(); // znalezienie mozliwych ruchow obu graczy
	PART.ruchyB();

	while (!esc && !PART.Koniec()) // glowna petla
	{
		if (!utworz_pola(PART, z1, z2)) // odswierzenie sytuacji na planszy
			return 0;
		znacznik_x = SIZEA;
		znacznik_y = 0;

		bufor = load_bmp("img/plansza.bmp", default_palette); //wczytanie t³a

		wyswietl_grafike(PART, z1, z2, bufor); // aktualizacja grafiki
		masked_blit(bufor, screen, 0, 0, 0, 0, SIZEA, SIZEB);
		if (index == 2) //ruch gracza
		{
			while (mouse_b != 1 && !esc) //dopoki nie pojawi sie klikniecie myszki lub Esc ktory konczy gre
			{
				myszka();
				if (key[KEY_ESC])
					esc = true;
			}
			rest(180);
			int a, b, c, d; //wspolrzedne ruchu pionka
			bool zaznaczone = false; //nie jest zaznaczony zaden pionek
			if (PART.PL.zaznacz(index, tmp2, mx, my, a, b))
			{
				znacznik_x = tmp2.X(); //zaznaczono pionek, ustawiono wspolrzedne znacznika
				znacznik_y = tmp2.Y();
				zaznaczone = true;
				masked_blit(znacznik, bufor, 0, 0, znacznik_x, znacznik_y,
						znacznik->w, znacznik->h); // maskujemy tlo
				masked_blit(bufor, screen, 0, 0, 0, 0, SIZEA, SIZEB); //wyswietlono znacznik we wlasciwym miejscu
			}
			while (zaznaczone && !esc) //dopoki ruch gracza sie nie skonczy
			{
				while (mouse_b != 1 && !esc) //oczekiwanie na klikniecie myszka
				{
					myszka();
					if (key[KEY_ESC])
						esc = true;
				}
				if (PART.PL.klikniecie(tmp, mx, my, c, d)) // sprawdzenie czy kliknieto w dozwolonie miejsce
				{
					if (tmp.czyPionek(index))
						break;

					if (index == 2)
					{
						if (PART.B.jestBicie()) //jeœli jest bicie
						{
							if (PART.B.lista[PART.PL.pl[a][b].nrP].ruchy[c][d]
									== 4) //to bicia s¹ jedynymi mo¿liwymi ruchami
							{
								int x1, x2, y1, y2, t;
								PART.B.lista[PART.PL.pl[a][b].nrP].zmien_pole(
										tmp.X(), tmp.Y()); //zmiana polozenia pionka
								PART.PL.pl[c][d].dodajP(PART.PL.pl[a][b].P); //dodanie pionka do nowego pola
								PART.PL.pl[a][b].usunP(); //usuniecie pionka ze starego pola
								PART.PL.pl[c][d].nrP = PART.PL.pl[a][b].nrP;
								PART.PL.pl[a][b].nrP = -1;
								//x1, x2 pomocnicze wspolrzednie do wykonania bicia
								t = ((a > c && b > d) || (a < c && b < d)) ?
										1 : 0;
								x1 = (a > c) ? a : c;
								x2 = (a > c) ? c : a;
								y1 = t ? (b > d) ? b : d:(b > d) ? d : b;
								y2 = t ? (b > d) ? d : b:(b > d) ? b : d;
								while ((x1 > x2 + 1 && y1 > y2 + 1 && t)
										|| (x1 > x2 + 1 && y2 > y1 + 1 && !t))
								{
									t ? (x1-- && y1--) : (x1-- && y1++); //iteruje wspolrzedne w zaleznosci od przekatnej
									if (PART.PL.pl[x1][y1].nrP != -1) // usuwa napotkany pionek
									{
										PART.A.ilosc--;
										PART.PL.pl[x1][y1].usunP();
										PART.A.lista[PART.PL.pl[x1][y1].nrP].zmien_pole(
												SIZEA, SIZEB);
										PART.PL.pl[x1][y1].nrP = -1;
									}
								}
								PART.bezBicia = 0; //wlasnie bylo bicie
								PART.ruchyA(); //aktualizacja mozliwych ruchow
								PART.ruchyADamka();
								PART.ruchyB();
								PART.ruchyBDamka();

								if (PART.B.lista[PART.PL.pl[c][d].nrP].czyBicie()) // jesli pionek ktorym wykonano bicie dalej moze bic
									index = 2; //to powtorzenie czynnosci
								else
									index = 1;
							}
							else//jesli chciano wykonac ruch bez bicia gdy taki istnieje
								allegro_message("Masz bicie!!");

						}
						else //wykonanie zwyklego ruchu do przodu
						{
							if (PART.B.lista[PART.PL.pl[a][b].nrP].ruchy[c][d]
									== 2)
							{
								PART.B.lista[PART.PL.pl[a][b].nrP].zmien_pole(
										tmp.X(), tmp.Y()); // przeniesienie pionka we wlasciwe miejsce
								PART.PL.pl[c][d].dodajP(PART.PL.pl[a][b].P);
								PART.PL.pl[a][b].usunP();
								PART.PL.pl[c][d].nrP = PART.PL.pl[a][b].nrP;
								PART.PL.pl[a][b].nrP = -1;
								PART.bezBicia++; // zwiekszenie liczby ruchow bez bicia
								PART.ruchyA(); //aktualizacja mozliwych do wykonania ruchow
								PART.ruchyADamka();
								PART.ruchyB();
								PART.ruchyBDamka();
								index = 1; // zmiana indeksu na indeks komputera
							}
						}
						cout << "PO BIAŁYCH!!!!!!!!!!!!!" << endl; // wyswietlenie w terminalu sytuacji
						for (int h = 0; h < 8; ++h)
						{
							for (int g = 0; g < 8; ++g)
								cout << PART.PL.pl[g][h].P << "\t";
							cout << endl;
						}
						cout << endl;
					}
					zaznaczone = false; // odznaczenie elementu
				}
			}
		}
		destroy_bitmap(bufor); //zniszczenie bitmap
		for (int i = 0; i < 12; ++i)
			destroy_bitmap(z1[i]);
		for (int i = 0; i < 12; ++i)
			destroy_bitmap(z2[i]);

		bufor = load_bmp("img/plansza.bmp", default_palette); //wczytanie nowych bitmap

		if (!utworz_pola(PART, z1, z2))
			return 0;
		wyswietl_grafike(PART, z1, z2, bufor); //wyswietlenie aktualnej sytuacji
		masked_blit(bufor, screen, 0, 0, 0, 0, SIZEA, SIZEB);
		if (index == 1 && !PART.Koniec()) // ruch komputera
		{
                A.wykonaj_ruch(PART);
                index = 2;
		}
		destroy_bitmap(bufor); //zniszczenie nieaktualnych bitmap
		for (int i = 0; i < 12; ++i)
			destroy_bitmap(z1[i]);
		for (int i = 0; i < 12; ++i)
			destroy_bitmap(z2[i]);
	}

	bufor = load_bmp("img/plansza.bmp", default_palette); //wczytanie nowej sytuacji

	if (!utworz_pola(PART, z1, z2))
		return 0;
	wyswietl_grafike(PART, z1, z2, bufor);
	masked_blit(bufor, screen, 0, 0, 0, 0, SIZEA, SIZEB);

	/* zakonczenie gry
	 * wyswietlenie odpowiedniej grafiki od stanu zakonczenia gry
	 */
	znacznik = load_bmp("img/koniec.bmp", default_palette);
	if (PART.Koniec() == 1)
		znacznik = load_bmp("img/zwyciestwo.bmp", default_palette);
	if (PART.Koniec() == 2)
		znacznik = load_bmp("img/porazka.bmp", default_palette);
	if (PART.Koniec() == 3)
		znacznik = load_bmp("img/remis.bmp", default_palette);
	masked_blit(znacznik, screen, 0, 0, 0, 0, SIZEA, SIZEB);
	while (!key[KEY_ESC]); // oczekiwanie na zamkniecie gry poprzez klawisz Esc

	for (int i = 0; i < 12; ++i) //zniszczenie bitmap
		destroy_bitmap(z1[i]);
	for (int i = 0; i < 12; ++i)
		destroy_bitmap(z2[i]);
	destroy_bitmap(bufor);
	destroy_bitmap(znacznik);
	destroy_bitmap(kursor);
	allegro_exit(); // zamkniecie trybu graficznego
	return 0;
}
END_OF_MAIN()
;
