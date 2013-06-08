#include "modul.hh"

using namespace std;

void PowitanieOrazInformacje()				// Wizualne menu
{
  cout << endl
       << "Ten program czyta znaki oraz liczby zmiennoprzecinkowe i je rozroznia." << endl
       << "Operacje na stosie i operacje dodatkowe:" << endl
       << "+  dodawanie," << endl
       << "-  odejmowanie," << endl
       << "*  mnozenie." << endl << endl 
       << "&  zduplikowanie argumentu znajdujacego sie na szczycie stosu," << endl
       << "#  usuniecie argumentu ze szczytu stosu," << endl
       << "$  zamiana kolejnosci dwoch argumentow na szczycie stosu," << endl
       << "?  wyswietlenie zawartosci calego stosu," << endl
       << "p  wyswietlenie argumentu ze szczytu stosu," << endl
       << "q  zakonczenie dzialania programu." << endl
       << "Podaj znak dzialania lub wektor >";
}
ostream & operator << (ostream & StrmWy, wektor w)	//przeciozenie operatora << (wyjscia)
{
  StrmWy << '('<<w.x<<','<<w.y<<','<<w.z<<')' <<endl;
  return StrmWy;
}

istream & operator >> (istream & StrmWej, wektor & w)	//przeciezenie operatora >> (wejscia)
{
char znak;
StrmWej >> znak;
if(znak != '(')
{ cerr << "Blad! Wektor nie pasuje do szablonu." << endl; exit(1); }
StrmWej >> w.x;
if ( StrmWej.fail() )
{ cerr << "Blad! wspolrzedna X nie pasuje do szablonu." << endl; exit(1); }
StrmWej >> znak;
if(znak != ',')
{ cerr << "Blad! Brak ','! Nie pasuje do szablonu." << endl; exit(1); }
StrmWej >> w.y;
if ( StrmWej.fail() )
{ cerr << "Blad! wspolrzedna Y nie pasuje do szablonu." << endl; exit(1); }
StrmWej >> znak;
if(znak != ',')
{ cerr << "Blad! Brak ','! Nie pasuje do szablonu." << endl; exit(1); }
StrmWej >> w.z;
if ( StrmWej.fail() )
{ cerr << "Blad! wspolrzedna Z nie pasuje do szablonu." << endl; exit(1); }
StrmWej >> znak;
if(znak != ')')
{ cerr << "Blad! Wektor nie pasuje do szablonu." << endl; exit(1); }
return StrmWej;
}            
  
wektor wektor::operator + (wektor w1)   //przeciazenie dodawania dla zmiennej typu wektor
{ 
    w1.x += x;
    w1.y += y;
    w1.z += z;
    return w1;
}

wektor wektor::operator - (wektor w1)   //przeciazenie odejmowania
{ 
    w1.x -= x;
    w1.y -= y;
    w1.z -= z;
    return w1;
}

wektor wektor::operator * (wektor w1)   //przeciazenie operacji iloczynu wektorowego
{
    wektor wynik;
    wynik.x = w1.y*z-w1.z*y;
    wynik.y = w1.z*x-w1.y*z;
    wynik.z = w1.x*y-w1.x*x;
    return wynik;
}

bool Stos::poloz(wektor w)		// funkcja umieszczajaca wektor na stosie
{
    if(_ilosc<rozm_tab-1)
      {
      _tab[_ilosc++]=w;
      return false;
      }
    else
      {
      return true;
      }
}

wektor Stos::sciagnij()			// funkcja usuwajaca wektor ze szczytu stosu
{
      wektor w, w_pom;
      w.x=0; w.y=0; w.z=0;

      if(_ilosc>0)
      {
	w_pom=_tab[--_ilosc];
	_tab[_ilosc]=w;
	return w_pom;
      }   else
      {
	return w;
      }
}

bool Stos::podgladnij()			// przeglad wszystkich wektorow ze stosu
{
    if (_ilosc>0) { cout << _tab[_ilosc-1]; return true; }
    return false;
}

void Stos::wypisz()					// funkcja wypisujaca zawartos stosu
{
    int index=_ilosc;
    while(index>0)
	{
      cout << _tab[index-1] << endl;
      --index;
	}
}

bool Kalk::zapamietaj_arg()				// wczytanie wektora
{
  wektor wek1;
  cin >> wek1;
  _st_arg.poloz(wek1);
  return true;
}

bool Kalk::dzialanie()					// Wczytywanie opcji i wykonanie odpowiedniego dzialania
{
    char oper;
    do
  {
    cin >> oper;
    switch (oper)
   {
     case '+':{
       _st_arg.poloz(_st_arg.sciagnij()+_st_arg.sciagnij());
       break;}    
     case '-':{
       _st_arg.poloz(_st_arg.sciagnij()-_st_arg.sciagnij());
    break;}    
     case '*':{
       _st_arg.poloz(_st_arg.sciagnij()*_st_arg.sciagnij());
    break;}   
     case '?':{
       wypisz();
    break;}   
     case '&':{
       duplikuj();
    break;}    
     case '$':{
       zmien();
    break;}   
     case '#':{
       usun();
    break;}
     case '(':{
	cin.putback(oper);
	zapamietaj_arg();
    break;}   
     case 'p':{
       _st_arg.podgladnij();
    break;}
     case 'q':{
       cout << "Dziekuje za skorzystanie z programu."<< endl;
    break;}
    default:{
      cout<<"Zly operator"<<endl;}
   }   
  } while (oper != 'q');
 return true;
}

void Kalk::wypisz(){_st_arg.wypisz();} 		//wypisuje wektor

void Kalk::zmien()                     		//zamienia wektory kolejnoscia
{                   
    wektor pom1, pom2;
    pom1=_st_arg.sciagnij();
    pom2=_st_arg.sciagnij();
    _st_arg.poloz(pom1);
    _st_arg.poloz(pom2);
}

void Kalk::usun(){_st_arg.sciagnij();}		//usuwa wektor ze stosu

void Kalk::duplikuj()                  		//duplikuje wektor znajdujcie sosu
{
    wektor pom;
    pom=_st_arg.sciagnij();
    _st_arg.poloz(pom);
    _st_arg.poloz(pom);
}

bool Kalk::CzyLiczbaDoWczytania()
{
  char  PierwszyZnak;
  bool  JestLiczba = false;

  while (isspace(PierwszyZnak = cin.get()) && PierwszyZnak != EOF);
  if (PierwszyZnak == EOF) exit(0);

  if (PierwszyZnak == '+' || PierwszyZnak == '-')
  {
       JestLiczba = isdigit(cin.get());
       cin.unget();
  }
  else JestLiczba = isdigit(PierwszyZnak);

  cin.putback(PierwszyZnak);
  return JestLiczba;  
}

bool Kalk::czywektor()
{
  char znak;
  znak =cin.get();
  cin.unget();
  if (znak=='(')
  {
    return 1;
  }  else
  {
    return 0;
  }
}
