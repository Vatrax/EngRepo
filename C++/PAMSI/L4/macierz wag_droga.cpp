/* Wojciech Krzaczek
nr indeksu: 184035
Termin zajec: Sroda 8:30
Lista: 4 MACIERZ WAG - Algorytm Dijkstry i Ballmana-Forda*/

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <list>

using namespace std;

class graf
{
    public:
    int **tab;
    int d;
    graf(int);
    void wyswietl();
    void zapis();
    void uzupelnij(int, int);
};

graf::graf(int dlugosc)
{
    int i,j;
    d = dlugosc;
    int **tab = new int *[d];
    for(i=0; i<d; i++)
    {
        tab[i] = new int[d];
    }
    for(i=0;i<d;i++)
    {
        for(j=0;j<d;j++)
        tab[i][j]=0;
    tab[i][i]=-1;
    }
}

void graf::zapis()
{
    int i,j;
    fstream plik;                                       //odczyt i zapis pliku
    plik.open("graf MW.txt", ios::out|ios::app);
    for (i=0; i<d; i++)
    {
        for(j=0; j<d; j++)
        {
            plik << setw(2) << tab[i][j] << " ";
        }
    plik << endl;
    }
    plik.close();
}

void graf::wyswietl()
{
    int i,j;
    for (i=0; i<d; i++)
    {
        for(j=0; j<d; j++)
        {
            cout << setw(2) << tab[i][j] << " ";
        }
    cout << endl;
    }
}

void graf::uzupelnij(int p, int m)
{
    int ilosc, n;
    ilosc=d*(d-1)/2;            //ilosc wszystkich krawedzi grafu
    n=(ilosc*p)/100;            //ilosc krawedzi grafu
    for(int i=0; i<d; i++)
        for(int j=i+1; (j<d) && (n>0); j++ , n--)
        {
        tab[i][j]=(rand()%m+1);
        tab[j][i]=tab[i][j];
        }
}

struct krawedz
{
    int w1, w2, waga;
    krawedz * nast;
};

class ford_gl // DFS
{
    public:
    krawedz * lista;
    int lw;
    graf * g;
    int przeplyw;

    ford_gl(graf *);

    int czy_droga(int, int);
    void licz(int, int, int);
};

ford_gl::ford_gl(graf * arg)
{
    this->lw=arg->d;

    this->lista=NULL;

    this->przeplyw=0;

    this->g=arg;

    int waga;

    for(int i=0;i<lw;i++)
        for(int j=i; j<lw; j++)
        {
             if(waga<1)
                continue;
            krawedz * nowa = new krawedz(i, j, waga, this->lista);
            this->lista=nowa;
        }
}

int ford_gl::czy_droga(int start, int meta)
{
    stack <int> stos;
    bool wierz[lw];
    int droga[lw];

    for(int i=0; i<lw; i++)
        wierz[lw]=false;

    stos.push(start);
    droga[start]=-1;

    while(!stos.empty())
    {
        start=stos.top();
        stos.pop();
        wierz[start]=true;
        for ( int i=lw-1; i>=0; --i)
            if(g->tab[start][i]!= 0  && wierz[i]!= true)
			{
				stos.push(i);
				wierz[i]=true;
				droga[i]=start;
			}
    }
    if (wierz[meta] == false)
        return false;

	return true;
}

void ford_gl::licz(int start, int meta, int max)
{

}

int main(int argc, char *argv[])
{
    int d, p, m, s, max;
    float czas1, czas2;
    clock_t start, stop;
    srand(time(NULL));

    d=5;                              //wielkosc grafu
    p=50;                               //procent zaplenienia grafu
    max=9;                                //zakres liczb
    s=0;                               //wierzcholek startowy
    m=d-1;                               //koncowy wierzcholek MAX= d-1;


    graf * graf1 = new graf(d);
    graf1->uzupelnij(p, max);

    //graf1->zapis();
    graf1->wyswietl();
    cout << endl;

    ford_gl * f1= new ford_gl(graf1);

    start=clock();
    f1->licz(s,m, max);
    stop=clock();

    czas1=stop - start;

    start=clock();
//    ford_sz * f2= new ford_sz(graf1);
//    f2->licz(s, m, max);
    stop=clock();

    czas2=stop - start;
    cout << endl << "przeplyw w glab: " << f1->przeplyw << endl;
    cout << endl << "Czas w glab: " << czas1 << " ms" << endl;
//    cout << endl << "Przeplyw: " << f2->przeplyw << endl;
//    cout << endl << "przeplyw w szerz: " << czas2 << " ms" << endl;


    fstream plik;                                       //odczyt i zapis pliku
    plik.open("statystyki MW.txt", ios::out|ios::app);
    plik << czas1 << endl << czas2 << endl;
    plik.close();
}
