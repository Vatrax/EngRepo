#ifndef MODUL_HH
#define MODUL_HH

#include <cctype>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <ostream> 
#include <cstdlib>
#include <cstdio> 

const int rozm_tab=75;		//stala definiujaca rozmiar stosu
void PowitanieOrazInformacje();
/***************************************************************************************/
struct wektor				//struktura wektor
{
  int x,y,z;
  wektor operator + (wektor w2);
  wektor operator - (wektor w2);
  wektor operator * (wektor w2);
};
/***************************************************************************************/
struct Stos		       	    //struktura Stos
{  
  Stos(){_ilosc=0;}           //konstruktor stosu
  wektor _tab[rozm_tab];      //deklaracja stosu
  int _ilosc;	         
  bool poloz(wektor w);
  wektor sciagnij();
  bool podgladnij();
  void wypisz();
};
/***************************************************************************************/
struct Kalk                    //struktura Kalkulator
{
  Stos _st_arg;			//delkaracja obiektu typu Stos
  char oper;
  bool zapamietaj_arg();
  bool dzialanie();
  void wypisz();
  void zmien();
  void usun();
  void duplikuj();
  bool CzyLiczbaDoWczytania();
  bool czywektor();
};
#endif
