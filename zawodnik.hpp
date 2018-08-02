#ifndef ZAWODNIK_HPP
#define ZAWODNIK_HPP

#include<vector>
#include"pole.hpp"
#include"pionek.hpp"

using namespace std;

/*****************************************************************
 * Klasa okresla obiekt jakim jest Zawodnik
 * posiada on liste pionkow
 * swoj indeks
 * ilosc pionkow na planszy
 * ilosc ruchow do wykonania
 *****************************************************************/
class zawodnik
{
    public:
        int ile_ruchow; //ile ruchow ma do wykonania
        int ilosc; //ilosc pionkow na planszy
        int index;
        vector<pionek> lista; //lista pionkow
        zawodnik();
        ~zawodnik();
        void utworz(pole &A); // ustawia swoje pionki na planszy
        bool jestBicie(); //sprawdza czy jest bicie
        bool brakRuchow(); //sprawdza czy sa ruchy do wykonania
        void liczbaRuchow(); // aktualizuje zmienna ile_ruchow
        void wyswietl_ruchy(); // wyswietla wszystkie ruchy mozliwe do wykonania
};

#endif // ZAWODNIK_HPP
