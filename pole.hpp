#ifndef POLE_HPP
#define POLE_HPP

/*****************************************************************
 * Klasa Pole tworzy obiekt jakim jest aktywne pole na planszy
 * (czarne)
 * P-informuja jakiej druzyny pionek znajduje sie na planszy
 * nrP - informuje o indeksie tego pionka
 * Xmin,Xmax,Ymin,Ymax - parametry okreslajace polozenie pola
 *****************************************************************/
class pole
{
    public:
        int P;
        int nrP;
        int Xmin;
        int Xmax;
        int Ymin;
        int Ymax;

        pole();
        bool operator ==(pole &tmp); // przyrownywanie pol
        void utworz(int Xa, int Xb, int Ya, int Yb); // tworzenie pola
        void dodajP(int pion); //dodaje pion na dane pole
        void usunP(); //usuwa pion z danego pola
        bool klik(int mx, int my); // okresla czy klikniecie myszka odbylo sie w dane pole
        bool czyPionek(int index); // okresla czy na danym polu znajduje sie pionek
        int X()
        {return Xmin;}
        int Y()
        {return Ymin;}
        ~pole();
};

#endif // POLE_HPP
