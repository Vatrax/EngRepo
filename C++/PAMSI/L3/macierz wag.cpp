/* Wojciech Krzaczek
nr indeksu: 184035
Termin zajec: Sroda 8:30
Lista: 3 MACIERZ WAG - Algorytm Prima i Kruskala*/

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>
#include <iomanip>

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

class kruskal
{
    public:
    krawedz * lista;
    int * kolory;
    int lw;
    krawedz * wyj;
    int dl;

    kruskal(graf *);

    void licz();
};

kruskal::kruskal(graf * arg)
{
    this->lw=arg->d;

    this->kolory= new int [lw];

    for(int i=0; i<lw; i++)
        this->kolory[i]=0;

    this->lista=NULL;

int waga;

    for(int i=0;i<lw;i++)
        for(int j=i; j<lw; j++)
        {
            waga=arg->tab[i][j];
            if(arg->tab[i][j]<1)
                continue;
            if(this->lista==NULL || this->lista->waga>=waga)
            {
                krawedz * nowa = new krawedz;
                nowa->w1=i;
                nowa->w2=j;
                nowa->waga=waga;
                nowa->nast=this->lista;
                this->lista=nowa;
                continue;
            }
            krawedz * wsk=this->lista;
            while (wsk->nast!=NULL)
            {
                if(wsk->nast->waga>=waga)
                break;
                wsk=wsk->nast;
            }
            krawedz * nowa = new krawedz;
            nowa->w1=i;
            nowa->w2=j;
            nowa->waga=waga;
            nowa->nast=wsk->nast;
            wsk->nast=nowa;
        }

this->dl=0;

this->wyj=NULL;
}

void kruskal::licz()
{
    krawedz * wsk=this->lista;
    if(wsk==NULL)
        return;
    int nastepny=1;
    while(wsk!=NULL)
    {
        if(this->kolory[wsk->w1]==0 && this->kolory[wsk->w2]==0)
        {
            this->kolory[wsk->w1]=nastepny;
            this->kolory[wsk->w2]=nastepny++;
        }
        else if(this->kolory[wsk->w1]==0)
        this->kolory[wsk->w1]=this->kolory[wsk->w2];
        else if(this->kolory[wsk->w2]==0)
        this->kolory[wsk->w2]=this->kolory[wsk->w1];
        else if(this->kolory[wsk->w2]==this->kolory[wsk->w1])
        {
            wsk=wsk->nast;
            continue;
        }
        else
        {
            for(int i=0; i<lw; i++)
            if(this->kolory[i]==this->kolory[wsk->w2])
            this->kolory[i]=this->kolory[wsk->w1];
        }
        krawedz * nowa = new krawedz;
        nowa->nast=this->wyj;
        nowa->w1=wsk->w1;
        nowa->w2=wsk->w2;
        nowa->waga=wsk->waga;
        this->wyj=nowa;
        this->dl+=wsk->waga;
        wsk=wsk->nast;
    }
}

class prim
{
    public:
    krawedz * lista;
    bool * kolory;
    int lw;
    krawedz * wyj;
    int dl;

    prim(graf *);

    void licz();
};

prim::prim(graf * arg)
{
    this->lw=arg->d;

    this->kolory=new bool [lw];

    for(int i=0; i<lw; i++)
        this->kolory[i]=false;

    this->lista=NULL;

int waga;

    for(int i=0;i<lw;i++)
        for(int j=i; j<lw; j++)
        {
            waga=arg->tab[i][j];
            if(arg->tab[i][j]<1)
                continue;
            if(this->lista==NULL || this->lista->waga>=waga)
            {
                krawedz * nowa = new krawedz;
                nowa->w1=i;
                nowa->w2=j;
                nowa->waga=waga;
                nowa->nast=this->lista;
                this->lista=nowa;
                continue;
            }
            krawedz * wsk=this->lista;
            while (wsk->nast!=NULL)
            {
                if(wsk->nast->waga>=waga)
                break;
                wsk=wsk->nast;
            }
            krawedz * nowa = new krawedz;
            nowa->w1=i;
            nowa->w2=j;
            nowa->waga=waga;
            nowa->nast=wsk->nast;
            wsk->nast=nowa;
        }

this->dl=0;

this->wyj=NULL;
}

void prim::licz()
{
    krawedz * wsk=this->lista;
    if(wsk==NULL)
        return;
    int pomoc=lw;
    this->kolory[this->lista->w1];
    kolory[lista->w1]=true;
    pomoc--;
    while(pomoc>0)
    {
        wsk=this->lista;
        while(kolory[wsk->w1]==kolory[wsk->w2])
              wsk=wsk->nast;
        kolory[wsk->w1]=true;
        kolory[wsk->w2]=true;
        dl+=wsk->waga;
        pomoc--;
    }
}


int main(int argc, char *argv[])
{
    int d, p, dl, m;
    float czas;
    clock_t start, stop;
    srand(time(NULL));

    d=10;                              //wielkosc grafu
    p=75;                               //procent zaplenienia grafu
    m=100;                                //zakres liczb

{
    graf * graf1 = new graf(d);
    graf1->uzupelnij(p,m);

    //graf1->zapis();
    graf1->wyswietl();
    cout << endl;

    start=clock();
    kruskal * kruskal1= new kruskal(graf1);
    //prim * prim1= new prim(graf1);

    kruskal1->licz();
    //prim1->licz();
    stop=clock();

    czas=stop - start;

    dl=kruskal1->dl;
    //dl=prim1->dl;

    cout << "dlugosc drzewa rozpinajacego: " << dl << endl << "Czas: " << czas << " ms" << endl;

    fstream plik;                                       //odczyt i zapis pliku
    plik.open("statystyki MW.txt", ios::out|ios::app);
    plik << czas << endl;
    plik.close();
    }
}
