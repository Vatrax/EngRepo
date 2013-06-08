#ifndef MACIERZ_HH
#define MACIERZ_HH



//klasa macierz
class Macierz
{
  Wektor _wiersze[4];

  public:
  Wektor& operator [] (unsigned int);
  Wektor operator * (Wektor);
  void wyswietl (std::ostream& , unsigned int);
  void zapisz (std::istream& , unsigned int);  
};


// przeciazenie operatorow przesuniec bitowych dla strumienia wejscia i wyjscia
std::ostream& operator << (std::ostream&, Macierz);
std::istream& operator >> (std::istream&, Macierz&);

#endif
