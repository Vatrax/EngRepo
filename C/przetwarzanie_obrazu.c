/*      Wojciech Krzaczek
        Nr albumu: 184035
        Data ost. modyfikacji: 29.11.2010r.*/

/* PRE: Program wczytuje obrazek *.pgm o maksymalnych wymiarach 512x512 pixeli*/
/* POST: Program tworzy obraz ktory jest progowany, jest konturem lub negatywem wczytanego obrazu - w zaleznosci od wybranej funkcji, a takze zapisuje go*/

/*dekalaracja stalych i zmiennych*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 512
#define DL_LINII 80

/*************************************************************************************************************************************/
int czytaj(FILE *p,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci) {
  char s[DL_LINII];
  int znak,koniec=0,i,j;

  /*sprawdzenie czy podano prawid³owy uchwyt pliku */
  if (p==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }
  if (fgets(s,DL_LINII,p)==NULL) koniec=1;
  /* Sprawdzenie "numeru magicznego - powinien byæ P2 */
  if ( (s[0]!='P') || (s[1]!='2') || koniec) {
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
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
  if (fscanf(p,"%d %d %d",wymx,wymy,szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  } 
  /* Sprawdzanie wymiarow */
    if (*wymx>MAX || *wymy>MAX) {
    fprintf(stderr,"Blad: Obraz ma za duze wymiary\n");
    return(0);
	}      
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (j=0;j<*wymy;j++) {
    for (i=0;i<*wymx;i++) {
      if (fscanf(p,"%d",&(obraz_pgm[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return *wymx**wymy;
}

/*************************************************************************************************************************************/
void wyswietl(char *n_pliku) {
  /* Wyswietlenie obrazu o zadanej nazwie 
     za pomoca programu "display"   */
  char polecenie[1024];
  strcpy(polecenie,"display ");
  strcat(polecenie,n_pliku);
  strcat(polecenie," &");  
  system(polecenie);
}
/*************************************************************************************************************************************/
/*funkcja odpowiadajaca za tworzenie negatywu i zapis*/
int negatyw(int *wymx, int *wymy, int *odcieni,int obraz[][MAX])
{
int i, j;
char nazwa[100];
FILE *plik;
printf("podaj nazwe do zapisania\n");
scanf("%s",nazwa);
plik=fopen(nazwa,"w");
fprintf(plik,"P2# %s\n%d\n%d\n%d",nazwa,*wymx,*wymy,*odcieni);
for(i=0;i<*wymy;i++) {
	fprintf(plik,"\n");
	for(j=0;j<*wymx;j++)
		fprintf(plik,"%d ",(*odcieni-obraz[j][i]));
}
wyswietl(nazwa);
fclose(plik);
return 0;
}

/*************************************************************************************************************************************/
/*funkcja odpowiadajaca za tworzenie progowania i zapis*/
int progowanie(int *wymx, int *wymy, int *odcieni,int obraz[][MAX])
{
int i, j;
char nazwa[100];
FILE *plik;
printf("podaj nazwe do zapisania\n");
scanf("%s",nazwa);
plik=fopen(nazwa,"w");
fprintf(plik,"P2\n #%s\n%d\n%d\n%d",nazwa,*wymx,*wymy,*odcieni);
for(i=0;i<*wymy;i++)
	{
	for(j=0;j<*wymx;j++)
		{
		fprintf(plik,"\n");
		if(obraz[j][i]>*odcieni/2)
			fprintf(plik,"%d ",(obraz[j][i]=*odcieni));
		else
			fprintf(plik,"%d ",0);
		}
	}
wyswietl(nazwa);
fclose(plik);
return 0;
}

/*************************************************************************************************************************************/
/*funkcja odpowiadajaca za tworzenie konturowania i zapis*/
int konturowanie(int *wymx, int *wymy, int *odcieni,int obraz[][MAX])
{
int i, j, a, b;
char nazwa[100];
FILE *plik;
printf("podaj nazwe do zapisania\n");
scanf("%s",nazwa);
plik=fopen(nazwa,"w");
fprintf(plik,"P2#%s\n\n%d\n%d\n%d",nazwa,(*wymx-1),(*wymy-1),*odcieni);
for(i=0;i<*wymy-1;i++)
	{
	fprintf(plik,"\n");
	for(j=0;j<*wymx-1;j++)
	{
		a=(obraz[j][i]-obraz[j+1][i]>0)?(obraz[j][i]-obraz[j+1][i]):(obraz[j+1][i]-obraz[j][i]);
		b=(obraz[j][i]-obraz[j][i+1]>0)?(obraz[j][i]-obraz[j][i+1]):(obraz[j][i+1]-obraz[j][i]);
		fprintf(plik,"%d ",(obraz[j][i]=a+b));
	}
	}
wyswietl(nazwa);
fclose(plik);
return 0;
}


/*************************************************************************************************************************************/
int main() {

  int wymx,wymy,odcieni;
  int obraz[MAX][MAX] ;
  int odczytano = 0;
  FILE *plik;
  char nazwa[100];
  int opcja;

  printf("Podaj nazwe pliku:\n");
  scanf("%s",nazwa);
  plik=fopen(nazwa,"r");
  
  if (plik != NULL)         /* co spowoduje zakomentowanie tego warunku */
    odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
  
  if (odczytano != 0)
    {
 do
	{
	/*menu programu*/
	printf("MENU\n");
	printf("co chcesz zrobic z obrazem?(wpisz odpowiednia liczbe)\n");
	printf("1. Negatyw\n");
	printf("2. Progowanie\n");
	printf("3. Konturowanie\n");
	printf("4. Zakonczenie dzialania programu\n");
	scanf("%d", &opcja);
	switch (opcja)
	{
	case 1:
		negatyw(&wymx,&wymy,&odcieni,obraz);
		break;
	case 2:
		progowanie(&wymx,&wymy,&odcieni,obraz);
		break;
	case 3:
		konturowanie(&wymx,&wymy,&odcieni,obraz);
		break;
	case 4:
		printf("dziekuje za skorzystanie z programu.\n");		
		break;
	default:
		printf("prosze wybrac liczbe od 1 do 4");
	return opcja;
	}
	}
while(opcja!=4);
	}
fclose(plik);
return 0;
}
