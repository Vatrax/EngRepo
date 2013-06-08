/*	Wojciech Krzaczek
	Nr albumu: 184035
	Data ost. modyfikacji: 11.01.2011r. */
/* PRE: Program wczytuje obrazek *.pgm. */
/* POST: Program tworzy obraz ktory jest progowany, jest konturem lub negatywem wczytanego obrazu. W przypadku napotkanych problemow zwraca rodzaj bledu. */


#include<stdio.h>
#include<stdlib.h>

#include "funkcje.h"

int main(int argc, char ** argv) {
  int blad;
  
  w_opcje opcje; 
/*~~~~~~~~Opcje zmieniane przez funkcje przetwarzaj_opcje()*/
/*typedef struct {		   Wziete z "fukcje.h"
  FILE *plik_we, *plik_wy; 	   uchwyty do pliku wej. i wyj. //
  int negatyw,progowanie,konturowanie,wyswietlenie;      // opcje.. 1 - wykonanie, 0-nie wykonywac
  int w_progu;              	   wartosc progu dla opcji progowanie  
} w_opcje;*/

  t_obraz obraz; 
/*~~~~~~~Parametry obrazu oraz sama dynamicznie alokowana tablica zmieniane przez opcje  czytaj() oraz przez opcje przetwarzajace obraz
       int wymx;		  wymiar x
       int wymy;		  wymiar y
       int odcieni;		  Maksymalny odcien szarosci
       
       int *piksele;		  Wskaznik do dynamicznie alokowanej tablicy zawierajacej elementy pliku pgm   
       int *poczatek_piksele;	  Przechowuje adres pierwszego elementu dynamicznie alkowanej tablicy
             
       } t_obraz;*/

  fprintf(stderr,"przetwarzaj opcje = %d\n",blad = przetwarzaj_opcje(argc,argv,&opcje)); 	
	
	if(blad)						 /*blad=0 == brak bledu*/
	return blad;


fprintf(stderr,"switchuj opcje = %d\n",blad = switchuj_opcje(&opcje, &obraz));
if(blad) /*blad=0 == brak bledu*/
return blad;
 
free(obraz.piksele);

  return 0;
}
