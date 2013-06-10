/*****************************************************************************
 * Copyright (c) 2009 Bogdan Kreczmer
 *
 * Niniejszy plik zostal utworzony jako przyklad na potrzeby nauki
 * programowania w jezyku C++ w ramach kursu "Programowanie obiektowe"
 * prowadzonego na kierunku Automatyka i Robotyka, Wydzialu Elektroniki
 * Politechniki Wroclawskiej. Plik ten jest udostepniany na licencji
 * GNU General Public License v.3.
 *
 * Fragmenty tego programu moga byc wykorzystane w programach realizowanych
 * w ramach zadan laboratoryjnych pod warunkiem zacytowania zrodla, z ktorego
 * zostaly one pobrane.
 *****************************************************************************/

/*****************************************************************************
 * W niniejszym przykladzie prezentowane sa podstawowe operacje na listach
 * wraz z przykladami opisow funkcji.
 *
 *****************************************************************************/

#include <iostream>
#include <list>
using namespace std;

typedef list<int>  ListaLiczb;



/*
 * Usuwa z listy wskazany element.
 * 
 * Parametry:
 *   Lista      - lista, z ktorej ma byc usuniety wybrany element.
 *   NrElementu - numer elementu listy, ktory ma zostac usuniety,
 *                przy czym numeracja elementow w liscie rozpoczyna
 *                sie od 0. Tak wiec numer pierwszego elementu to 0.
 *
 * Warunki wstepne:
 *   Aby operacja sie powiodla musi zachodzic warunek: 
 *                                    Lista.size() > NrElementu
 * Zwraca:
 *   true  - gdy element o podanym numerze zostanie znaleziony i usuniety.
 *   false - w przypadku przeciwnym.
 *
 * Warunki koncowe:
 *   Jezeli operacja powiedzie sie, to zostaje usuniety wskazny element.
 *   W przypadku przeciwnym lista pozostaje niezmieniona
 */
bool UsunElement(ListaLiczb& Lista, unsigned int NrElementu)
{
  if (Lista.empty()) return false;

  ListaLiczb::iterator  Iter = Lista.begin();

  for (; NrElementu > 0 && Iter != Lista.end(); --NrElementu, ++Iter) ;

  if (NrElementu) return false;
  Lista.erase(Iter);
  return true;
}



/*
 * Zmienia wartosc wskazanego elementu listy
 * 
 * Parametry:
 *   Lista      - lista, ktorej element ma zostac zmodyfikowany.
 *   NrElementu - numer element listy, ktorego wartosc ma zostac zmieniona,
 *                przy czym numeracja elementow w liscie rozpoczyna
 *                sie od 0. Tak wiec numer pierwszego elementu to 0.
 *   Wartosc    - wartosc, ktora ma byc wpisana do wskazanego elementu
 *                listy.
 *
 * Warunki wstepne:
 *   Aby operacja sie powiodla musi zachodzic warunek: 
 *                                    Lista.size() > NrElementu
 * Zwraca:
 *   true  - gdy element o podanym numerze zostanie znaleziony i jego wartosc
 *           zostanie zmodyfikowana.
 *   false - w przypadku przeciwnym.
 *
 * Warunki koncowe:
 *   Jezeli operacja powiedzie sie, to zostaje zmieniona zawartosc wskazanego
 *   elementu. W przypadku przeciwnym lista pozostaje niezmieniona.
 */
bool ZmienElement(ListaLiczb& Lista, unsigned int NrElementu, int Wartosc)
{
  if (Lista.empty()) return false;

  ListaLiczb::iterator  Iter = Lista.begin();

  for (; NrElementu > 0 && Iter != Lista.end(); --NrElementu, ++Iter) ;

  if (NrElementu) return false;
  *Iter = Wartosc;
  return true;
}




/*
 * Wyswietla (tzn. wpisuje do strumienia wyjscia standardowego)
 * zawartosc listy w formacie:
 *
 *  Element: wartosc_elementu_nr_0
 *  Element: wartosc_elementu_nr_1
 *  Element: wartosc_elementu_nr_2
 *         ...
 *  Element: wartosc_elementu_nr_N
 * 
 * Parametry:
 *   Lista      - lista, ktorej wartosci elementow maja zostac wyswietlone.
 *
 * Warunki wstepne:
 *   Strumien wyjscia standardowego musi byc otwarty do zapisu.
 *
 * Warunki koncowe:
 *   Jezeli lista nie jest pusta, to do strumienia wyjscia standardowego
 *   zostaje wpisany wydruk zawartosci listy w formacie pokazanym powyzej.
 *   Jezeli lista jest pusta, to nie jest podejmowana zadna akcja.
 */
void WyswietlListe(const ListaLiczb& Lista)
{
  for (ListaLiczb::const_iterator Iter = Lista.begin();
       Iter != Lista.end();
       ++Iter) 
    cout << " Element: " << *Iter << endl;
}




int main()
{
  ListaLiczb  Lista;

  Lista.push_back(0);
  Lista.push_back(1);
  Lista.push_back(2);
  Lista.push_back(3);

  WyswietlListe(Lista);
  cerr << "=========================" << endl;
  UsunElement(Lista,2);
  WyswietlListe(Lista);
  
 
  cerr << "=========================" << endl;
  ZmienElement(Lista,1,999);
  WyswietlListe(Lista);
}
