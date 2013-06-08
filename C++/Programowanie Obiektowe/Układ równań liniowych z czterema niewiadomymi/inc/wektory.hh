#ifndef WEKTORY_HH
#define WEKTORY_HH


//klasa wektor
class Wektor
{
double _dane[4];
public:
double& operator [] (unsigned int);
Wektor operator * (double);
Wektor operator + (Wektor);
Wektor operator - (Wektor);
double dlugosc ();
bool sprawdz_zero (unsigned int);
double jedynka (unsigned int);
};

std::ostream& operator << (std::ostream&, Wektor);
std::istream& operator >> (std::istream&, Wektor&);

#endif
