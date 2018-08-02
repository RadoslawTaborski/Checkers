#ifndef PIONEK_HPP
#define PIONEK_HPP

#include "Ruch.hpp"
#include "pole.hpp"
#include <vector>
#include<iostream>

using namespace std;


/**************************************************************
 * Klasa okresla obiekt jakim jest pionek
 * poprzez zmienna damka rozdziela go na dwa rodzaj
 * pionka zwyklego i damke
 * Kazdy pionek przechowuje wspolrzedne polozenia
 * indeks gracza do ktorego nalezy
 * swoje otoczenie
 * oraz wektor ruchow ktore moze wykonac
 *************************************************************/
class pionek
{
    public:
        int x; //wspolrzedna x
        int y; //wspolrzedna y
        bool damka; //true- gdy staje sie damka
        int team; // ideks zawodnika do ktorego nalezy
        char grafika[50]; //adres grafiki
        vector<Ruch> wektor; // wektor mozliwych ruchow
        int ruchy[8][8]; // plansze ze swoim otoczeniem

        pionek();
        pionek(int a, int b, char txt[50], int t);
        ~pionek();
        void okreslGrafike(const char txt[50]);
        void dTeam(int t); //przypisuje indeks zawodnika do ktorego nalezy
        void zmien_pole(int a, int b); // zmienia wspolrzedne punktu i ewentualnie zamienia pionka w damke
        void wyswietl_ruchy(); // wyswietla mozliwe ruchy pionkiem
        void zeruj(); // zeruje otoczenie pionka, w celu pozniejszej aktualizacji
        bool czyBicie(); // sprawdza czy pionkiem mozna wykonac bicie
        bool czyRuch(); // sprawdza czy istnieje jakikolwiek ruch danym pionkiem
        int ileRuchow(int x); // sprawdza ile ruchow mozna wykonac pionkiem i dodaje ruchy do wektora
};

#endif // PIONEK_HPP
