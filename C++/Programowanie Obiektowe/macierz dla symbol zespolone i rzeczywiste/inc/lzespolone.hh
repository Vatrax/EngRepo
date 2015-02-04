#ifndef LZESPOLONE_HH
#define LZESPOLONE_HH


// Klasa liczba zespolona

class LZespolona
{
  public:
  double re, im;

  LZespolona operator + ( LZespolona );
  LZespolona operator - ( LZespolona );
  LZespolona operator * ( LZespolona );
  LZespolona& operator = ( double );
  bool operator == ( double );
};


// Przeciążenie operatora dzielenia liczby double przez liczbę zespoloną

LZespolona operator / ( double, LZespolona );


// wyświetlanie liczby zespolonej

void WysRE ( std::ostream &, LZespolona );
void WysIM ( std::ostream &, LZespolona );
std::ostream & operator << ( std::ostream &, LZespolona );

// wczytywanie liczby zespolonej

std::istream & operator >> ( std::istream &, LZespolona & );


#endif
