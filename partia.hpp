#ifndef PARTIA_HPP
#define PARTIA_HPP

#include "plansza.hpp"
#include "zawodnik.hpp"

/**************************************************************
 * Klasa Partia tworzy wszystko to co potrzebne do gry
 * sklada sie z zawodnika A i B oraz planszy. Zlicza ruchy bez
 * bicia, aktualizuje aktualna sytuacje na planszy, poprzez
 * znajdowanie nowych ruchow
 *************************************************************/
class partia
{
    public:
        int bezBicia;
        plansza PL;
        zawodnik A;
        zawodnik B;
        partia();
        ~partia();
        void utworz(); // tworzy poczatkowe ustawienei gry
        void ruchyA(); // aktualizuje mozliwe ruchy pionkami gracza A
        void ruchyADamka(); // aktualizuje mozliwe ruchy damka gracza A
        void ruchyB(); // aktualizuje mozliwe ruchy pionkami gracza B
        void ruchyBDamka(); // aktualizuje mozliwe ruchy damka gracza A
        void znajdzBiciaA(); // znajduje ruchy bijace do wykonania przez gracza A
        void znajdzBiciaB(); // znajduje ruchy bijace do wykonania przez gracza B
        int Koniec(); // rozpoznaje czy gra dobiegla konca
};

#endif // PARTIA_HPP
