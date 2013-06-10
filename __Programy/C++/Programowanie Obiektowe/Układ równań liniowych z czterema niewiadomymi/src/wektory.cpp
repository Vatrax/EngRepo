#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "wektory.hh"
using namespace std;




double& Wektor::operator [] (unsigned int pozycja)
{
return _dane[pozycja];
}


//kazda wspolrzedna przekazana do funkcji mnozona jest przez skalar i wartosc jest zwracana do wektora wynik
Wektor Wektor::operator * (double liczba)
{
Wektor wynik;
wynik[0] = _dane[0] * liczba;
wynik[1] = _dane[1] * liczba;
wynik[2] = _dane[2] * liczba;
wynik[3] = _dane[3] * liczba;
return wynik;
}


//kazda wspolrzedna przekazana do funkcji dodawana jest do drugiego wektora i wartosc jest zwracana do wektora wynik
Wektor Wektor::operator + (Wektor wektor)
{
Wektor wynik;
wynik[0] = _dane[0] + wektor[0];
wynik[1] = _dane[1] + wektor[1];
wynik[2] = _dane[2] + wektor[2];
wynik[3] = _dane[3] + wektor[3];
return wynik;
}


//kazda wspolrzedna przekazana do funkcji odejmowana jest od drugiego wektora i wartosc jest zwracana do wektora wynik
Wektor Wektor::operator - (Wektor wektor)
{
Wektor wynik;
wynik[0] = _dane[0] - wektor[0];
wynik[1] = _dane[1] - wektor[1];
wynik[2] = _dane[2] - wektor[2];
wynik[3] = _dane[3] - wektor[3];
return wynik;
}



double Wektor::dlugosc ()
{
return sqrt(_dane[0]*_dane[0] + _dane[1]*_dane[1] + _dane[2]*_dane[2] + _dane[3]*_dane[3]);
}



bool Wektor::sprawdz_zero(unsigned int pozycja)
{
return _dane[pozycja]==0;
}



double Wektor::jedynka(unsigned int pozycja)
{
double liczba = 1/_dane[pozycja];
_dane[0] = _dane[0] * liczba;
_dane[1] = _dane[1] * liczba;
_dane[2] = _dane[2] * liczba;
_dane[3] = _dane[3] * liczba;
return liczba;
}


/*Wyswietlany jest wektor.Funkcja wypisuje cztery wartosci*/
ostream& operator << (ostream& StrmWyj, Wektor wektor)
{
StrmWyj << "(";
StrmWyj << wektor[0] << ",";
StrmWyj << wektor[1] << ",";
StrmWyj << wektor[2] << ",";
StrmWyj << wektor[3];
StrmWyj << ")";
return StrmWyj;
}


/*Wczytywany jest wektor.Sprawdzana jest poprawnosc wektora*/
istream& operator >> (istream& StrmWej, Wektor& wektor)
{
char znak;
StrmWej >> skipws;

StrmWej >> znak;
if ( znak != '(' ) { cerr << "blad: zly wektor." << endl; exit(1); }

StrmWej >> wektor[0];
if (StrmWej.fail()) { cerr << "blad: zla wspolrzedna." << endl; exit(1); }

StrmWej >> znak;
if ( znak != ',' ) { cerr << "blad: zly wektor." << endl; exit(1); }

StrmWej >> wektor[1];
if (StrmWej.fail()) { cerr << "blad: zla wspolrzedna." << endl; exit(1); }

StrmWej >> znak;
if ( znak != ',' ) { cerr << "blad: zly wektor." << endl; exit(1); }

StrmWej >> wektor[2];
if (StrmWej.fail()) { cerr << "blad: zla wspolrzedna." << endl; exit(1); }

StrmWej >> znak;
if ( znak != ',' ) { cerr << "blad: zly wektor." << endl; exit(1); }

StrmWej >> wektor[3];
if (StrmWej.fail()) { cerr << "blad: zla wspolrzedna." << endl; exit(1); }

StrmWej >> znak;
if ( znak != ')' ) { cerr << "blad: zly wektor."; exit(1); }

return StrmWej;
}

