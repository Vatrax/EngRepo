#include "bloki.hh"

using namespace std;


// oblicza wyjscie w zaleznosci od wartosci wejscia                                                       *

float Blok::Oblicz(float sygnal)
{
    return sygnal;
}



// metoda potegujaca wejscie

float BlokPotegujacy::Oblicz(float sygnal)
{
    sygnal = sygnal*sygnal;
    return sygnal;
}



// metoda przesuwania poziomu wejscia

BlokPrzesunieciaPoziomu::BlokPrzesunieciaPoziomu(int przesuniecie)
{
    wartosc = przesuniecie;
}



// metoda przesuwania poziomu wejscia


float BlokPrzesunieciaPoziomu::Oblicz(float sygnal)
{
    sygnal = sygnal + wartosc;
    return sygnal;
}




// metoda prostowania wejscia

float BlokProstujacy::Oblicz(float sygnal)
{
    return sygnal*(sygnal>0 ? 1 : -1);
}



BlokDyskryminacji::BlokDyskryminacji(float liczba)
{
    wartosc = liczba;
}


// metoda dyskryminacji wejscia


float BlokDyskryminacji::Oblicz(float sygnal)
{
    return (sygnal < wartosc ? 0 : 1);
}

BlokWzmocnienia::BlokWzmocnienia(float liczba)
{
   wartosc = liczba;
}

float BlokWzmocnienia::Oblicz(float sygnal)
{
   return sygnal*wartosc;
}

BlokCalkowania::BlokCalkowania(): pamiec()
{
    delta_czasu = 0.02;
}


// metoda calkujaca wejscie

/*float BlokCalkowania::Oblicz(float sygnal)
{

    float suma;
    float sygnal_old;

    if (int temp=0){
        suma=0;
        sygnal_old=0;
        suma+=((sygnal_old + sygnal)/2) * (delta_czasu);
        sygnal_old=sygnal;
        temp=1;
    }
    else{
       suma+=((sygnal_old + sygnal)/2) * (delta_czasu);
    }

    return suma;
}
*/
float BlokCalkowania::Oblicz(float sygnal)
{
   pamiec+=((sygnal+sygnal_old)/2)*delta_czasu;
   sygnal_old=sygnal;
   return pamiec;
}
