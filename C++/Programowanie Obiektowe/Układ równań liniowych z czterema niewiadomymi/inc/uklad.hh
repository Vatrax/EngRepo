#ifndef UKLAD_HH
#define UKLAD_HH





//klasa uklad
class Uklad_rownan
{
public:
Macierz _wartosci, _robocza;
Wektor _rozwiazanie, _wyrazy;

void zapisz ();
bool nie_zero (unsigned int);
void jedynka (unsigned int);
void do_zera (unsigned int);
void rozwiaz ();
void wylicz_blad ( );
};

#endif
