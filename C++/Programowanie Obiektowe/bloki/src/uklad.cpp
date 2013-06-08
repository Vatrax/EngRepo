#include "uklad.hh"

using namespace std;



//konstruktor
Uklad::Uklad(): sygnal_max(), sygnal_min(), czas_max(), czas_min(), plik_wyjscia(PLIK_WYJSCIA), plik_wejscia(PLIK_WEJSCIA){}


//dopasowanie wykresu
void Uklad::DopasujWykres(float SygWyj, float czas)
{
    if (czas < czas_min) czas_min = czas;
    if (czas > czas_max) czas_max = czas;
    if (SygWyj < sygnal_min) sygnal_min = SygWyj;
    if (SygWyj > sygnal_max) sygnal_max = SygWyj;
}

//zmiana parametrow wyswietlania
void Uklad::ZmienWyswietlanie()
{
    float X1, X2, Y1, Y2;

    X1 = czas_min - 0.5;
    X2 = czas_max + 0.5;
    Y1 = sygnal_min - 0.5;
    Y2 = sygnal_max + 0.5;

    Lacze.DodajNazwePliku( plik_wyjscia.c_str() ).ZmienSposobRys(PzG::SR_Ciagly).ZmienSzerokosc(3);
    Lacze.Inicjalizuj();
    Lacze.ZmienTrybRys(PzG::TR_2D);
    Lacze.UstawZakresX(X1,X2);
    Lacze.UstawZakresY(Y1,Y2);

}


void Uklad::WyswietlWykres()
{
    ZmienWyswietlanie();
    Lacze.Rysuj();
}



void Uklad::DodajBlok(char ID, int wartosc)
{
    BlokPotegujacy *bPotegujacy;
    BlokPrzesunieciaPoziomu *bPrzesuniecia;
    BlokProstujacy *bProstujacy;
    BlokCalkowania *bCalkowania;
    BlokDyskryminacji *bDyskryminacji;
    BlokWzmocnienia *bWzmocnienia;

    switch (ID)
    {
    case 'G':
        bPotegujacy = new BlokPotegujacy;
        bloki.push_back(bPotegujacy);
        break;

    case 'P':
        bPrzesuniecia = new BlokPrzesunieciaPoziomu(wartosc);
        bloki.push_back(bPrzesuniecia);
        break;

    case 'S':
        bProstujacy = new BlokProstujacy;
        bloki.push_back(bProstujacy);
        break;

    case 'C':
        bCalkowania = new BlokCalkowania;
        bloki.push_back(bCalkowania);
        break;

    case 'D':
        bDyskryminacji = new BlokDyskryminacji(wartosc);
        bloki.push_back(bDyskryminacji);
        break;

    case 'W':
        bWzmocnienia = new BlokWzmocnienia(wartosc);
        bloki.push_back(bWzmocnienia);
        break;
    }
}



float Uklad::Rozpocznij(float SygWej)
{
    Blok *A;
    float y;
    y = SygWej;

//petla przepuszczajaca sygnal przez wszystkie bloki na liscie
    for (list<Blok*>::const_iterator Iter = bloki.begin();Iter != bloki.end();++Iter)
    {
        A = *Iter;
        y = A->Oblicz(y);
    }
    return y;
}

void Uklad::WczytajWejscie()
{
    float SygWej, SygWyj;
    float Czas;
    bool CzyPierwszy=1;


    ifstream PlikWejscia;
    PlikWejscia.open(plik_wejscia.c_str());

    ofstream PlikWyjscia;
    PlikWyjscia.open( plik_wyjscia.c_str() , ios::trunc);
    PlikWyjscia.close();

//odczytywanie kolejnych wierszy wejscia
    while (!PlikWejscia.eof() && PlikWejscia.good())
    {
        PlikWejscia>>Czas;
        PlikWejscia>>SygWej;

//rozpoczecie obliczania sygnalu wyjsciowego
        if (!PlikWejscia.eof())
        {
            SygWyj = Rozpocznij(SygWej);

//zapisuje dane pierwszej wartosci sygnalu dla ustawienia wykresu
            if (CzyPierwszy)
            {
                sygnal_max = SygWyj;
                sygnal_min = SygWyj;
                czas_max = Czas;
                czas_min = Czas;
                CzyPierwszy = 0;
            }

//otwarcie pliku wyjscia i dopisanie obliczonego sygnalu
            ofstream PlikWyjscia;
            PlikWyjscia.open( plik_wyjscia.c_str() , ios::app);
            PlikWyjscia<<Czas<<" "<<SygWyj<<endl;
            PlikWyjscia.close();

//sprawdza czy nalezy zmienic skale wykresu
            DopasujWykres(SygWyj,Czas);
        }

    }

    PlikWejscia.close();
}

void Uklad::ZmienWejscie(string wejscie)
{
    plik_wejscia = wejscie;
}


void Uklad::ZmienWyjscie(string wyjscie)
{
    plik_wyjscia = wyjscie;
}
