#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "wektory.hh"
#include "macierz.hh"
#include "uklad.hh"
using namespace std;


//wczytywany jest do pamieci uklad rownan
void Uklad_rownan::zapisz ()
{
cin >> _wartosci >> _wyrazy;
_rozwiazanie = _wyrazy;
_robocza = _wartosci;
}


//przygotowuje wiersz pod metode gaussa
bool Uklad_rownan::nie_zero (unsigned int pozycja)
{
unsigned int i=0;
while(_robocza[pozycja].sprawdz_zero(pozycja) && i<4)
 {
  _robocza[pozycja] = _robocza[pozycja] + _robocza[i];
  _rozwiazanie[pozycja] = _rozwiazanie[pozycja] + _rozwiazanie[i++];
 }
return _robocza[pozycja].sprawdz_zero(pozycja);
}


//konkretne rownanie wymnazane jest tak, aby na odpowiednim miejscu znalazla sie 1
void Uklad_rownan::jedynka (unsigned int pozycja)
{
_rozwiazanie[pozycja] = _rozwiazanie[pozycja] * _robocza[pozycja].jedynka(pozycja);
}


//poprzez wskazana liczbe calkowita wyzerowana jest odpowiednia kolumna
void Uklad_rownan::do_zera (unsigned int pozycja)
{
for ( unsigned int i=0 ; i<4 ; ++i ) 
 {
  if (i!=pozycja)
  {
   _rozwiazanie[i]=_rozwiazanie[i]-_rozwiazanie[pozycja]*_robocza[i][pozycja];
   _robocza[i]=_robocza[i]-_robocza[pozycja]*_robocza[i][pozycja];
  }
 }
}


//rozwiazywany jest uklad rownan poprzez wykorzystanie wczesniejszych funkcji
void Uklad_rownan::rozwiaz ()
{
if ( nie_zero(0) ){ cout << "uklad nie posiada dokladnie jednego rozwiazania." << endl; exit(0); }
jedynka(0);
do_zera(0);

if ( nie_zero(1) ){ cout << "uklad nie posiada dokladnie jednego rozwiazania." << endl; exit(0); }
jedynka(1);
do_zera(1);

if ( nie_zero(2) ){ cout << "uklad nie posiada dokladnie jednego rozwiazania." << endl; exit(0); }
jedynka(2);
do_zera(2);

if ( nie_zero(3) ){ cout << "uklad nie posiada dokladnie jednego rozwiazania." << endl; exit(0); }
jedynka(3);
do_zera(3);

cout << "macierz:" << endl << _wartosci;
cout << "wektor wyrazow wolnych:" << endl << _wyrazy << endl;
cout << "rozwiazanie: " << _rozwiazanie << endl;
}


//liczony jest blad wynikajacy z bledow obliczen
void Uklad_rownan::wylicz_blad ()
{
cout << "blad obliczen: " << (_wartosci*_rozwiazanie-_wyrazy).dlugosc() << endl;
}
