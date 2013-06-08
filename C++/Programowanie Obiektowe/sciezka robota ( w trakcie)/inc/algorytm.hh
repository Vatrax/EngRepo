#ifndef _ALGORYTM_
#define _ALGORYTM_
#include "robot.hh"
#include "cel.hh"
#include "start.hh"
#include "przeszkoda.hh"
#include <vector>
#include <iostream>
#include <fstream>
#define NAZWAPLIKU_start   "dat/start.xyr" 
#define NAZWAPLIKU_cel "dat/cel.xyr" 
#define NAZWAPLIKU_robot     "dat/robot.xyr"
#define NAZWAPLIKU_przeszkody    "dat/przeszkody.xyr"
#define NAZWAPLIKU_sciezka    "dat/sciezka.xy"

using namespace std;

class algorytm
{
	public:
	algorytm(){przemieszczenie=kroki=kroki_wyk=0;}
	///////////////////////// algorytm //////////////////////////////////
	void stan();
	void licz();
	void wczytywanie_danych();
	//////////////////////////////////////////////////////////////////////
	
	///////////////// przeszkody /////////////////////////////////////////
	void dodaj_przeszkode(float x, float y, int ladunek);
	void dodaj_przeszkode_z_pliku(float x, float y, int ladunek);
	void usun_przeszkode(int i);
	void usun_ostatnia_przeszkode();
	void edytuj_przeszkode(float x, float y, int rozmiar, unsigned int i);
	float wylicz_potencjal_sceny(float x, float y);
	//////////////////////////////////////////////////////////////////////
	
	//////////////////////// cel i start /////////////////////////////////
	void ustal_ladunek_celu(int ladunek);
	void ustal_wsprz_startu(float x, float y);
	void ustal_wsprz_celu(float x, float y);
	void wez_wsprz_celu();
	void przywroc_pozycje_startu();
	//////////////////////////////////////////////////////////////////////
	
	//////////////////////// dane algorytmu /////////////////////////////
	void ustal_przemieszczenie(int i);
	int wez_przemieszczenie();
	void ustal_kroki(int kroki);
	int wez_kroki();
	//////////////////////////////////////////////////////////////////////	
	private:
	int przemieszczenie, kroki, kroki_wyk;
	robot r;
	vector< przeszkoda >przeszkody;
	start s;
	cel c;
};

#endif
