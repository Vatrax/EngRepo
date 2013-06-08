// l2witi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <time.h>

using namespace std;

void algorythm( char * nazwa_in, char * nazwa_out)
{
	unsigned int n, N;
	
	ifstream data_in (nazwa_in);
	data_in >> n;

	register int *p = new int[n];
	register int *w = new int[n];
	register int *d = new int[n];

	for(int i = 0; i<n; i++)
		data_in >> p[i] >> w[i] >> d[i];

	data_in.close();

	N=1<<n;

	unsigned int **kolejnosc= new unsigned int * [N];
	for(int i=0; i<N; i++)
		kolejnosc[i]=new unsigned int [n];

	for(int i=0; i<N; i++)
		for(int j=0; j<n; j++)
			kolejnosc[i][j]=0;

	int *kary = new int[N];
	for(int i=1; i<N; i++)
		kary[i]=0xFFFFFFF;
	kary[0]=0;

	unsigned int Cmax, pos;
	signed int tmp;

	for(int i = 1; i < N; i++)
	{
		pos = i;
		Cmax = 0;
		for(int j = 0; j<32; j++, pos>>=1)
			if((pos&1)==1)
				Cmax += p[j];
		pos=i;
		for(int j = 0; j<32; j++, pos>>=1)
			if((pos&1)==1)
			{
				tmp=(Cmax-d[j])*w[j];
				tmp=max(tmp,0);
				tmp+=kary[i-(1<<j)];
				if(kary[i]>tmp)
				{
					kary[i]=tmp;
					
					int k=0;
					for(; kolejnosc[i-(1<<j)][k]!=0;k++)
						kolejnosc[i][k]=kolejnosc[i-(1<<j)][k];
					kolejnosc[i][k]=j+1;
				}
			}
	}

	/*cout << kary[N-1] << endl;
	for(int i=0; i<n;i++)
		cout << kolejnosc[N-1][i] << " ";
	cout << endl;*/

	ofstream data_out (nazwa_out);
	data_out << kary[N-1] << endl;
	for(int i=0; i<n;i++)
		data_out << kolejnosc[N-1][i] << " ";

	data_out.close();

	delete [] p;
	delete [] w;
	delete [] d;
	delete [] kary;
	delete [] kolejnosc;

}


int _tmain(int argc, _TCHAR* argv[])
{
	clock_t start, koniec;
	start=clock();
	algorythm("data10.txt","out10.txt");
	algorythm("data11.txt","out11.txt");
	algorythm("data12.txt","out12.txt");
	algorythm("data13.txt","out13.txt");
	algorythm("data14.txt","out14.txt");
	algorythm("data15.txt","out15.txt");
	algorythm("data16.txt","out16.txt");
	algorythm("data17.txt","out17.txt");
	algorythm("data18.txt","out18.txt");
	algorythm("data19.txt","out19.txt");
	algorythm("data20.txt","out20.txt");
	koniec=clock();
	cout<< koniec-start << " ms" << endl;
	system("pause");
}