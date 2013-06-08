/* Imie:        Wojciech
   Nazwisko:    Krzaczek
   nr indeksu:  184035 */

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

/*
  Definicja typu wyliczeniowego "Symbol" dla symboli  a, b, c, d, e.
*/
enum Symbol { e, a, b, c, d };

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
Symbol TabliczkaMnoz[5][5]={{e,e,e,e,e},
                            {e,d,c,a,b},
                            {e,c,d,b,a},
                            {e,a,b,c,d},
                            {e,b,a,d,c}};

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
istream &  operator >> (istream &  StrmWej, Symbol &  WczytSym)    //przeciazenie operatora >>
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

/* Funkcja wyswietlajaca menu */ 
void MENU()
  {
      cout << "MENU" << endl;
      cout << "2 - wykonaj operacje dwuargumentowa" << endl;
      cout << "P - wykonaj operacje z wykorzystaniem pamieci jako arg1" << endl;
      cout << "p - wykonaj operacje z wykorzystaniem pamieci jako arg2" << endl;
      cout << "z - zapamietaj wynik" << endl;
      cout << "w - wyswietl pamiec" << endl;
      cout << "? - wyswietl menu" << endl;
      cout << "k - koniec dzialania programu" << endl;
  }
//============================================================================
//.......................  Kalkulator ........................................

/*
 * Klasa modeluje kalkulator z pamiecia. Obiekty tej klasy moga
 * wykonywac operacje dodawania, odejmowania, mnozenia i dzielenia.
 * Operacje te wykonywane sa na elementach typu wyliczeniowego
 * Symbol.
 * Wynik biezacej operacji zapamietywany jest w polu "_Wynik".
 * Pole "_Pamiec" pozwala przechowac ten wynik na potrzeby
 * wykonania dalszych operacji.
 */
struct Kalkulator {
  /*
   * Konstruktor inicjalizujacy obiekt. W polach "_Wynik" i "_Pamikec"
   * zapisywany jest element neutralny wzgledem operacji dodawania.
   */
 Kalkulator() { _Wynik = _Pamiec = e; }

Symbol WykonajDzialanie( Symbol Arg1, char Oper, Symbol Arg2 )
{
  switch (Oper)
 {
    case '-': return _Wynik = Arg1 - Arg2;
    case '+': return _Wynik = Arg1 + Arg2;
    case '*': return _Wynik = Arg1 * Arg2;
    case '/': return _Wynik = Arg1 / Arg2;
    default:
      cerr << "Blad! Jako operator zostal uzyty niedozwolony znak: '"
           << Oper << "'" << endl;
      exit(1);
  }
}

   void WykonajDzialanie_i_Wyswietl(Symbol Arg1, char Oper, Symbol Arg2){
        cout << "Wykonane dzialanie: " << Arg1 << " " << Oper << " " << Arg2 << " = ";
        cout << WykonajDzialanie(Arg1, Oper, Arg2) << endl << endl;
         }

  /*
   * Powoduje zapisanie wyniku ostatniej operacji do pamieci.
   * Oznacza to, ze wartosc pola "_Wynik" zostaje przepisana
   * do pola "_Pamiec".
   */
  void ZapamietajWynik()
      {
          _Pamiec = _Wynik;
      }
  /*
   * Zwraca wartosc pola "_Pamiec".
   */
  Symbol WezPamiec()
    {
        return _Pamiec;
    }
  /*
   * Zwraca wartosc pola "_Wynik"
   */
  Symbol WezWynik()
    {
        return _Wynik;
    }
 private:

   /*
    * Przechowuje wynik ostatniej wykonanej operacji.
    */
  Symbol _Wynik;
   /*
    * Przechowuje wynik jednej z wczesniejszych operacji.
    * Sam akt zapamietania realizowany jest przez metode
    * ZapamietajWynik.
    */
  Symbol _Pamiec;
};
int main()
{
  Kalkulator     Kalk;  
  Symbol         Arg1, Arg2;
  char           Oper, menu[1]={'0'};
  
  
  MENU();
  while(menu[0]!='k')
  {
  cout << "Wybierz opcje z menu>";
  cin >> menu;
  switch (menu[0]) 
    {
         
 /* MENU
 2 - wykonaj operacje dwuargumentowa
 P - wykonaj operacje z wykorzystaniem pamieci jako arg1
 p - wykonaj operacje z wykorzystaniem pamieci jako arg2
 z - zapamietaj wynik
 w - wyswietl pamiec
 ? - wyswietl menu
 k - koniec dzialania programu*/
    case '2': {
              cout << "Wprowadz rownanie w postaci: Arg Oper Arg" << endl;
              cin >> Arg1 >> Oper >> Arg2;
              Kalk.WykonajDzialanie_i_Wyswietl(Arg1, Oper, Arg2) ;
              break;
              }
    case 'P': {
              cout << "Wprowadz rownanie w postaci: Oper Arg" << endl;
	          cin >> Oper >> Arg2;
	          Arg1 = Kalk.WezPamiec();
              Kalk.WykonajDzialanie_i_Wyswietl(Arg1, Oper, Arg2);
              break;
              }
    case 'p': {
              cout << "Wprowadz rownanie w postaci: Arg Oper" << endl;
	          cin >> Arg1 >> Oper;
	          Arg2 = Kalk.WezPamiec();
              Kalk.WykonajDzialanie_i_Wyswietl(Arg1, Oper, Arg2);
              break;
              }
    case 'z': {
              cout << "Zapamietane" << endl;
              Kalk.ZapamietajWynik();
              break;
              }
    case 'w': {
              cout << "W pamieci znajduje sie: " << Kalk.WezPamiec() << endl;
              break;
              }
    case '?': {
              MENU();
              break;
              }
    case 'k': {
              cout << "Dziekuje za skorzystanie z Kalkulatora." << endl;
              break;
              }
     default: cout << "Prosze wybrac poprawna opcje." << endl;
     } 
  }
}

