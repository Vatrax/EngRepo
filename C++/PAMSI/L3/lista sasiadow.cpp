/* Wojciech Krzaczek
nr indeksu: 184035
Termin zajec: Sroda 8:30
Lista: 3 LISTA SASIADOW - Algorytm Prima i Kruskala*/

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>
#include <iomanip>

using namespace std;

struct list
{
    list *nast;
    int wagak;
    int wierz;
    list(int, int, list*);
};

list::list(int wierzch, int waga, list *nast)
{
    this->wagak=waga;
    this->wierz=wierzch;
    this->nast=nast;
}

class graf
{
    public:
    list **tab;
    int d;
    graf(int);
    void zapis();
    void wyswietl();
    void uzupelnij(int, int);
    bool dodaj(int, int, int);
    int szukaj(int, int);
};

graf::graf(int dlugosc)
{
    int i;
    this->d = dlugosc;
    this->tab = new list * [dlugosc];
    for (i=0; i<d; i++)
        tab[i]=NULL;
}

int graf::szukaj(int w1, int w2)
{
    list * wsk = this->tab[w1];
    while(wsk!=NULL)
    {
        if(wsk->wierz==w2)
        return wsk->wagak;
    wsk=wsk->nast;
    }

    return -1;
}

void graf::zapis()
{
    int i,j;
    fstream plik;                                       //odczyt i zapis pliku
    plik.open("graf LS.txt", ios::out|ios::app);
    for (i=0; i<d; i++)
    {
        plik << "[" << setw(3) << i <<"]";
        for(list * w=tab[i] ; w!=NULL; w=w->nast)
        {
            plik << " -> [" << setw(2) << w->wierz << "] " << setw(3) << w->wagak;
        }
        plik << endl;
    }
    plik.close();
}

/*void graf::wczytanie()
{
    int i,j;
    ifstream plik("graf LS.txt");

    for (i=0; i<d; i++)
    {
        plik
        for(list * w=tab[i] ; w!=NULL; w=w->nast)
        {
            plik << " -> [" << setw(2) << w->wierz << "] " << setw(3) << w->wagak;
        }
        plik << endl;
    }
    plik.close();
}*/

void graf::wyswietl()
{
    int i,j;
    for (i=0; i<d; i++)
    {
        cout << "[" << setw(2) << i <<"]";
        for(list * w=tab[i] ; w!=NULL; w=w->nast)
        {
            cout << " -> [" << setw(2) << w->wierz << "] " << setw(3) << w->wagak;
        }
        cout << endl;
    }
}

void graf::uzupelnij(int p, int m)
{
    int ilosc, n, i, tmp, tmp1, tmp2;
    ilosc=d*(d-1)/2;            //ilosc wszystkich krawedzi grafu
    n=ilosc*p/100;              //ilosc krawedzi jaka ma byc w grafie
    for(i=0;i<d-1;i++)
        dodaj(i,i+1,rand()%m+1);
    do
    i+=dodaj(rand()%d,rand()%d,rand()%m+1);
    while(i<n);
}

bool graf::dodaj(int pocz, int kon, int dl)
{
    if (pocz==kon)
        return false;
    if (pocz>d || kon>d)
        return false;
    for(list * w=tab[pocz]; w!=NULL; w=w->nast)
        if(w->wierz==kon)
            return false;
    list * nowy = new list(pocz, dl, tab[kon]);
    tab[kon]= nowy;
    nowy = new list(kon, dl, tab[pocz]);
    tab[pocz]= nowy;
    return true;
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
            waga=arg->szukaj(i,j);
            if(waga<1)
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
                if(wsk->nast->waga>= waga)
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

    this->kolory= new bool [lw];

    for(int i=0; i<lw; i++)
        this->kolory[i]=false;

    this->lista=NULL;

int waga;

    for(int i=0;i<lw;i++)
        for(int j=i; j<lw; j++)
        {
            waga=arg->szukaj(i,j);
            if(waga<1)
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
                if(wsk->nast->waga>= waga)
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
        {
              wsk=wsk->nast;
        }
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

    d=5;                              //wielkosc grafu 10 30 50 100 300
    p=50;                               //procent zaplenienia grafu
    m=10;                                //zakres liczb

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
    }
    fstream plik;                                       //odczyt i zapis pliku
    plik.open("statystyki LS.txt", ios::out|ios::app);
    plik << czas << endl;
    plik.close();
}
