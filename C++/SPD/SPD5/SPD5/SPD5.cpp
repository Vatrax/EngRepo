// SPD5.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>

using namespace std;



struct proces
{
	unsigned int r;		//wyprzedzanie
	unsigned int p;		//zadanie
	unsigned int q;		//opoznienie
	unsigned int ID;		//identyfikator
};

unsigned int sumowanie(list<proces> lista)
{
	unsigned int suma=0, suma_tmp=0;
	for(list<proces>::iterator it=lista.begin();it!=lista.end();it++)
	{
		if(it->r>=suma)
			suma=it->r;
		suma+=it->p;
	}
	for(list<proces>::reverse_iterator it=lista.rbegin();it!=lista.rend();it++)
	{
		if(it->q>=suma_tmp)
			suma_tmp=it->q;
		suma_tmp+=it->p;
	}
	suma+=suma_tmp;
	for(list<proces>::iterator it=lista.begin();it!=lista.end();it++)
		suma-=it->p;
	return suma;
}

bool comp_r(proces p1, proces p2)
{
	return (p1.r<p2.r);
}

bool comp_q(proces p1, proces p2)
{
	return (p1.q>p2.q);
}

unsigned int schrage(list<proces> &r)
{
	unsigned int k=0;
	list<proces> q, procesy;

	r.sort(comp_r);

	while(!r.empty() || !q.empty())
	{
		for(list<proces>::iterator it=r.begin(); it!=r.end();)
			if(it->r<=k)
			{
				q.push_back(*it);
				it=r.erase(it);
			}
			else
				break;
		q.sort(comp_q);

		if(!q.empty())
		{
			list<proces>::iterator it=q.begin();
			procesy.push_back(*it);
			k+=it->p;
			q.pop_front();
		}
		else
			k++;
	}

	r=procesy;
	return sumowanie(r);
}

unsigned int schrage_Ptmn(list<proces> r)
{
	unsigned int k=0, lenght=0;
	
	list<proces> q;
	
	r.sort(comp_r);

	while(!r.empty() || !q.empty())
	{
		for(list<proces>::iterator it=r.begin(); it!=r.end();)
			if(it->r<=k)
			{
				q.push_back(*it);
				it=r.erase(it);
			}
			else
				break;
		q.sort(comp_q);

		if(!q.empty())
		{
			list<proces>::iterator it=q.begin();
			it->p--;
			if(it->p==0)
			{
				lenght=max((unsigned int) k+it->q, (unsigned int) lenght);
				q.pop_front();
			}
		}
		k++;
	}
	lenght++;

	return lenght;
}

unsigned int b_search(list<proces> lista)
{
	unsigned int ID, Cmax_tmp = 0;
	for(list<proces>::reverse_iterator it=lista.rbegin(); it!=lista.rend(); it++)
	{
		if(it->q>=Cmax_tmp)
		{
			Cmax_tmp=it->q; 
			ID=it->ID;
		}
		Cmax_tmp+=it->p;
	}
	return ID;
}

unsigned int a_search(list<proces> lista)
{
	unsigned int ID, Cmax_tmp = 0;
	for(list<proces>::iterator it=lista.begin();it!=lista.end(); it++)
	{
		if(it->r>=Cmax_tmp)
		{
			Cmax_tmp=it->r; 
			ID=it->ID;
		}
		Cmax_tmp+=it->p;
	}
	return ID;
}

int c_search(list<proces> lista, unsigned int a, unsigned int b)
{
	unsigned int q, Cmax_tmp = 0;
	list<proces>::reverse_iterator it=lista.rbegin();
	while(it->ID!=b)
		it++;
	q=it->q;
	for(;it->ID!=a; it++)
		if(it->q<q)
			return it->ID;
	return -1;
}

unsigned int r_min(list<proces> lista, unsigned int start, unsigned int end)
{
	unsigned int r=0xFFFF;
	list<proces>::iterator it=lista.begin();
	while(it->ID!=start)
		it++;
	do
	{
		it++;
		r=min(r, it->r);
	}	while(it->ID!=end);
	return r;
}

unsigned int p_sum(list<proces> lista, unsigned int start, unsigned int end)
{
	unsigned int p=0;
	list<proces>::iterator it=lista.begin();
	while(it->ID!=start)
		it++;
	do
	{
		it++;
		p+=it->p;
	}		while(it->ID!=end);
	return p;
}

unsigned int q_min(list<proces> lista, unsigned int start, unsigned int end)
{
	unsigned int q=0xFFFF;
	list<proces>::iterator it=lista.begin();
	while(it->ID!=start)
		it++;
	do
	{
		it++;
		q=min(q, it->q);

	}		while(it->ID!=end);
	return q;
}

unsigned int Carlier(list<proces> &procesy, unsigned int UB)
{
	unsigned int a_ID, b_ID, LB, U, UB_tmp, r_blok, p_blok, q_blok, r_tmp, q_tmp;
	int c_ID=-1;
	U=schrage(procesy);
	UB=U;
	a_ID=a_search(procesy);					//5->1
	b_ID=b_search(procesy);					//13->11
	c_ID=c_search(procesy, a_ID, b_ID);		//2->9
	if(c_ID==-1)
		return UB;
	r_blok=r_min(procesy, c_ID, b_ID);
	p_blok=p_sum(procesy, c_ID, b_ID);
	q_blok=q_min(procesy, c_ID, b_ID);

	list<proces>::iterator it=procesy.begin();
	while (it->ID!=c_ID)
		it++;

	r_tmp=it->r;
	q_tmp=it->q;

	it->r=max(it->r, r_blok+p_blok);
	LB=schrage_Ptmn(procesy);
	if(LB<UB)
	{
		UB_tmp=Carlier(procesy, UB);
		if(UB_tmp!=0 && UB_tmp<UB)
			UB=UB_tmp;
	}

	it=procesy.begin();
	while (it->ID!=c_ID)
		it++;
	it->r=r_tmp;
	//==============================================================
	it->q=max(it->q, q_blok+p_blok);

	LB=schrage_Ptmn(procesy);
	if(LB<UB)
	{
		UB_tmp=Carlier(procesy, UB);
		if(UB_tmp!=0 && UB_tmp<UB)
			UB=UB_tmp;
	}
	it=procesy.begin();
	while (it->ID!=c_ID)
		it++;
	it->r=r_tmp;
	it->q=q_tmp;

	return UB;
}


int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int n;
	unsigned int UB=INT_MAX;

	fstream plik;
	plik.open("data01.txt", std::ios::in );
	plik >> n;
	list<proces> procesy;

	for(int i=0; i<n; i++)
	{
		proces *nowy= new proces();
		plik >> nowy->r >> nowy->p >> nowy->q;
		nowy->ID=i+1;
		procesy.push_front(*nowy);
		delete nowy;
	}
	plik.close();

	UB=Carlier(procesy, UB);
		
	cout << UB << endl;
	plik.open("out.txt", ios::out|ios::app);
	plik.close();
	system("pause");
}