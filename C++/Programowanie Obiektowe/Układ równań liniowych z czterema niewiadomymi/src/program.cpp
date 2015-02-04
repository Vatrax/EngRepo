/* Autor: 			Wojciech Krzaczek				*/
/* Data ostatniej modyfikacji: 	20.04.2011r					*/
/* Program: 			Układ równań liniowych z czterema niewiadomymi	*/

#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "wektory.hh"
#include "macierz.hh"
#include "uklad.hh"
using namespace std;

int main ()
{
Uklad_rownan uklad;

uklad.zapisz();
uklad.rozwiaz();
uklad.wylicz_blad();
}
