/* Autor: 			Wojciech Krzaczek	*/
/* Data ostatniej modyfikacji: 	30.03.2011r		*/
/* Program: 			Kalkulator wektorow RPN	*/

/* Ten program to kalkulator RPN wektorow, dzialajacy na stosie.
   Za jego pomoca mozna dodawac odejmowac a takze mnozyc wektorowo. */

#include "modul.hh"

using namespace std;

int main()
{
Kalk kal;

PowitanieOrazInformacje();
kal.dzialanie();
}
