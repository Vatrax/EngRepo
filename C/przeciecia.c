/*	Wojciech Krzaczek
	Nr albumu: 184035
	Data ost. modyfikacji: 15.11.2010r. 
	Data utworznia: 10.11.2010r. */

/* Program wczytuje ciag liczb i zwraca liczbe przeciec zera */

/* Dzialanie programu dla danych wejsciowych:
   A. liczba w przedziale <-10,10>, rozna od 0	- program zwieksza licznik ilosci liczb, sprawdza czy nastepuje przeciecie.
   B. liczba 0					                - zwieksza licznik ilosci liczb.
   C. Liczba 99					                - sprawdza poprawnosc grupy i czestotliwosci, wyswietla liczbe przeciec i konczy dzialanie.
   D. reszta liczb	  			                - program je ignoruje.

   Warunek zakonczenia dzialania
   Wpisanie liczby 99 */

#include <stdio.h>                    /* deklaracja bibliotek */
#include <math.h>
#define STOP 99                       /* deklaracja stalych   */
#define WLK_GR 10
#define MIN_L -10
#define MAX_L 10
#define MIN_CZ 5
#define MAX_CZ 8

int main ()
{
int biez  = 0;                        /* deklaracja zmiennych */
int poprz = 0;
int czest = 0;
int liczb = 0;

do
{
printf("Podaj liczbe: ");			/*wczytywanie liczby*/
	scanf("%d", &biez);
	if(biez==0)				/* sprawdzenie czy jest rowna 0*/
	liczb++;
	else if(MIN_L<=biez&&biez<MAX_L)	/* sprawdzenie czy znajduje sie w przedziale dopuszczalnym*/
	{
		liczb++;
		if(poprz*biez<0)		/* sprawdzenie czy nastepuje przeciecie 0*/
		czest++;
		poprz = biez;
		else
		liczb++;
	}
}
while(biez!=STOP&&liczb<WLK_GR);		/* warunki zakonczenia dzialania*/

if(liczb<WLK_GR)
	printf("Niepelna grupa. Program zakonczy dzialanie.\n");	
else
{
	if(czest<MIN_CZ||czest>MAX_CZ)		/* sprawdzenie czy jest poprawna liczba przeciec*/
		printf("Niepoprawna liczba przeciec: %d\n", czest);
	else
		printf("Liczba przeciec: %d\n", czest);		/* wyswietlenie l. przeciec*/
		main();
}
return 0;
}
