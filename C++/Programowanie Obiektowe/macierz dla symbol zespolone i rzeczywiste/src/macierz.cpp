#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "typdanych.hh"
#include "symbol.hh"
#include "lzespolone.hh"
#include "wektory.hh"
#include "macierz.hh"

using namespace std;



Wektor& Macierz::operator [] (unsigned int pozycja)
{
  return _wiersze[pozycja];
}


Wektor Macierz::operator * (Wektor wektor)
{
  Wektor wynik;

  for ( unsigned int i=0 ; i<4 ; ++i )
  {
    wynik[i] = ELEM_0;
    for ( unsigned int j=0 ; j<4 ; ++j )
    wynik[i] = wynik[i] + _wiersze[j][i] * wektor[j];
  }

  return wynik;
}


//funkcja wyswietlajaca
void Macierz::wyswietl (ostream& StrmWyj, unsigned int pozycja)
{
  StrmWyj << "| ";
  StrmWyj << setw(5) << setprecision(2);
  StrmWyj << _wiersze[pozycja][0] << ' ';
  StrmWyj << setw(5) << setprecision(2);
  StrmWyj << _wiersze[pozycja][1] << ' ';
  StrmWyj << setw(5) << setprecision(2);
  StrmWyj << _wiersze[pozycja][2] << ' ';
  StrmWyj << setw(5) << setprecision(2);
  StrmWyj << _wiersze[pozycja][3] << ' ';
  StrmWyj << "|" << endl;
}


//funkcja wczytujaca wiersz
void Macierz::zapisz (istream& StrmWej, unsigned int pozycja)
{
  char znak;
  StrmWej >> skipws;

  StrmWej >> znak;
  if ( znak != '|' )
  { cerr << "error:  zly wektor." << endl; exit(1); }

  StrmWej >> _wiersze[pozycja][0];
  if (StrmWej.fail()) { cerr << "blad:  zla wspolrzedna." << endl; exit(1); }
  StrmWej >> _wiersze[pozycja][1];
  if (StrmWej.fail()) { cerr << "blad:  zla wspolrzedna." << endl; exit(1); }
  StrmWej >> _wiersze[pozycja][2];
  if (StrmWej.fail()) { cerr << "blad:  zla wspolrzedna." << endl; exit(1); }
  StrmWej >> _wiersze[pozycja][3];
  if (StrmWej.fail()) { cerr << "blad:  zla wspolrzedna." << endl; exit(1); }

  StrmWej >> znak;
  if ( znak != '|' )
  { cerr << "blad:  zly wektor." << endl; exit(1); }
}

/*przeciazenia operatorow */
ostream& operator << (ostream& StrmWyj, Macierz macierz)
{
  macierz.wyswietl(StrmWyj, 0);
  macierz.wyswietl(StrmWyj, 1);
  macierz.wyswietl(StrmWyj, 2);
  macierz.wyswietl(StrmWyj, 3);
  return StrmWyj;
}


istream& operator >> (istream& StrmWej, Macierz& macierz )
{
  macierz.zapisz(StrmWej, 0);
  macierz.zapisz(StrmWej, 1);
  macierz.zapisz(StrmWej, 2);
  macierz.zapisz(StrmWej, 3);
  return StrmWej;
}

