/* Wojciech Krzaczek
   nr indeksu: 184035
   Termin zajêæ: Œroda 8:30
   Lista: 2 Zadanie:Sortowanie babelkowe */

#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
    int     i, j, d, t, tmp;
    int     m;
    clock_t start, stop;
    float czas;
    srand(time(NULL));

cout << ">>>Podaj liczbe tysiecy elementow: ";      //wczytywanie wartosci
cin >> d;
cout << ">>>Podaj max wartosc: ";
cin >> m;

d=d*1000;
int *tab = new int [d];                         //deklaracja tablicy dynamicznej
t=d;
/* PETLA ILOSCI WYKONAN SORTOWANIA */
for (j=0;j<10;j++)
{
d=t;

for(i=0; i<d; i++)                              // wpisanie losowych liczb
{   
    tab[i]= rand()% m+1;
}
/*for (i=0 ; i<d; i++)                            //wypisanie warosci tablicy
{
    cout<<tab[i]<< " "; 
}*/
start=clock();                                  //uruchomienie licznika czasu
/*====================SORTOWANIE BABELKOWE=================================*/
while (d>1)
{
      for(i=0; i<d-1; i++)
      {
               if (tab[i]>tab[i+1])
               {
                                   tmp=tab[i];
                                   tab[i]=tab[i+1];
                                   tab[i+1]=tmp;
               }
      }
d=d-1;
}
/*=========================================================================*/
stop=clock();                                   //zatrzymanie licznika czasu
for(i=0; i<t; i++)                              //wypisanie posorotwanych wartosci
/*{
cout << tab[i] << " ";
}
cout < endl;*/

czas=(stop - start);                            //oblicznie czasu pracy
/*ofstream outfile ("czasy.txt")


cout << "Czas pracy: " << czas << " ms" << endl;

outfile.close();*/
cout << "Czas pracy: " << czas << " ms" << endl;
}
    system("PAUSE");
    return EXIT_SUCCESS;
}
