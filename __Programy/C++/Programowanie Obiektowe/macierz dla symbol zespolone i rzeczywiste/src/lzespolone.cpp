#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "lzespolone.hh"
using namespace std;

// przeciazenie operatora =
LZespolona& LZespolona::operator = ( double liczba )
{re = liczba; im=0; return *this; }

bool LZespolona::operator == ( double liczba )
{ return re==liczba; }

// przeciazenie operatora +
LZespolona LZespolona::operator + ( LZespolona liczba )
{
  liczba.re += re;
  liczba.im += im;
  return liczba;
}

// przeciazenie operatora -
LZespolona LZespolona::operator - ( LZespolona liczba )
{
  liczba.re = re - liczba.re;
  liczba.im = im - liczba.im;
  return liczba;
}

// przeciazenie operatora *
LZespolona LZespolona::operator * ( LZespolona liczba )
{
  LZespolona wynik;
  wynik.re = liczba.re*re - liczba.im*im;
  wynik.im = liczba.im*re + liczba.re*im;
  return wynik;
}

// przeciazenie operatora /
LZespolona operator / ( double liczba, LZespolona dzielnik )
{
  LZespolona wynik;
  double mianownik = dzielnik.re*dzielnik.re + dzielnik.im*dzielnik.im;
  wynik.re = ( liczba * dzielnik.re ) /mianownik;
  wynik.im = ( (-1) * liczba * dzielnik.im ) /mianownik;
  return wynik;
}

// funkcja wyswietaljaca czesc rzeczywista liczyby rzeczywistej
void WysRE ( ostream & StrmWyj, LZespolona liczba )
{ if ( liczba.re!=0 ) StrmWyj << liczba.re; }

// funkcja wyswietaljaca czesc urojona liczyby rzeczywistej
void WysIM ( ostream & StrmWyj, LZespolona liczba )
{
  if ( liczba.re!=0 && liczba.im>0 ) StrmWyj << '+';
  if      ( liczba.im==1  ) StrmWyj << "i";
  else if ( liczba.im==-1 ) StrmWyj << "-i";
  else if ( liczba.im!=0  ) StrmWyj << liczba.im << 'i';
}

// przeciazenie operatora Wyjscia (<<)
ostream & operator << ( ostream & StrmWyj, LZespolona liczba )
{
  WysRE ( StrmWyj, liczba );
  WysIM ( StrmWyj, liczba );
  if ( liczba.re==0 && liczba.im==0 ) StrmWyj << 0;
  return StrmWyj;
}

// przeciazenie operatora Wejscia (>>)
istream & operator >> ( istream &  StrmWej, LZespolona & liczba )
{
  char znak;
  cin >> liczba.re >> liczba.im >> znak;
  if ( StrmWej.fail() )
    { cerr << "Blad! Zly zapis liczby zespolonej." << endl; exit(1); }
  if ( znak !='i')
    { cerr << "Blad! Brak czesci urojonej." << endl; exit(1);}
}
