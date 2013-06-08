/* Wojciech Krzaczek
   nr indeksu: 184035
   Termin zajêæ: Œroda 8:30
   Lista: 1 Zadanie:3 */


#include <cstdlib>
#include <iostream>
#include <stack>
#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
    stack<int> stos;
    int i, w;
    int x;
    srand(time(NULL));
    
    cout << "podaj wielkosc stosu: ";
    cin >> w;
    cout << "podaj maksymalna wartosc w stosie: ";
    cin >> x;
    
    for (i=0; i<w; i++)
    {
        stos.push( rand() % x);
    } 
    
    x = stos.top();
    cout << "Na szczycie stosu znajduje sie: " << x << endl;
    
    stos.pop();
    
    cout << "Dodaj element na szczyt stosu: ";
    cin >> x;
    stos.push(x);
    
    x = stos.top();
    cout << "Na szczycie stosu znajduje sie: " << x << endl;
    
    w=stos.size();
    cout << "Wielkosc stosu: " << w << endl;
    
    system("PAUSE");
    return EXIT_SUCCESS;
}

