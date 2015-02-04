/* Wojciech Krzaczek
nr indeksu: 184035
Termin zajec: Sroda 8:30
Lista: 6 Algorytm sztucznej inteligencji rozwiazujacy gre saper*/

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

struct elem
{
    int x;
    int y;
    elem * nast;
    elem(int, int, elem *);
};

elem::elem(int x, int y, elem * nast)
{
    this->x=x;
    this->y=y;
    this->nast=nast;
}

class stos
{
    public:
    elem * pierwszy;
    stos();
    void czysc();
    void dodaj(int, int);
};

stos::stos()
{
    this->pierwszy=NULL;
}

void stos::dodaj(int x, int  y)
{
    elem * nowy=new elem(x, y, pierwszy);
    pierwszy=nowy;
}

void stos::czysc()
{
    elem * tmp;
    while(pierwszy!=NULL)
    {
        tmp=pierwszy;
        pierwszy=pierwszy->nast;
        delete tmp;
    }
}

struct mapa
{
    char **tab;
    int x, y;
    int xobw, yobw;
    int b;
    mapa(int, int);
    void wyswietl();
    char nast_znak(char);
    int konwert(char);
    char konwert(int);
    void zmien(int, int);
    void uzupelnij(int);
    void uzupelnij_gracz();
    void zeruj();

};

mapa::mapa(int rozmiar_x, int rozmiar_y)
{
    this->x=rozmiar_x;
    this->y=rozmiar_y;

    this->xobw=x+2;
    this->yobw=y+2;

    this->b=0;

    this->tab= new char * [yobw];
    for(int i=0; i<yobw; i++)
        tab[i]=new char [xobw];

    for(int i=0; i<yobw; i++)
        for(int j=0;j<xobw; j++)
            tab[i][j]='0';

}

int mapa::konwert(char znak)
{
    char znaki[12] = {'0','1','2','3','4','5','6','7','8','.','x', '?'};

    for(int i=0;i<12;i++)
        if(znak==znaki[i])
            return i;
}

char mapa::konwert(int znak)
{
    char znaki[12] = {'0','1','2','3','4','5','6','7','8','.','x', '?'};
        return znaki[znak];
}

char mapa::nast_znak(char pop)
{
    char znaki[9] = {'0','1','2','3','4','5','6','7','8'};

    if(pop=='B')
        return pop;

    for(int i=0;i<9;i++)
       if(pop==znaki[i])
           return znaki[++i];
}

void mapa::zmien(int x, int y)
{
    int xx, yy;
    int maxx=this->y-1;
    int maxy=this->x-1;

    tab[xx=x-1][yy=y-1]=nast_znak(tab[xx][yy]);
    tab[xx=x-1][yy=y]=nast_znak(tab[xx][yy]);
    tab[xx=x-1][yy=y+1]=nast_znak(tab[xx][yy]);
    tab[xx=x+1][yy=y-1]=nast_znak(tab[xx][yy]);
    tab[xx=x+1][yy=y]=nast_znak(tab[xx][yy]);
    tab[xx=x+1][yy=y+1]=nast_znak(tab[xx][yy]);
    tab[xx=x][yy=y-1]=nast_znak(tab[xx][yy]);
    tab[xx=x][yy=y+1]=nast_znak(tab[xx][yy]);
    zeruj();
}

void mapa::wyswietl()
{
    for(int i=1; i-1<y; i++)
    {
        for(int j=1; j-1<x; j++)
            cout << tab[i][j] << " ";
        cout << endl;
    }
    cout<< endl;
}

void mapa::uzupelnij(int w)
{
    int wymiar=x*y;

    this->b=wymiar*w/100;
    int bomby=b;

    while(bomby>0)
    {
        int i=rand() % this->y+1;
        int j=rand() % this->x+1;
        if(tab[i][j]!='B')
        {
            tab[i][j]='B';
            bomby--;
        }
    }

    for(int i=0; i-1<this->y; i++)
        for(int j=0; j-1<this->x; j++)
            if(tab[i][j]=='B')
                zmien(i,j);
}

void mapa::zeruj()
{
    for(int i=0; i<yobw; i++)
    {
        tab[i][xobw-1]='0';
        tab[i][0]='0';
    }
    for(int i=0; i<xobw; i++)
    {
        tab[yobw-1][i]='0';
        tab[0][i]='0';
    }
}

void mapa::uzupelnij_gracz()
{
    for(int i=1; i-1<y; i++)
        for(int j=1;j-1<x; j++)
            tab[i][j]='.';
}

class AI
{
    public:
    mapa * uzupelniona;
    mapa * stan;
    int bomby;
    int x, y;
    stos * flagi;
    int licz_flagi;

    AI(mapa *, mapa *);
    int licz();
};

AI::AI(mapa * u, mapa * s)
{
    this->uzupelniona=u;
    this->stan=s;

    this->flagi=new stos;
    this->licz_flagi=0;

    this->bomby=uzupelniona->b;

    this->x=stan->x;
    this->y=stan->y;
}

int AI::licz()
{
    int operacje=0;
    int x_tmp, y_tmp;
    int bomby_tmp;
    int bomby_ile;
    int licznik;
    elem * wsk =this->flagi->pierwszy;
    while(bomby!=0)
    {
        for(int i=1; i-1<y; i++)
            for(int j=1; j-1<x; j++)
                {
                    if(stan->tab[i][j]=='.')
                    {
                        operacje++;
                        continue;
                    }
                    else if(stan->tab[i][j]=='x')
                    {
                        operacje++;
                        continue;
                    }
                    else if(stan->tab[i][j]=='?')
                    {
                        operacje++;
                        continue;
                    }
                    else if(stan->tab[i][j]=='0')
                    {
                        licznik=0;
                        for(int k=i-1; k<i+2; k++)
                            for(int l=j-1; l<j+2; l++)
                                if(stan->tab[k][l]=='.' || stan->tab[k][l]=='?')
                                {
                                    stan->tab[k][l]=uzupelniona->tab[k][l];
                                    licznik++;
                                }
                        if(licznik==0)
                            operacje++;
                    }
                    else
                    {
                        bomby_tmp=0;
                        bomby_ile=0;
                        licznik=0;
                        for(int k=i-1; k<i+2; k++)
                            for(int l=j-1; l<j+2; l++)
                                if(stan->tab[k][l]=='.' || stan->tab[k][l]=='?')
                                    bomby_tmp++;
                                else if(stan->tab[k][l]=='x')
                                    bomby_ile++;
                        if(bomby_tmp+bomby_ile==stan->konwert(stan->tab[i][j]))
                        {
                            for(int k=i-1; k<i+2; k++)
                                for(int l=j-1; l<j+2; l++)
                                    if(stan->tab[k][l]=='.' || stan->tab[k][l]=='?')
                                    {
                                        bomby--;
                                        stan->tab[k][l]='x';
                                        licznik++;
                                    }
                        }
                        else if(bomby_ile==stan->konwert(stan->tab[i][j]))
                        {
                            for(int k=i-1; k<i+2; k++)
                                for(int l=j-1; l<j+2; l++)
                                    if(stan->tab[k][l]=='.' || stan->tab[k][l]=='?')
                                    {
                                        stan->tab[k][l]=uzupelniona->tab[k][l];
                                        licznik++;
                                    }
                        }
                        else
                        {
                            for(int k=i-1; k<i+2; k++)
                                for(int l=j-1; l<j+2; l++)
                                    if(stan->tab[k][l]=='.')
                                    {
                                        stan->tab[k][l]='?';
                                        flagi->dodaj(k, l);
                                        licz_flagi++;
                                    }
                        }
                        if(licznik==0)
                            operacje++;
                    }
                }

    if(operacje== x * y)
    {
        if(this->licz_flagi!=0)
        {
            int tab[licz_flagi][2];
            wsk=this->flagi->pierwszy;
            for(int i=0; i<this->licz_flagi; i++)
            {
                tab[i][0]=wsk->x;
                tab[i][1]=wsk->y;
                wsk=wsk->nast;
            }
            int losuj;
            losuj=rand() % licz_flagi;
            y_tmp=tab[losuj][0];
            x_tmp=tab[losuj][0];
        }
        else
        {
            do
            {
                y_tmp=rand() % y +1;
                x_tmp=rand() % x +1;
            }
            while(stan->tab[y_tmp][x_tmp]!='.');
        }
        stan->tab[y_tmp][x_tmp]=uzupelniona->tab[y_tmp][x_tmp];
        if(stan->tab[y_tmp][x_tmp]=='B')
        {
            cout<< "PRZEGRANA!!! :(" << endl;
            return 1;
        }
    }
    operacje=0;
    licz_flagi=0;
    flagi->czysc();

    //stan->wyswietl();
    }
    if(bomby==0)
        cout << "WYGRANA!!! :)" << endl << endl;
}

int main(int argc, char *argv[])
{
    int x, y, w;

    srand(time(NULL));

    x=10000;
    y=10000;
    w=10;

    mapa * map = new mapa(x, y);
    map->uzupelnij(w);

    mapa * map_gracz = new mapa(x,y);
    map_gracz->uzupelnij_gracz();

    AI * gra = new AI(map,map_gracz);
    gra->licz();

    //map_gracz->wyswietl();

    //map->wyswietl();
}
