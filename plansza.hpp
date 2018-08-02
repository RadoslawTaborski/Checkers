#ifndef PLANSZA_HPP
#define PLANSZA_HPP

#include"pole.hpp"
#include"pionek.hpp"

/*****************************************************************
 * Klasa plansza okreœla obiekt planszy do gry w warcaby o rozmiarze
 *  8x8
 *****************************************************************/
class plansza
{
    public:
        pole pl[8][8]; // przechowuje obiekty klasy pole
        bool klikniecie(pole &tmp, int X, int Y, int &a, int &b); //sprawdza na ktore pole odbylo sie klikniecie
        bool zaznacz(int index,pole &tmp, int X, int Y,int &a, int &b); //sprawdza czy na kliknietym polu znajduje sie pionek
        pole& Pole(int a, int b); // zwraca element pl o wspolrzednych a,b
        plansza();
        virtual ~plansza();

};

#endif // PLANSZA_HPP
