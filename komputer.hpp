#ifndef CPU_HPP
#define CPU_HPP
#include "partia.hpp"
#include "zawodnik.hpp"
#include "Wezel.hpp"

#define POZIOM 7	// POZIOM REKURENCJI 3,5,7,9 wiecej nie polecam
#define PIONEK 5	//punktacja za zwykly pionek
#define DAMKA 25	//punktacja za damke
#define STREFA0 3	//bronienie przed zdobyciem damki przez przeciwnika
#define STREFA1 1	//œrodek planszy
#define STREFA2 3	//zbli¿anie sie do zdobycia damki
#define STREFA3 6   //strefa "królewska"
#define KONIEC 2000	 // WAGA ZWYCIESTWA


/***********************************************************
 * klasa komputer, dziedziczy publicznie po klasie zawodnik
 * pozwala ona na zastapienie zwyklego zawodnika
 * komputerem o wbudowanej sztucznej inteligencji
 ***********************************************************/
class komputer : public zawodnik
{
    public:
        Wezel *korzen; //korzen drzewa gry
        vector<vector<Wezel*> > drzewo; // przechowuje wszystkie przewidywane sytuacje
        komputer();
        ~komputer();
        int ocen(partia Partia); // funkcja oceniajaca stan partii
        void utworzDrzewo(int poziom, const partia &Partia, Wezel *podstawa); //tworzy drzewo przysz³ymi stanami gry
        void ocen_drzewo(); //ocenia drzewo wg regu³ MINMAX
        void wykonaj_ruch(partia &Partia); //wykonuje znaleziony ruch
        void wybor_ruchu(); //wybiera najlepszy ruch
};

#endif // CPU_HPP
