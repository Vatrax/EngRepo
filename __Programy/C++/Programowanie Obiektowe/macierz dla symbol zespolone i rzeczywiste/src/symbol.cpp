#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include "symbol.hh"

using namespace std;

Symbol TabliczkaMnoz[5][5]={{e,e,e,e,e},
                            {e,d,c,a,b},
                            {e,c,d,b,a},
                            {e,a,b,c,d},
                            {e,b,a,d,c}};

Symbol TabliczkaDodaj[5][5]={{e,a,b,c,d},
                             {a,d,e,b,c},
                             {b,e,c,d,a},
                             {c,b,d,a,e},
                             {d,c,a,e,b}};


/* Przeciazenia operatorow*/

Symbol operator - (Symbol x, Symbol y)
    {
    return TabliczkaDodaj[x][5-y];
    }
Symbol operator + (Symbol x, Symbol y)
    {
    return TabliczkaDodaj[x][y];
    }


Symbol operator * (Symbol x, Symbol y)
    {   
    return TabliczkaMnoz[x][y];
    }
Symbol operator / (Symbol x, Symbol y)
    {
    if ( y == e)
        {
        cout << "nie wolno dzielic przez e" << endl;
        exit(1);
        }                                                         // d*d=c
    else if( y == b )                                             // c*c=c         
        y = a;                                                    // b*a=c
    else if( y == a )
        y = b;
    return TabliczkaMnoz[x][y];
    }
ostream & operator << (ostream &  StrmWyj, Symbol SymDoWys)        //przeciazenie operatora <<
{
 Symbol Tablica[5] = {e,a,b,c,d};
 char   Wyniki[5]  = {'e','a','b','c','d'};
 return StrmWyj << Wyniki[SymDoWys];
}
istream & operator >> (istream &  StrmWej, Symbol &  WczytSym)    //przeciazenie operatora >>
{
  Symbol TabSymboli[] = {a,b,c,d,e};
  char   ZnakSymbolu;

  StrmWej >> ZnakSymbolu;
  if (ZnakSymbolu < 'a' || 'e' < ZnakSymbolu)
  {
    cerr << "Blad! Wprowadzony znak nie odpowiada zadnemu symbolowi."
         << endl;
    exit(1);
  }
  WczytSym =  TabSymboli[ZnakSymbolu-'a'];
  return StrmWej;
}

