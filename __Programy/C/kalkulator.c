/* Wojciech Krzaczek											*/
/* Numer indeksu: 184035										*/
/* Program: Kalkulator RPN										*/
/* Data ostatniej modyfikacji: 24.01.2011								*/

/* PRE: program wczytuje liczby, a takze znaki, ktorym sa przydzielone odpowiednie funkcje programu	*/
/* POST: Program wykonuje nastepujace operacje:			  					*/
/*	- odejmowanie											*/
/*	+ dodawanie											*/
/*	* mnozenie											*/
/*	/ dzielenie											*/
/*		# usuwa pierwszy element stosu								*/
/*		q zamyka program									*/
/*		$ zamienia miejscami 2 pierwsze elementy na stosie					*/
/*		& duplikuje pierwszy (z gory) element na stosie						*/
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ROZMIAR 8
typedef struct elem
{
int dana;
struct elem *nast;
} t_elem;
 
void push(t_elem **lista,int wartosc) {
        t_elem *pomoc;
 
        pomoc=(t_elem*) malloc (sizeof(t_elem));
        pomoc->dana=wartosc;
        pomoc->nast=*lista;
 
        *lista=pomoc;
}
/* push: Dodaje nowy element na szczyt stosu */
int pop(t_elem **lista)
{
        t_elem *wskaz;
        int wartosc;
 
        if (lista==NULL)
                fprintf(stderr,"Stos pusty");
        else {
                wartosc=(*lista)->dana;
                wskaz=*lista;
                *lista=(*lista)->nast;
                free(wskaz);
                return wartosc;
/* pop: Usuwa 1 element ze stosu*/
        }
 
}
int print(t_elem **lista) {
        t_elem *elem;
 
        elem=*lista;
        while (elem!=NULL) {
                printf("%d ", elem->dana);
                elem=elem->nast;
        }
        printf("\n");
 
        return 0;
}
/* print: Wypisuje  zawartooci stosu*/
 
int empty(t_elem **lista)
{
        if (*lista==NULL)
                return 0;
    else
        return 1;
}
/* empty: Sprawdza czy stos jest pusty */
void przetwarzaj(t_elem **stos, char operat,int ilosc) {
   int pom1, pom2;
    if(ilosc==0)
    printf("Za ma3o podanych liczb aby dokonaa dzia3ania");
   pom1=pop(stos);
   if(empty(stos)==0)
    printf("Za ma3o podanych liczb aby dokonaa dzia3ania");
   pom2=pop(stos);
 switch(operat)
   {
                   case '+':
                        pom1 = pom1+pom2;
                        push(stos, pom1);
                        break;
                   case '-':
                        if (pom2<0){
                         pom2=-pom2;
                         pom1 = pom1+pom2;
                         }
                         else
                         pom1=pom1-pom2;
                        push(stos, pom1);
                        break;
                   case '*':
                        pom1 = pom1*pom2;
                        push(stos, pom1);
                        break;
                   case '/':
                        pom1 = pom1/pom2;
                        push(stos, pom1);
                        break;
                   case '#':
                        push(stos, pom2);
                        break;
                   case '&':
                          push(stos, pom1);
                          push(stos, pom1);
                          break;
                   case '$':
                         push(stos, pom1);
                         push(stos, pom2);
                   break;
                   default:
                           printf("\n\n\t\tWarunki PRE funkcji niespelnione");
                           break;
}
}
 
 
   int main ()
 {
        char char_pobierane[ROZMIAR];		/* Do tej tablicy dane pobierane sa ze stdin */
        int int_pobierane;			/* Do tej zmiennej przepisywane sa liczby z char_pobierane przy pomocy funkcji atoi */
        char operat=0;				/* Pojawienie sie operatora funkcyjnego [+ - * / # % q ?] zostaje przypisane do zmiennej operat */
        int  indeks=1;				/* i dla for petli for, indeks dla while(operator!=q) () */
        int  ilosc=0;				/* Ilosc liczb na stosie */
t_elem *stos=NULL;				/* zainiciowanie stosu */
        int  pomoc3=0;				/* Zmienna która bede potrzebowala do sprawdzenia czy podany znak przez uzytnownika jest cyfra czy znakiem */
 
 
 
  printf("\nKalkulator RPN mozliwe opcje \n");
  printf("q=Koniec pracy  z programem\n");
  printf("#-usuwanie ostatnio dodanego elementu\n");
  printf("$-zamiana miejscami 2 elementów na szczycie\n");
  printf("&-zduplikowanie ostatniego wprowadzonego elementu\n");
  printf("?- Wyswietla elementy stosu\n");
      while(operat != 'q')
      {
      printf("\nNo. %d:\t", indeks);
      scanf("%s", char_pobierane);
 
 
                                  /* Jezeli zostala wprowadzona liczba to ten switch zamieni ja na int i wpisze do zmiennej int_pobierane */
                        switch(char_pobierane[0])
                        {
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9':
                        int_pobierane=atoi(char_pobierane);
                        ilosc++;
                        pomoc3++;
                        push(&stos, int_pobierane);
                        break;
                        case '-':                              /* Uwzglednienie liczb ujemnych */
                             switch(char_pobierane[1])
                             {
                             case '0':
                             case '1':
                             case '2':
                             case '3':
                             case '4':
                             case '5':
                             case '6':
                             case '7':
                             case '8':
                             case '9':
                             int_pobierane=atoi(char_pobierane);
                             ilosc++;
                             pomoc3++;
                             push(&stos, int_pobierane);
                             break;
                             default:
                             break;
                             }
                        break; /* break do case '-' */
                        default:
                        break;/* Niepotrzebny default,.. ale moze jakis blad wpadnie po drodze, ktory tym defaultem bedzie mozna wyeliminowac */
                        }
 
 
 
 
      if(pomoc3==0) /* Znaczy, ze char_pobierane nie jest liczba */
          {
                      operat = char_pobierane[0];
 
                      switch(operat)              
                      {
                               case '+':
                               case '-':
                               case '*':
                               case '/':
                               case '$':
                                    if(ilosc>=2)
                                    przetwarzaj(&stos, operat,ilosc);
                                    else
                                    printf("\n\n\t\tZa malo liczb na stosie");
                                      break;
                               case '#':
                                    if(ilosc>1)
                                    przetwarzaj(&stos, operat,ilosc);
                                    else
                                    printf("\n\n\t\tZa malo liczb na stosie, Nie mozna usunac jedynego elementu");
                                      break;
                               case '&':
                                    if(ilosc>=1)
                                    przetwarzaj(&stos, operat,ilosc);
                                    else
                                    printf("\n\n\t\tZa malo liczb na stosie");
                                      break;
                               case '?':
                                    print(&stos);
                               case 'q':
                                    break;
                               default:
                                        printf("\n\n\t\tBrak takiego polecenia");
                      }  /* Koniec switcha */
          }    /* Koniec  operacji dla operata roznego od cyfry */
 
          pomoc3=0;
      indeks++;
      }      /* Koniec while(operator != 'q') */
 
 
      }
