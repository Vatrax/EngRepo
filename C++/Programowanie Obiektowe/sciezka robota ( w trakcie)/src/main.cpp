#include <iostream>
#include "robot.hh"
#include "przeszkoda.hh"
#include "cel.hh"
#include "start.hh"
#include "lacze_do_gnuplota.hh"
#include "algorytm.hh"
#include <fstream>
#include <cmath>
#include <cstdlib>

#define NAZWAPLIKU_start   	"dat/start.xyr" 
#define NAZWAPLIKU_cel		"dat/cel.xyr" 
#define NAZWAPLIKU_robot     	"dat/robot.xyr"
#define NAZWAPLIKU_przeszkody	"dat/przeszkody.xyr"
#define NAZWAPLIKU_sciezka    	"dat/sciezka.xy"

using namespace std;

void main_menu();
void wczytywanie_danych(algorytm a);

int main()
{
  
  char znak;
  float temp_x, temp_y;
  int temp_rozmiar, temp_i;

  PzG::LaczeDoGNUPlota  Lacze;
  algorytm a;
  main_menu();
  a.wczytywanie_danych();
  
  while(znak != 'k')
  {
	 cout << "(wyswietl menu: ?) > ";
	 cin >> znak; 
	 switch(znak)
	  {
		  case '?': { main_menu(); break; }
		  case 's': { a.licz(); break; }
		  case 'a' : //aktualny stan
		  {
			  a.stan();
			  Lacze.Inicjalizuj();  
			  Lacze.DodajNazwePliku_PunktyRoznejWielkosci(NAZWAPLIKU_robot,false).ZmienEtykiete("Robot");
			  Lacze.DodajNazwePliku_PunktyRoznejWielkosci(NAZWAPLIKU_cel,false).ZmienEtykiete("Cel");
			  Lacze.DodajNazwePliku_PunktyRoznejWielkosci(NAZWAPLIKU_start,false).ZmienEtykiete("Start");
			  Lacze.DodajNazwePliku_PunktyRoznejWielkosci(NAZWAPLIKU_przeszkody,false);
			  Lacze.DodajNazwePliku_Lamana(NAZWAPLIKU_sciezka,false);
			  Lacze.UstawZakresX(0, 100);
			  Lacze.UstawZakresY(0, 100);		
			  Lacze.ZmienTrybRys(PzG::TR_2D);	  
			  Lacze.Rysuj();
			  break;
		  }
		   case 'z' : //zmiana startu
		  {
			  cout << "Podaj nowe współrzędne startu: " << endl;
			  cout << "x: ";
			  cin >> temp_x;
			  cout << "y: ";
			  cin >> temp_y;
			  a.ustal_wsprz_startu(temp_x, temp_y);
			  
			  break;
		  }
		  case 'c' : //zmiana celu
		  {
			  cout << "Podaj nowe współrzędne celu: " << endl;
			  cout << "x: ";
			  cin >> temp_x;
			  cout << "y: ";
			  cin >> temp_y;
			  a.ustal_wsprz_celu(temp_x, temp_y);
			  break;
		  }
		  case 'u' : //usuwanie przeszkody
		  {
			  cout << "Podaj numer przeszkody do usunięcia: ";
			  cin >> temp_i;
			  a.usun_przeszkode(temp_i);
			  break;
		  }
		  case 'w' : //dodawanie przeszkody
		  {
			  cout << "Wpisz wymiar nowej przeszkody:" << endl;
			  cout << "Podaj x: ";
			  cin >> temp_x;
			  cout << "Podaj y: ";
			  cin >> temp_y;
			  cout << "Podaj rozmiar: ";
			  cin >> temp_rozmiar;
			  a.dodaj_przeszkode(temp_x, temp_y, temp_rozmiar);
			  break;
		  }
		  case 'e' : //edycja przeszkody
		  {
			  cout << "Podaj numer przeszkody: ";
			  cin >> temp_i;
			  cout << "Podaj x: ";
			  cin >> temp_x;
			  cout << "Podaj y: ";
			  cin >> temp_y;
			  cout << "Podaj rozmiar: ";
			  cin >> temp_rozmiar;
			  a.edytuj_przeszkode(temp_x, temp_y, temp_rozmiar, temp_i);
			  break;
		  }
		  case 'd' : //zmiana długości pojedynczego przemieszczenia
		  {
			  cout << "Podaj wartość długości pojedynczego przemieszczenia: ";
			  cin >> temp_i;
			  a.ustal_przemieszczenie(temp_i);
			  break;
		  }
		  case 'i' : //zmiana ilości kroków
		  {
			  cout << "Podaj wartość jednorazowej ilości kroków: ";
			  cin >> temp_i;
			  a.ustal_kroki(temp_i);
			  break;
		  }
		  case 'l' : //zmiana ładunku celu
		  {
			  cout << "Podaj nową wartość ładunku celu: ";
			  cin >> temp_i;
			  a.ustal_ladunek_celu(temp_i);
			  break;
		  }
		  case 'p' : //zmiana ładunku celu
		  {
			  a.przywroc_pozycje_startu();
			  cout << "Przywrócono pozycję startową" << endl;
			  break;
		  }
		  default: break;
	  } 
  }

}

void main_menu()
{
	cout << "Menu Główne: " << endl;
	cout << endl << "s - start algorytmu" << endl;
	cout << "p - przywróć pozycję startową" << endl;
	cout << endl << "z - zmiana współrzędnych startu" << endl;
	cout << "c - zmiana współrzędnych celu" << endl;
	cout << endl << "u - usuń przeszkodę" << endl;
	cout << "w - wstaw nową przeszkodę" << endl;
	cout << "e - edytuj przeszkodę" << endl;
	cout << endl << "d - zmiana długości pojedyńczego przemieszczenia" << endl;
	cout << "i - zmiana jednorazowej ilości kroków" << endl;
	cout << "l - zmiana ładunku celu" << endl;
	cout << "a - wyświetl aktualny stan sceny i robota" << endl;
	cout << endl << "k - koniec programu" << endl;	
}


