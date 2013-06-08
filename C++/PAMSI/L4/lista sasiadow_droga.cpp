/* Wojciech Krzaczek
nr indeksu: 184035
Termin zajec: Sroda 8:30
Lista: 4 LISTA SASIADOW - Algorytm Dijkstry i Ballmana-Forda*/

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <list>

using namespace std;

struct lista
{
    lista *nast;
    int wagak;
    int wierz;
    lista(int, int, lista*);
};

lista::lista(int wierzch, int waga, lista *nast)
{
    this->wagak=waga;
    this->wierz=wierzch;
    this->nast=nast;
}

class graf
{
    public:
    lista **tab;
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
    this->tab = new lista * [dlugosc];
    for (i=0; i<d; i++)
        tab[i]=NULL;
}

int graf::szukaj(int w1, int w2)
{
    lista * wsk = this->tab[w1];
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
        for(lista * w=tab[i] ; w!=NULL; w=w->nast)
        {
            plik << " -> [" << setw(2) << w->wierz << "] " << setw(3) << w->wagak;
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
        cout << "[" << setw(2) << i <<"]";
        for(lista * w=tab[i] ; w!=NULL; w=w->nast)
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
    for(lista * w=tab[pocz]; w!=NULL; w=w->nast)
        if(w->wierz==kon)
            return false;
    lista * nowy = new lista(pocz, dl, tab[kon]);
    tab[kon]= nowy;
    nowy = new lista(kon, dl, tab[pocz]);
    tab[pocz]= nowy;
    return true;
}

struct krawedz
{
    int w1, w2, waga;
    krawedz * nast;
};

class dijkstra
{
    public:
    krawedz * lista;
    int * kolory;
    int * wagi;
    int lw;

    dijkstra(graf *, int);

    void licz(int, int);
};

dijkstra::dijkstra(graf * arg, int m)
{
    this->lw=arg->d;

    this->wagi= new int [lw];

    for(int i=0; i<lw; i++)
        this->wagi[i]=m;

    this->lista=NULL;

    this->kolory= new int [lw];

    for(int i=0; i<lw;i++)
        this->kolory[i]=0;

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
}

void dijkstra::licz(int start, int m)
{
    int dl, dl_tmp, tmp, k;
    this->wagi[start]=0;
    krawedz * wsk = this->lista;
    for(int j=0; j<lw; j++)
    {
        dl=m;
        for(int i=0; i<lw; i++)
        {
            if(wagi[i]<dl && kolory[i]<2)
            {
                dl=wagi[i];
                k=i;
            }
        }
        kolory[k]=2;
        for(int i=0; i<lw; i++)
            if(kolory[i]==1)
                kolory[i]=0;
        for(int i=0; i<lw; i++)
        {
            dl_tmp=dl;
            if(kolory[i]>1)
                continue;
            while((this->kolory[wsk->w1] == this->kolory[wsk->w2] || this->kolory[wsk->w1]==1 || this->kolory[wsk->w2]==1 || this->kolory[wsk->w1]==3 || this->kolory[wsk->w2]==3) && wsk->nast!=NULL)
                {
                wsk=wsk->nast;
                }
            if(wsk->nast==NULL)
            {
                wsk=this->lista;
                continue;
            }
            tmp=(this->kolory[wsk->w1]!=2?wsk->w1:wsk->w2);
            dl_tmp+=wsk->waga;
            this->kolory[tmp]=1;
            if(dl_tmp <=this->wagi[tmp])
                this->wagi[tmp]=dl_tmp;
            wsk=this->lista;
            wsk=this->lista;
        }
    }
}

class bellman
{
    public:
    krawedz * lista;
    bool * kolory;
    int * wagi;
    int lw;
    list <int> wierz;

    bellman(graf *, int);

    void licz(int, int);
};

bellman::bellman(graf * arg, int m)
{
    this->lw=arg->d;

    this->wagi= new int [lw];

    for(int i=0; i<lw; i++)
        this->wagi[i]=m;

    this->lista=NULL;

    this->kolory= new bool [lw];

    for(int i=0; i<lw;i++)
        this->kolory[i]=false;

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
}


void bellman::licz(int start, int m)
{
    int tmp, tmp2,  dl, dl_tmp;
    bool czy;
    krawedz * wsk;
    this->wierz.push_front(start);
    this->kolory[start]=true;
    this->wagi[start]=0;

    while(!this->wierz.empty())
    {
        tmp=this->wierz.front();
        this->wierz.pop_front();
        dl=this->wagi[tmp];
        for(wsk = this->lista; wsk!=NULL; wsk=wsk->nast)
        {
            if(wsk->w1!=tmp && wsk->w2!=tmp)
                continue;
            dl_tmp=dl;
            dl_tmp+=wsk->waga;
            tmp2=(wsk->w1==tmp?wsk->w2:wsk->w1);
            if(dl_tmp < this->wagi[tmp2])
            {
                wagi[tmp2]=dl_tmp;
                czy=false;
                for(list <int>::iterator it=wierz.begin(); it!=wierz.end(); it++)
                {
                    if(*it==tmp2)
                        czy=true;
                }
                if(kolory[tmp2] && !czy)
                    wierz.push_front(tmp2);
                else if(!czy)
                    wierz.push_back(tmp2);
                kolory[tmp2]=true;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int d, p, dl, m, s;
    float czas1, czas2;
    clock_t start, stop;
    srand(time(NULL));

    d=10;                              //wielkosc grafu
    p=50;                               //procent zaplenienia grafu
    m=5;                                //zakres liczb
    s=0;                               //wierzcholek startowy


    graf * graf1 = new graf(d);
    graf1->uzupelnij(p,m);

    //graf1->zapis();
    //graf1->wyswietl();
    cout << endl;

    start=clock();
    dijkstra * dijkstra1= new dijkstra(graf1, m);
    dijkstra1->licz(s, m);
    stop=clock();

    czas1=stop - start;

    start=clock();
    bellman * bellman1= new bellman(graf1, m);
    bellman1->licz(s, m);
    stop=clock();

    czas2=stop - start;

    cout << "odleglosci: ";
    for(int i=0; i<d; i++)
        cout << dijkstra1->wagi[i] << " ";
    cout << endl << "Czas Dijkstra: " << czas1 << " ms" << endl;
    cout << endl << "odleglosci: ";
    for(int i=0; i<d; i++)
        cout << bellman1->wagi[i] << " ";
    cout << endl << "Czas Bellman: " << czas2 << " ms" << endl;


    fstream plik;                                       //odczyt i zapis pliku
    plik.open("statystyki LS.txt", ios::out|ios::app);
    plik << czas1 << endl << czas2 << endl;
    plik.close();
}
