/* Wojciech Krzaczek
   nr indeksu: 184035
   Termin zajêæ: Œroda 8:30
   Lista: 1 Zadanie:2 */


#include <list>
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
    list<int> lista;
    int i, w;
    int x, y;
    srand(time(NULL));
        
    cout << "podaj wielkosc listy: ";
    cin >> w;
    cout << "podaj maksymalna wartosc w liscie: ";
    cin >> x;
    
    for(i=0; i<w; i++)
    {
               lista.push_front(rand()% x);
    }
    
    size_t rozmiar = lista.size();
    
    list<int>::iterator it;
    cout << "lista po kolei: " << endl;
    for( it=lista.begin(); it!=lista.end(); ++it )
    {
      cout << *it << " ";  
    }
    cout << endl << "dodaj 2 elementy na poczatek listy:" << endl;
    cout << "1. element: ";
    cin >> y;
    cout << "2. element: ";
    cin >> x;
    lista.push_front(y);
    lista.push_front(x);
    
    if (lista.empty())
    {
    system ("PAUSE");
    return EXIT_SUCCESS;
    }
    
    lista.pop_back();
      
    if (lista.empty())
    {
    system ("PAUSE");
    return EXIT_SUCCESS;
    }
    
    lista.pop_front();
    

         
    for( it=lista.begin(); it!=lista.end(); ++it )
    {
      cout << *it << " ";
    }
        
    w = lista.size();
    cout << endl << "Wielkosc listy: " << w << endl;
        
    system("PAUSE");
    return EXIT_SUCCESS;
}
