#ifndef UKLAD_HH
#define UKLAD_HH
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include "bloki.hh"
#include "lacze_do_gnuplota.hh"
#define PLIK_WEJSCIA   "dat/sinus.syg"
#define PLIK_WYJSCIA   "dat/wyjscie.syg"

using namespace std;


class Uklad
{


private:
    PzG::LaczeDoGNUPlota  Lacze;
    //dane do ustawienia wykresu gnuplota
    float sygnal_max,sygnal_min;
    float czas_max, czas_min;
    string plik_wyjscia,plik_wejscia;

    //listy przechowujace kluczowe dane
    list<Blok*> bloki;
    list<float> wejscie;
    list<float> wyjscie;


public:
    //konstruktor
    Uklad();

    //obsluga ilustrowania wyjscia ukladu
    void DopasujWykres( float SygWyj, float czas );
    void ZmienWyswietlanie();
    void WyswietlWykres();

    // wykonanie obliczen
    void DodajBlok(char ID,int wartosc);
    float Rozpocznij(float SygWej);

    // pobieranie i zapis danych
    void WczytajWejscie();
    void ZmienWejscie( string wejscie );
    void ZmienWyjscie( string wyjscie );

};



#endif
