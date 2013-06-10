#ifndef BLOKI_HH
#define BLOKI_HH
#include <cstdlib>
#include <iostream>



class Blok
{
public:
    virtual float Oblicz(float sygnal);
  //virtual ~Blok();
};

class BlokPotegujacy: public Blok
{
public:
    virtual float Oblicz(float sygnal);
};



class BlokPrzesunieciaPoziomu: public Blok
{
public:
    BlokPrzesunieciaPoziomu(int przesuniecie);
    virtual float Oblicz(float sygnal);
    float wartosc;
};


class BlokProstujacy: public Blok
{
public:
    virtual float Oblicz(float sygnal);
};


class BlokDyskryminacji: public Blok
{
public:
    BlokDyskryminacji(float liczba);
    virtual float Oblicz(float sygnal);
    float wartosc;
};


class BlokCalkowania: public Blok
{
private:
    float delta_czasu;
    float pamiec;
    float sygnal_old;
public:
    BlokCalkowania();
    virtual float Oblicz(float sygnal);
};

class BlokWzmocnienia: public Blok
{
public:
    BlokWzmocnienia(float liczba);
    virtual float Oblicz(float sygnal);
    float wartosc;
};

#endif
