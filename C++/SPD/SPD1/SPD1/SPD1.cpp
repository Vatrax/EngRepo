// SPD1.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

struct proces
{
	short r;		//wyprzedzanie
	short p;		//zadanie
	short q;		//opoznienie
	short No;
};

int sumowanie(list<proces> lista)
{
	unsigned int suma=0, suma_tmp=0;
	for(list<proces>::iterator it=lista.begin();it!=lista.end();it++)
	{
		if(it->r>=suma)
			suma=it->r;
		suma+=it->p;
		cout << suma << endl;
	}
	/*for(list<proces>::iterator it=lista.end();it!=lista.begin();it--)
	{
		if(it->q>=suma_tmp)
			suma_tmp=it->q;
		suma_tmp+=it->p;
	}*/
	suma+=suma_tmp;
	for(list<proces>::iterator it=lista.begin();it!=lista.end();it++)
		suma-=it->p;
	return suma;
}

bool comp_r(proces p1, proces p2)
{
	if(p1.r>=p2.r)
		return false;
	else
		return true;
}

bool comp_q(proces p1, proces p2)
{
	if(p1.q<=p2.q)
		return false;
	else
		return true;
}


int _tmain(int argc, _TCHAR* argv[])
{
	static short n, m;
	fstream plik;
	plik.open("in07.txt", std::ios::in );
	plik >> n >> m;
	list<proces> procesy;
	list<proces> procesy2;

	for(short i=0;i<n;i++)
	{
		proces *nowy= new proces();
		plik >> nowy->r >> nowy->p >> nowy->q;
		nowy->No=i+1;
		nowy->r<=nowy->q?procesy2.push_front(*nowy):procesy.push_front(*nowy);
		delete nowy;
	}
	plik.close();

	procesy.sort(comp_q);
	procesy2.sort(comp_r);

	list<proces>::iterator it=procesy.begin();
	procesy.splice(it, procesy2);

	//for(it=procesy.begin(); it!=procesy.end();it++)
		//cout << it->No << " " << it->r << " " << it->p << " " << it->q << endl;

	plik.open("out07.txt", std::ios::out );
	plik << n << " " << m << endl;
	for(it=procesy.begin(); it!=procesy.end();it++)
		plik << it->No << " ";
	plik << endl;
	plik << sumowanie(procesy);
	
	plik.close();
	system("PAUSE");
}