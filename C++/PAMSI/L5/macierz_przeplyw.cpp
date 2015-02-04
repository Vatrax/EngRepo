/* Wojciech Krzaczek
nr indeksu: 184035
Termin zajec: Sroda 8:30
Lista: 5 MACIERZ WAG - Algorytm Forda Fulkersona*/

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <stack>
#include <vector>
#include <queue>

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
    d = dlugosc;
    int **tab = new int *[d];

    for(int i=0; i<d; i++)
        tab[i] = new int[d];

    for(int i=0;i<d;i++)
    {
        for(int j=0;j<d;j++)
            tab[i][j]=0;
    tab[i][i]=-1;
    }
}

void graf::zapis()
{
    fstream plik;                                       //odczyt i zapis pliku
    plik.open("graf MW.txt", ios::out|ios::app);
    for (int i=0; i<d; i++)
    {
        for(int j=0; j<d; j++)
            plik << setw(2) << tab[i][j] << " ";
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
            cout << setw(2) << tab[i][j] << " ";
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
            tab[i][j]=(rand()%m+1);
}


class ford_gl // DFS
{
    public:
    int lw;
    int ** tab;
    int przeplyw;
    int * droga;

    ford_gl(graf *);

    int czy_droga(int, int);
    void licz(int, int, int);
};

ford_gl::ford_gl(graf * arg)
{
    this->lw=arg->d;

    this->przeplyw=0;

    this->tab = new int * [lw];
    for(int i=0; i<lw; i++)
        this->tab[i]= new int [lw];

    this->droga = new int [lw];//przechowuje indeksy wierzch

    for(int i=0; i<lw; i++)// kopia macierzy grafu
        for(int j=0; j<lw; j++)
            this->tab[i][j]=arg->tab[i][j];
}


int ford_gl::czy_droga(int start, int meta)
{
    stack <int> stos;
    bool wierz[lw];

    for(int i=0; i<lw; i++)
        wierz[lw]=false;

    stos.push(start);
    droga[start]=-1;

    while(!stos.empty())
    {
        start=stos.top();// spisuje to co jest na szczycie stosu(start)
        stos.pop();
        wierz[start]=true;
        for ( int i=lw-1; i>=0; --i)
            if(tab[start][i]!= 0  && wierz[i]!= true)
			{
				stos.push(i);
				wierz[i]=true;
				droga[i]=start;
			}
    }
	return wierz[meta];
}

void ford_gl::licz(int start, int meta, int max)//zlicza droge
{
    vector < vector<int> > przeplyw (this->lw , vector<int> (this->lw));
    vector < vector<int> > przepust (this->lw , vector<int> (this->lw));

    int min=max;

    for (int i=0; i<lw; i++)
		for (int j=0; j<lw; j++)
		{
            przeplyw[i][j] = this->tab[i][j];
			przepust[i][j] = 0;
		}

    while (czy_droga(start, meta))//dopóki s¹ po³¹czenia
    {
        min = max;

	for ( int i =this->lw-1 ; droga[i]>=0; i=droga[i])
	    if ( this->tab[droga[i]][i] > 0 )
            min = (min<this->tab[droga[i]][i])?min:this->tab[droga[i]][i];
		// wyszukuje najmniejszy mozliwy przeplyw pomiedzy krawedziami zawartymi w drodze

	for ( int i =this->lw-1 ; droga[i]>=0; i=droga[i])
		przepust[droga[i]][i] +=min;
		// jak juz znalazl najmniejsza wartosc to zapisuje to w elmentach skladajacych sie na droge z elementu pocz do kon.

	for (int i=0; i<this->lw; i++)
        for (int j=0; j<this->lw; j++)
            this->tab[i][j] = przeplyw[i][j] - przepust[i][j];
		// otrzymujemy nowa macierz ktora jest juz pomniejszona o dany przepust.

	this->przeplyw += min;
    }

}
class ford_sz // BFS
{
    public:
    int lw;
    int ** tab;
    int przeplyw;
    int * droga;

    ford_sz(graf *);

    int czy_droga(int, int);
    void licz(int, int, int);
};

ford_sz::ford_sz(graf * arg)
{
    this->lw=arg->d;

    this->przeplyw=0;

    this->tab = new int * [lw];
    for(int i=0; i<lw; i++)
        this->tab[i]= new int [lw];

    this->droga = new int [lw];

    for(int i=0; i<lw; i++)
        for(int j=0; j<lw; j++)
            this->tab[i][j]=arg->tab[i][j];
}

int ford_sz::czy_droga(int start, int meta)
{
    queue <int> kolejka;
    bool wierz[lw];

    for(int i=0; i<lw; i++)
        wierz[lw]=false;

    kolejka.push(start);
    droga[start]=-1;

    while(!kolejka.empty())
    {
        start=kolejka.front();
        kolejka.pop();
        wierz[start]=true;

        for ( int i=0; i<lw; i++)
            if(tab[start][i]!= 0  && wierz[i]!= true)
			{
				kolejka.push(i);
				wierz[i]=true;
				droga[i]=start;
			}
    }

	return  wierz[meta];
}

void ford_sz::licz(int start, int meta, int max)
{
    vector < vector<int> > przeplyw (this->lw , vector<int> (this->lw));
    vector < vector<int> > przepust (this->lw , vector<int> (this->lw));

    int min=max;

    for (int i=0; i<lw; i++)
		for (int j=0; j<lw; j++)
		{
            przeplyw[i][j] = this->tab[i][j];
			przepust[i][j] = 0;
		}

    while (czy_droga(start, meta))
    {
        min = max;

	for ( int i =this->lw-1 ; droga[i]>=0; i=droga[i])
	    if ( this->tab[droga[i]][i] > 0 )
            min = (min<this->tab[droga[i]][i])?min:this->tab[droga[i]][i];
		// wyszukuje najmniejszy mozliwy przeplyw pomiedzy krawedziami zawartymi w drodze

	for ( int i =this->lw-1 ; droga[i]>=0; i=droga[i])
		przepust[droga[i]][i] +=min;
		// jak juz znalazl najmniejsza wartosc to zapisuje to w elmentach skladajacych sie na droge z elementu pocz do kon.

	for (int i=0; i<this->lw; i++)
        for (int j=0; j<this->lw; j++)
            this->tab[i][j] = przeplyw[i][j] - przepust[i][j];
		// otrzymujemy nowa macierz ktora jest juz pomniejszona o dany przepust.

	this->przeplyw += min;
    }

}


int main(int argc, char *argv[])
{
    int d, p, m, s, max;
    float czas1, czas2;
    clock_t start, stop;
    srand(time(NULL));

    d=5;                              //wielkosc grafu
    p=100;                               //procent zaplenienia grafu
    max=9;                                //zakres liczb
    s=0;                               //wierzcholek startowy
    //m=d-1;                               //koncowy wierzcholek MAX= d-1;


    graf * graf1 = new graf(d);
    graf1->uzupelnij(p, max);

    //graf1->zapis();
    graf1->wyswietl();
    cout << endl;

    ford_gl * f1= new ford_gl(graf1);

    start=clock();
    f1->licz(s,d-1, max);
    stop=clock();

    czas1=stop - start;

    start=clock();
    ford_sz * f2= new ford_sz(graf1);
    f2->licz(s, d-1, max);
    stop=clock();

    czas2=stop - start;


    cout << endl << "Przeplyw w glab: " << f1->przeplyw;
    cout << endl << "Czas w glab: " << czas1 << " ms" << endl;
    cout << endl;
    cout << endl << "Przeplyw w szerz: " << f2->przeplyw;
    cout << endl << "Czas w szerz: " << czas2 << " ms" << endl;


    fstream plik;                                       //odczyt i zapis pliku
    plik.open("statystyki MW.txt", ios::out|ios::app);
    plik << czas1 << endl << czas2 << endl;
    plik.close();
}
