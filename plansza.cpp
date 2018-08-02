#include "plansza.hpp"
#include <iostream>
#include "grafika.hpp"

using namespace std;

/*****************************************************************
 * Konstruktor tworzy plansze do gry poprzez nadanie kolejnym polom
 * planszy wspolrzednych
 *****************************************************************/
plansza::plansza()
{
    int Xmin, Xmax, Ymin, Ymax;
    for(int i=1; i<8; i+=2)
        for(int j=0; j<8; j+=2)
        {
            Xmin=PA+SIZE_PX*i;
            Xmax=PB+SIZE_PX*i;
            Ymin=P8+SIZE_PY*j;
            Ymax=P7+SIZE_PY*j;
            pl[i][j].utworz(Xmin,Xmax,Ymin,Ymax);
        }

    for(int i=0; i<8; i+=2)
        for(int j=1; j<8; j+=2)
        {
            Xmin=PA+SIZE_PX*i;
            Xmax=PB+SIZE_PX*i;
            Ymin=P8+SIZE_PY*j;
            Ymax=P7+SIZE_PY*j;
            pl[i][j].utworz(Xmin,Xmax,Ymin,Ymax);
        }
}

/*****************************************************************
 * Funkcja zwraca true jesli wykonano klikniecie na aktywne pole
 * planszy (czarne)
 *  * do zmiennej tmp zostaja przypisane wspolrzedne pola na ktore kliknieto
 *****************************************************************/
bool plansza::klikniecie(pole &tmp,int X, int Y, int &a,int &b)
{
    int z=0;
    for(int j=0; j<8;++j)
    {
        z=(!z);
        for(int i=z; i<8; i+=2)
            if(pl[i][j].klik(X,Y))
            {
                a=i;
                b=j;
                tmp=pl[i][j];
                return true;
            }
    }
            return false;
}

/*****************************************************************
 * Funkcja zwraca true jesli wykonano klikniecie na aktywne pole
 * planszy(czarne), na ktorym znajduje sie pionek zawodnika o indeksie
 * index
 * do zmiennej tmp zostaja przypisane wspolrzedne pola na ktore kliknieto
 *****************************************************************/
bool plansza::zaznacz(int index, pole &tmp, int X, int Y,int &a, int &b)
{
     for(int i=0; i<8; ++i)
        for(int j=0; j<8; ++j)
            if(pl[i][j].klik(X,Y))
            {
                if(pl[i][j].czyPionek(index))
                {
                tmp=pl[i][j];
                a=i;
                b=j;
                return true;
                }
            }
    return false;
}

/*****************************************************************
 * Funkcja zwraca pole planszy o indeksach a i b
 *****************************************************************/
pole& plansza::Pole(int a, int b)
{
    return pl[a][b];
}

plansza::~plansza()
{
    //dtor
}
