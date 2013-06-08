/* Wojciech Krzaczek
nr indeksu: 184035
Termin zajec: Sroda 8:30
Lista: 2 Sortowania: babelkowe, przez scalanie, szybkie*/

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

class macierz
{
    public:
    int *tab;
    int *tmp;
    macierz(int);
    void uzupelnij(int, int);
    void bubblesort(int);
    void quicksort(int, int);
    void mergesort(int, int);
    void mergesort_odwrot(int, int);
    void merge(int, int, int);
    void merge_odwrot(int, int, int);
    void wyswietl(int);
    void zera(int, float);
    void sprawdzenie(int);
};

macierz::macierz(int d)
{
    tab = new int [d]; //deklaracja tablicy dynamicznej
    tmp = new int [d]; //deklaracja pomocniczej tablicy dynamicznej
}

void macierz::uzupelnij(int m, int d)
{
    int i;
    for(i=0; i<d; i++) // wpisanie losowych liczb
        tab[i]= rand()% m+1;
}

void macierz::wyswietl(int d)
{
    int i;
    for(i=0; i<d; i++)
        cout << tab[i] << " ";
    cout << endl;
}
void macierz::sprawdzenie(int d)
{
    int i,j=0;
    for(i=1; i<d; i++)
        {
            if(tab[i]<tab[i-1])
            j=1;
        }
        if (j==1)
        cout << "blad sorotwania" << endl;
}

/*====================SORTOWANIE BABELKOWE=================================*/
void macierz::bubblesort(int d)
{
    int i, tmp;
    while (d>1)
    {
        for(i=0; i<d-1; i++)
            if (tab[i]>tab[i+1])
            {
                tmp=tab[i];
                tab[i]=tab[i+1];
                tab[i+1]=tmp;
            }
        d=d-1;
    }
}

/*====================SORTOWANIE SZYBKIE===================================*/
void macierz::quicksort(int pocz, int d)
{
    int i,j,v,tmp;
    i=pocz;
    j=d;
    v=tab[(pocz+d)/2];          //srodek przedzialu
    do
    {
        while (tab[i]<v)        //sprawdzanie czy wartosc lewych czesci tablicy jest mniejsza od v
            i++;
        while (v<tab[j])        //sprawdzanie czy wartosc prawych czesci tablicy jest wieksza od v
            j--;
        if (i<=j)
        {
            tmp=tab[i];         //zamiana wartosci i i j w tablicy
            tab[i]=tab[j];
            tab[j]=tmp;
            i++;
            j--;
        }
    }
    while (i<=j);
    if (pocz<j) quicksort(pocz,j);  //rekurnencyjne wywolanie sortowania dla polowy tablicy
    if (i<d) quicksort(i,d);
}

/*====================SORTOWANIE PRZEZ SCALANIE============================*/
void macierz::merge(int pocz, int sr, int d)
{

    int i,j,q;
    for (i=pocz; i<=d; i++)
        tmp[i]=tab[i];
    i=pocz;
    j=sr+1;
    q=pocz;
    while (i<=sr && j<=d)
    {
        if (tmp[i]<tmp[j])
        tab[q++]=tmp[i++];
        else
        tab[q++]=tmp[j++];
    }
    while (i<=sr)
        tab[q++]=tmp[i++];
}

void macierz::mergesort(int pocz, int d)
{
    int sr;
    if (pocz<d)
    {
        sr=(pocz+d)/2;
        mergesort(pocz, sr);
        mergesort(sr+1, d);
        merge(pocz, sr, d);
    }
}

/*====================SORTOWANIE OODWROTNE=================================*/
void macierz::merge_odwrot(int pocz, int sr, int d)
{

    int i,j,q;
    for (i=pocz; i<=d; i++)
    tmp[i]=tab[i];                          // Skopiowanie danych do tablicy pomocniczej
    i=pocz;                                 // Ustawienie wskazników tablic
    j=sr+1;
    q=pocz;
    while (i<=sr && j<=d)                   // Przenoszenie danych z sortowaniem ze zbiorów pomocniczych do tablicy glownej
    {
        if (tmp[j]<tmp[i])
        tab[q++]=tmp[i++];
        else
        tab[q++]=tmp[j++];
    }
    while (i<=sr)
        tab[q++]=tmp[i++];                  // Przeniesienie nie skopiowanych danych ze zbioru pierwszego w przypadku, gdy drugi zbior sie skonczyl
}

void macierz::mergesort_odwrot(int pocz, int d)
{
    int sr;
    if (pocz<d)
    {
        sr=(pocz+d)/2;
        mergesort_odwrot(pocz, sr);     //rekurnencyjne wywolanie sortowania dla polowy tablicy
        mergesort_odwrot(sr+1, d);
        merge_odwrot(pocz, sr, d);      // laczenie
    }
}
/*=========================================================================*/
void macierz::zera(int d, float ilosc)
{
    int i;
    float df=d;                 //rzutowanie dlugosci na float
    for(i=0; i<(df*ilosc); i++)
    tab[i]=0;
}
/*=========================================================================*/
/*=========================================================================*/
/*===========================PROGRAM GLOWNY================================*/
/*=========================================================================*/
/*=========================================================================*/


int main(int argc, char *argv[])
{
int i, j, d, m, t, tmp;
int licz=1, ilosc[]={10000, 50000, 100000, 500000, 1000000};
clock_t start, stop;
float czas, av=0, procent[]={0.25, 0.5, 0.75, 0.95, 0.99, 0.997};
srand(time(NULL));

cout << ">>>Podaj liczbe tysiecy elementow: "; //wczytywanie wartosci
cin >> d;
if (cin.fail())
    return 1;
//d=d*1000;

//for (i=0; i<5; i++)                              //petla dla roznej ilosci elementow normalnie=5, bubble=3
{
    //d=ilosc[i];
    cout << "ILOSC ELEMENTOW: " << d << endl;
    fstream plik;                                       //odczyt i zapis pliku
    plik.open("statystyki.txt", ios::out|ios::app);
    plik << "ILOSC ELEMENTOW: " << d << " ***********************************************************" << endl;
    plik.close();
    macierz * mac = new macierz(d);
    cout << ">>>Podaj max wartosc: ";             //ustalanie maksymalnej wartosci w tablicy
    cin >> m;
    if (cin.fail())
    return 1;
//m=1000;

t=d;
//for(j=0; j<6; j++)                              //dla czesci postortowanych elementow
{
    /*cout << "ILOSC POSORTOWANYCH ELEMENTOW: " << procent[j] << endl;
    fstream plik;                                       //odczyt i zapis pliku
    plik.open("statystyki.txt", ios::out|ios::app);
    plik << "ILOSC POSORTOWANYCH ELEMENTOW: " << procent[j] << " =======================================================" << endl;
    plik.close();*/
//for(licz=0; licz<100; licz++)                      // 100-krone sortowanie 10- dla bubble
{
    mac->uzupelnij(m, d);                               //uzupelnienie losowymi elementami
    //mac->mergesort_odwrot(0, d-1);                      //sorotowanie odwrotne
    mac->zera(d, procent[j]);                           //posortowanie czesci tablicy
    start=clock();                                      //uruchomienie licznika czasu
    //mac->bubblesort(d);                                 //sorotowanie babelkowe
    //mac->quicksort(0, d-1);                             //sortowanie szybkie
    //mac->mergesort(0, d-1);                             //sortowanie przez scalanie
    stop=clock();                                       //zatrzymanie licznika czasu
    mac->wyswietl(d);                                   //wyswietlanie posortowanych elementow
    mac->sprawdzenie(d);
    czas=stop - start;                                  //oblicznie czasu pracy
    cout << licz+1 << ". Czas pracy: " << czas << " ms" << endl;

    fstream plik;                                       //odczyt i zapis pliku
    plik.open("statystyki.txt", ios::out|ios::app);
    plik << czas << endl;
    plik.close();
    av=av+czas;
}
cout << "Sredni czas sortowania:" << av/licz << " ms"<<endl;
av=0;
}
}
system("PAUSE");
return EXIT_SUCCESS;
}
