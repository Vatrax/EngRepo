/* Wojciech Krzaczek
   nr indeksu: 184035
   Termin zajêæ: Œroda 8:30
   Lista: 1 Zadanie:4 */


#include <cstdlib>
#include <iostream>
#include <queue>
#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
    queue<int> kolejka;
    int i, w;
    int x;
    srand(time(NULL));
    
    cout << "Podaj wielkosc kolejki: ";
    cin >> w;
    cout << "Podaj maksymalna wartosc w kolejce: ";
    cin >> x;
    
    for(i=0; i<w; i++)
    {
             kolejka.push(rand() % x);

    }
    if (kolejka.empty())
    {
    cout << "Kolejka jest pusta" << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
    }
    
    x = kolejka.front();
    cout << "Na poczatku kolejki znajduje sie: " << x << endl;
        
    kolejka.pop();
    
    x = kolejka.front();
    cout << "Na poczatku kolejki znajduje sie: " << x << endl;
    
    w=kolejka.size();
    
    cout << "Wielkosc kolejki: " << w << endl;
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
