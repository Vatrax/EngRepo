#ifndef WEKTORY_HH
#define WEKTORY_HH


//klasa wektor
class Wektor
{
  TYP _dane[4];
  public:
  TYP& operator [] (unsigned int);
  Wektor operator * (TYP);
  Wektor operator + (Wektor);
  Wektor operator - (Wektor);
  TYP dlugosc ();
  bool sprawdz_zero (unsigned int);
  TYP jedynka (unsigned int);
};

std::ostream& operator << (std::ostream&, Wektor);
std::istream& operator >> (std::istream&, Wektor&);

#endif
