#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#include "funkcje.h"

#define DL_LINII 80

#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow dla przetwarzaj opcje*/
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4

#define OK 0                  		 /* w przypadku braku bledow */
#define B_BRAKUCHWYTU_ODCZYT -1    	 /* kody bledow dla switchuj opcje */
#define B_PLIKNIEPGM   -2
#define B_BRAKWYMIAROW_SZAROSCI  -3
#define B_NIEWLASCIWEWYMIARY   -4

#define B_BRAKUCHWYTU_ZAPIS -5

/* PRE: Program wczytuje uchwyt do pliku */
/* POST: Program sprawdza czy to plik o rozszerzeniu *.pgm, czy ma poprawnie zapisane wymiary i stopnie szarosci.
         Jesli wszystko jest poprawnie to zapisuje go w tablicy obraz->piksele */
int czytaj(FILE *p, t_obraz *obraz) {
  char s[DL_LINII];
  int znak,koniec=0,i,j;

  /*sprawdzenie czy podano prawid³owy uchwyt pliku */
  if (p==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(-1);
  }
  if (fgets(s,DL_LINII,p)==NULL) koniec=1;
  /* Sprawdzenie czy zaczyna sie od P2 - czy plik ma rozszerzenie *.pgm */
  if ( (s[0]!='P') || (s[1]!='2') || koniec) {
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(-2);
  }
  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(p))=='#') {
      if (fgets(s,DL_LINII,p)==NULL) koniec=1;
    }  else {
      ungetc(znak,p);
    }
  } while (! koniec && znak=='#');

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(p,"%d %d %d",&obraz->wymx,&obraz->wymy,&obraz->odcieni)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(-3);
  }

/*Dynamiczna alokacja tablicy jednowymiarowej ~*/

obraz->piksele = malloc(obraz->wymx * obraz->wymy * sizeof(int));

  /* Pobranie obrazu i zapisanie w tablicy obraz->piksele*/
  for (j=0;j<obraz->wymy;j++) {
    for (i=0;i<obraz->wymx;i++) {
      if (fscanf(p,"%d",&obraz->piksele[i+obraz->wymx*j])!=1) { 
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(-4);
      }
    }
  }

	fclose(p);
  return 0;
}

/* PRE: --- */
/* POST: zapisanie obrazu do pliku */
int zapisz(FILE *p, t_obraz *obraz)
 {

int i, n;

if (p==NULL)
{
fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
return (-5);
}

fprintf(p, "P2\n");   /*Wpisanie do pliku, elementów niezbêdnych dla pliku pgm*/
fprintf(p,"%d\n", obraz->wymx);
fprintf(p,"%d\n", obraz->wymy);
fprintf(p,"%d\n", obraz->odcieni);


for(i=0; i<obraz->wymx*obraz->wymy; i++)
fprintf(p, "%d\t", *(obraz->piksele+i));
fclose(p);
  return 0;
}

/* PRE: --- */
/* POST: Program kolejno zastepuje kazdy piksel roznica maksymalnej szarosci i stopnia szarosci danego piksela */
int negatyw(t_obraz *obraz)
{
	int i;
	for(i=0; i<obraz->wymx*obraz->wymy; i++)
		{
			obraz->piksele[i] = obraz->odcieni - obraz->piksele[i];

		}

  	return 0;
}

/* PRE: Program wczytuje zmienna prog */
/* POST: Program sprawdza piksele czy maja wieksza szarosc od wczytanego progu.
	 Jesli sa ciemniejsze to zamieniane sa na maksymalna szarosc, w innym w wypadku na minimalna */
int progowanie(t_obraz *obraz, int prog)
{

int i;

for(i=0; i<obraz->wymx*obraz->wymy; i++)
{
	if(*(obraz->piksele+i) > prog)
	*(obraz->piksele+i) = obraz->odcieni;
	else
	*(obraz->piksele+i) = 0;

}

  	return 0;
}


/* PRE: --- */
/* POST: Program  przyciemnia piksele ktore sa podobne do otoczenia, a rozjasnia te ktore sie od neigo roznia*/
int konturowanie(t_obraz *obraz)
{

int i, j;

 for(i=0; i<(obraz->wymx-1); i++)
	for(j=0; j<(obraz->wymy-1);j++)
	{
obraz->piksele[i+obraz->wymx*j]= abs(obraz->piksele[i+obraz->wymx*j+1]-obraz->piksele[i+obraz->wymx*j]) +
abs(obraz->piksele[i+obraz->wymx*(j+1)]-obraz->piksele[i+obraz->wymx*j]);

    	if(obraz->piksele[i+obraz->wymx*j]>obraz->odcieni)       /*Zeby obraz->piksele[i+obraz->wymx*j] nie mialo wiekszej wartosci niz maksymalna szarosc*/
            obraz->piksele[i+obraz->wymx*j]=obraz->odcieni;
        }

  	return 0;
}


/* PRE: --- */
/* POST: Program zapisuje tymczasowo obraz pod nazwa temppgm.tmp, wyswietla go a nastepnie usuwa */
void wyswietl(t_obraz *obraz) {

FILE *temp;

temp=fopen("temppgm.tmp","w");

zapisz(temp, obraz);

  system("display temppgm.tmp &");
printf("\n\nZamknij wyswietlony obrazek, a nastepnie wcisnij klawisz enter."); /*Aby unikac usuwania pliku w uzyciu, */
getchar();
printf("\n\n");
  system ("rm temppgm.tmp &");

}

/*******************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor   */
/* PRE:                                                */
/*      poprawnie zainicjowany argument wybor (!=NULL) */
/* POST:                                               */
/*      "wyzerowana" struktura wybor wybranych opcji   */
/*******************************************************/

void wyzeruj_opcje(w_opcje * wybor) {
  wybor->plik_we=NULL;
  wybor->plik_wy=NULL;
  wybor->negatyw=0;
  wybor->konturowanie=0;
  wybor->progowanie=0;
  wybor->wyswietlenie=0;
}

/********************************************************************************/
/*Funkcja sprawdzaj±ca opcje zapisane w strukturze opcje			*/
/*oraz wykonujaca odpowiednie operacje						*/
/*PRE:										*/
/*	Poprawnie zainicjowana struktura opcje					*/
/*POST:										*/
/*	Wywolanie odpowiednich funkcji programu					*/
/*UWAGA: 									*/
/*Odpowiednie funkcje wywolywane sa Niezaleznie od				*/
/*kolejnosci, jaka zostala podana podczas wywolywania programu.			*/
/*Ta kolejnosc to:								*/
/*  wczytanie z pliku,negatyw,progowanie,konturowani, zapisanie,wyswietlenie	*/
/********************************************************************************/
int switchuj_opcje(w_opcje *wybor, t_obraz *obraz) {

int blad;

if(blad=czytaj(wybor->plik_we, obraz)) /*Warunek jest juz sprawdzany w przetwarzaj_opcje()*/
{
fprintf(stderr,"czytaj = %d\n",blad);
return blad;
}


if(wybor->negatyw==1)
if(blad=negatyw(obraz))
{
fprintf(stderr,"negatyw = %d\n",blad);
return blad;
}

if(wybor->progowanie==1)
if(blad=progowanie(obraz, wybor->w_progu))
{
fprintf(stderr,"progowanie = %d\n",blad);
return blad;
}

if(wybor->konturowanie==1)
if(blad=konturowanie(obraz))
{
fprintf(stderr,"konturowanie = %d\n",blad);
return blad;
}


if(wybor->plik_wy!=NULL)
if(blad=zapisz(wybor->plik_wy, obraz))
{
 fprintf(stderr,"zapisz = %d\n",blad);
return blad;
}

if(wybor->wyswietlenie==1)
wyswietl(obraz);		/*Funkcja nic nie zwraca. Zreszta zwracanie wartosci
				  przez funkcje negatyw progowanie konturowanie
				  rowniez jest zbedne..				   */


return 0;
}

/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu                                    */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-r] [-d] }  */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         wybor -  struktura z informacjami o wywolanych opcjach       */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wybór, do tego ustawia na 1 pola, ktore            */
/*	poprawnie wystapily w linii wywolania programu,                 */
/*	pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;     */
/*	zwraca wartosc W_OK, gdy wywolanie bylo poprawne                */
/*	lub kod bledu zdefiniowany stalymi B_* (<0)                     */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor) {
  int i, prog;
  char *nazwa_pliku_we, *nazwa_pliku_wy;

  wyzeruj_opcje(wybor);
  wybor->plik_wy=stdout;        /* na wypadek gdy nie podano opcji "-o" */

  for (i=1; i<argc; i++) {
    if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
      return B_NIEPOPRAWNAOPCJA; 
    switch (argv[i][1]) {
    case 'i': {                 /* opcja z nazwa pliku wejsciowego */
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	nazwa_pliku_we=argv[i];
	if (strcmp(nazwa_pliku_we,"-")==0) /* gdy nazwa jest "-"        */
	  wybor->plik_we=stdin;            /* ustwiamy wejscie na stdin */
	else                               /* otwieramy wskazany plik   */
	  wybor->plik_we=fopen(nazwa_pliku_we,"r");
      } else 
	return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
      break;
    }
    case 'o': {                 /* opcja z nazwa pliku wyjsciowego */
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	nazwa_pliku_wy=argv[i];
	if (strcmp(nazwa_pliku_wy,"-")==0)/* gdy nazwa jest "-"         */
	  wybor->plik_wy=stdout;          /* ustwiamy wyjscie na stdout */
	else                              /* otwieramy wskazany plik    */
	  wybor->plik_wy=fopen(nazwa_pliku_wy,"w");
      } else 
	return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
      break;
    }
    case 'p': {
      if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
	if (sscanf(argv[i],"%d",&prog)==1) {
	  wybor->progowanie=1;
	  wybor->w_progu=prog;
	} else
	  return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
      } else 
	return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
      break;
    }
    case 'n': {                 /* mamy wykonac negatyw */
      wybor->negatyw=1;
      break;
    }
    case 'k': {                 /* mamy wykonac konturowanie */
      wybor->konturowanie=1;
      break;
    }
    case 'd': {                 /* mamy wyswietlic obraz */
      wybor->wyswietlenie=1;
      break;
    }
    default:                    /* nierozpoznana opcja */
      return B_NIEPOPRAWNAOPCJA;
    } /*koniec switch */
  } /* koniec for */

  if (wybor->plik_we!=NULL)     /* ok: wej. strumien danych zainicjowany */
    return W_OK;/*******************************************************/
  else 
    return B_BRAKPLIKU;         /* blad:  nie otwarto pliku wejsciowego  */
}


