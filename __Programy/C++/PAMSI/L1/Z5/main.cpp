/* Wojciech Krzaczek
   nr indeksu: 184035
   Termin zajêæ: Œroda 8:30
   Lista: 1 Zadanie:5 */

#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

class list
{
      struct elem
      {
            int wartosc;
            elem *nast;
      };
      
      elem *poczatek;
                 
      public:
             list();
             ~list();
             void push_front(int);
             void push_back(int);
             void pop_back();
             void pop_front();
             bool empty();
             int size();
             elem *begin();
             elem *end();
             elem *nast(elem *);
};

list::list()
{
poczatek = NULL;
}

list::~list()
{
while(!empty())
     pop_front();
}

bool list::empty()
{
     elem * element = poczatek;
     if(element -> nast == NULL);
}

int list::size()
{
    int i;
    elem * element = poczatek;
    for(i=0; element -> nast != NULL; i++)
                  element = element -> nast;
    return i;
}

             
void list::push_front(int i)
{
     elem * element = poczatek;
     elem * nowy = new elem;
     
     nowy -> wartosc = i;
     nowy -> nast = element -> nast;
     poczatek = nowy;
};

void list::push_back(int i)
{
     if(empty())
     {
                push_front(i);
                return;
     }
     elem * element = poczatek;
     while(element -> nast != NULL)
                element = element -> nast;
     elem * nowy = new elem;
     nowy -> wartosc = i;
     nowy -> nast = NULL;
     element -> nast = nowy;
}

void list::pop_front()
{
     if(empty())
                return;
     elem * element = poczatek;
     elem * end = poczatek -> nast;
     poczatek -> nast = end;
     delete element;
}
void list::pop_back()
{
     if(empty())
     
                return;
     elem * element = poczatek;
     elem * end = poczatek -> nast;
     if( end -> nast = NULL)
     {
                pop_front();
                return;
     }
     while (end -> nast != NULL)
                element = element -> nast;
     delete end;
}

int main(int argc, char *argv[])
{
    list lista;
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
    
/*    list<int>::iterator it;
    cout << "lista po kolei: " << endl;
    for( it=lista.begin(); it!=lista.end(); ++it )
    {
      cout << *it << " ";  
    }*/
    cout << endl << "dodaj 2 elementy na poczatek listy:" << endl;
    cout << "1. element: ";
    cin >> y;
    cout << "2. element: ";
    cin >> x;
    lista.push_front(x);
    lista.push_front(y);
    
    lista.pop_back();
    
    if (lista.empty())
    {
    system ("PAUSE");
    return EXIT_SUCCESS;
    }
    
    lista.pop_front();
    
    if (lista.empty())
    {
    system ("PAUSE");
    return EXIT_SUCCESS;
    }
    
    w = lista.size();
    cout << endl << "Wielkosc listy: " << w << endl;
        
    system("PAUSE");
    return EXIT_SUCCESS;
}
