#include "zawodnik.hpp"
#include <fstream>
#include <iomanip>
#include "grafika.hpp"

using namespace std;

/*****************************************************************
 * Domyslnie zawodnik ma 12 pionkow
 * 0 ruchow do wykonania
 * oraz indeks 0
 *****************************************************************/
zawodnik::zawodnik()
{
    ilosc=12;
    ile_ruchow=0;
    index=0;
}

/*****************************************************************
 * destruktor usuwa elementy z listy pionkow
 *****************************************************************/
zawodnik::~zawodnik()
{
    lista.clear();
}

/*****************************************************************
 * Funkcja tworzy pionki danego zawodnika
 * pole- poczatkowe wspolrzedne pionka
 *****************************************************************/
void zawodnik::utworz(pole &A)
{
	char txt1[]={"img/p_pionek.bmp"};
	char txt2[]={"img/z_pionek.bmp"};

    if(index==1) // jesli nalezy do gracza pierwszego
        lista.push_back(pionek(A.X(),A.Y(),txt1,index));

    if(index==2) // jesli nalezy do gracza drugiego
        lista.push_back(pionek(A.X(),A.Y(),txt2,index));
}

/*****************************************************************
 * Funkcja sprawdza czy dany gracz ma bicie do wykonania
 *****************************************************************/
bool zawodnik::jestBicie()
{
    for(unsigned int i=0; i<lista.size(); ++i)
        if(lista[i].czyBicie() && lista[i].x!=SIZEA)
            return true;
    return false;
}

/*****************************************************************
 * Funkcja sprawdza czy istnieja jakies ruchy zawodnika
 *****************************************************************/
bool zawodnik::brakRuchow()
{
    for(unsigned int i=0; i<lista.size(); ++i)
        if(lista[i].czyRuch())
            return false;
    return true;
}

/*****************************************************************
 * Funkcja zwraca liczbe mozliwych ruchow do wykonania przez
 * zawodnika
 *****************************************************************/
void zawodnik::liczbaRuchow()
{
    ile_ruchow=0;
    for(unsigned int i=0; i<lista.size(); ++i)
    {
        if(jestBicie())
        ile_ruchow+=lista[i].ileRuchow(1);
        else
        ile_ruchow+=lista[i].ileRuchow(0);
    }
}

/*****************************************************************
 * Funkcja wyswietla wszystkie mozliwe ruchy do wykonania przez
 * zawodnika
 *****************************************************************/
void zawodnik::wyswietl_ruchy()
{
    for(unsigned int i=0; i<lista.size();++i)
        for(unsigned int j=0; j<lista[i].wektor.size();++j)
            cout<<lista[i].wektor[j].x1<<" "<<lista[i].wektor[j].y1<<" "<<lista[i].wektor[j].x2<<" "<<lista[i].wektor[j].y2<<endl;
}

