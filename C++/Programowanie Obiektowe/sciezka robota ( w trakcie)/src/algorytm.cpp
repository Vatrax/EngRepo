#include "algorytm.hh"

void algorytm::stan()
{
	unsigned int temp=0, rozmiar;
	float temp_x, temp_y;
	cout << "Aktualny stan:" << endl << endl;
	cout << "\tDługość pojedyńczego przemieszczenia: " << przemieszczenie << endl;
	cout << "\t            Jednorazowa ilość kroków: " << kroki << endl;
	cout << "\t            Ilość wykonanych kroków: " << kroki_wyk << endl << endl;
	cout << "\t         Start: (" << s.wez_x() << ", " << s.wez_y() << ")" << endl;  
	cout << "\t  =====> Robot: (" << r.wez_x() << ", " << r.wez_y() << ")" << endl; 
	cout << "\t         Cel: (" << c.wez_x() << ", " << c.wez_y() << ")" << endl << endl;
	cout << "\tŁadunek celu: " << c.wez_ladunek() << endl << endl;
	cout << "\tPołożenie przeszkód: " << endl;
	 
	for(temp=0; temp < przeszkody.size(); temp++)
	{
		temp_x = przeszkody[temp].wez_x();
		temp_y = przeszkody[temp].wez_y();
		rozmiar = przeszkody[temp].wez_rozmiar();
		cout << "\t\t" << temp+1 << ": (" << temp_x << ", " << temp_y << ")\tRozmiar: " <<  rozmiar << endl;
	}
}

void algorytm::dodaj_przeszkode(float new_x, float new_y, int new_rozmiar)
{
	ofstream przeszkody_file;
	przeszkody_file.open (NAZWAPLIKU_przeszkody, ios::app);
	przeszkoda temp;
	temp.ustaw_x(new_x);
	temp.ustaw_y(new_y);
	temp.ustaw_rozmiar(new_rozmiar);
	przeszkody.push_back(temp);
	przeszkody_file << new_x << " " << new_y << " " << new_rozmiar << endl;
	przeszkody_file.close();
}

void algorytm::usun_przeszkode(int i)
{
	ofstream przeszkody_file;
	przeszkody_file.open (NAZWAPLIKU_przeszkody, ios::ate);
	unsigned int temp,rozmiar;
	float temp_x,temp_y;
	przeszkody.erase(przeszkody.begin()+i-1);
	for(temp=0; temp < przeszkody.size(); temp++)
	{
		temp_x = przeszkody[temp].wez_x();
		temp_y = przeszkody[temp].wez_y();
		rozmiar = przeszkody[temp].wez_rozmiar();
		przeszkody_file << temp_x << " " << temp_y << " " << rozmiar << endl;
	}
	przeszkody_file.close();
}

void algorytm::ustal_wsprz_startu(float x, float y)
{
	ofstream start_file;
	start_file.open (NAZWAPLIKU_start, ios::ate);
	s.ustal_x(x);
	s.ustal_y(y);
	start_file << x << " " << y << " 1" << endl;
	
	start_file.close();
}

void algorytm::ustal_wsprz_celu(float x, float y)
{
	ofstream cel_file;
	cel_file.open (NAZWAPLIKU_cel, ios::ate);
	c.ustal_x(x);
	c.ustal_y(y);
	cel_file << c.wez_x() << " " << c.wez_y() << " 5" << endl;
	cel_file.close();
}

void algorytm::ustal_ladunek_celu(int ladunek)
{
	c.ustal_ladunek(ladunek);
}

void algorytm::ustal_przemieszczenie(int i)
{
	przemieszczenie = i;
}

void algorytm::ustal_kroki(int new_kroki)
{
	kroki = new_kroki;
}

void algorytm::edytuj_przeszkode(float new_x, float new_y, int rozmiar, unsigned int i)
{
	przeszkoda temp;
	unsigned int temp_i;
	float temp_x,temp_y;
	vector<przeszkoda>temp_vect;
	temp.ustaw_x(new_x);
	temp.ustaw_y(new_y);
	temp.ustaw_rozmiar(rozmiar);
	for(temp_i=0; temp_i < przeszkody.size(); temp_i++)
	{
		if(temp_i+1 != i)
		{
			temp_vect.push_back(przeszkody[temp_i]);
		}
		else
			temp_vect.push_back(temp);
	}
	przeszkody.clear();
	for(temp_i=0; temp_i < temp_vect.size(); temp_i++)
	{
			przeszkody.push_back(temp_vect[temp_i]);
	}
	
	
	ofstream przeszkody_file;
	przeszkody_file.open (NAZWAPLIKU_przeszkody, ios::ate);
	for(temp_i=0; temp_i < przeszkody.size(); temp_i++)
	{
		temp_x = przeszkody[temp_i].wez_x();
		temp_y = przeszkody[temp_i].wez_y();
		rozmiar = przeszkody[temp_i].wez_rozmiar();
		przeszkody_file << temp_x << " " << temp_y << " " << rozmiar << endl;
	}
	przeszkody_file.close();
	
	
}

void algorytm::dodaj_przeszkode_z_pliku(float new_x, float new_y, int new_rozmiar)
{
	przeszkoda temp;
	temp.ustaw_x(new_x);
	temp.ustaw_y(new_y);
	temp.ustaw_rozmiar(new_rozmiar);
	przeszkody.push_back(temp);
}

void algorytm::usun_ostatnia_przeszkode()
{
	przeszkody.pop_back();
}

void algorytm::wczytywanie_danych()
{
		float x = 0, y = 0;
		int rozmiar = 0;
		
		ofstream dane;
		dane.open (NAZWAPLIKU_cel, ios::ate);
		dane << "0 0 0";
		dane.close();

		
		dane.open (NAZWAPLIKU_start, ios::ate);
		dane << "0 0 0";
		dane.close();


		ifstream dane2(NAZWAPLIKU_przeszkody);

		while(!dane2.eof())
		{
		dane2 >> x >> y >> rozmiar;	
		dodaj_przeszkode_z_pliku(x,y,rozmiar);
		}
		przeszkody.pop_back();
		
		dane2.close();

		dane.open (NAZWAPLIKU_robot, ios::ate);
		dane << "0 0 1";
		dane.close();
		
		dane.open (NAZWAPLIKU_sciezka, ios::ate);
		dane << "0 0 1";
		dane.close();
}

void algorytm::przywroc_pozycje_startu()
{
	r.ustal_x(s.wez_x());
	r.ustal_y(s.wez_y());
	ofstream dane;
	dane.open (NAZWAPLIKU_robot, ios::ate);
	dane << s.wez_x() << " " <<  s.wez_y() << " 1" << endl ;
	dane.close();
	
	dane.open (NAZWAPLIKU_sciezka, ios::ate);
	dane << s.wez_x() << " " <<  s.wez_y() << endl ;
	dane.close();
}

void algorytm::licz()
{
	ofstream p_sciezka, p_robot;
	int i = 0;
	float temp_x = 10, temp_y = 10, natezenie_x = 0, natezenie_y = 0, norma = 0, kierunek_x = 0, kierunek_y = 0, d = 0;
	
	temp_x = r.wez_x();
	temp_y = r.wez_y();
	
	// Otwieranie plików //
	p_robot.open (NAZWAPLIKU_robot, ios::ate);
	p_sciezka.open (NAZWAPLIKU_sciezka, ios::app);
	//////////////////////

	for(i=0; i < kroki; ++i)
	{
		natezenie_x = - ( wylicz_potencjal_sceny(r.wez_x() + przemieszczenie,r.wez_y()  ) - wylicz_potencjal_sceny(r.wez_x(),r.wez_y()) ) / przemieszczenie;   
		natezenie_y = - ( wylicz_potencjal_sceny(r.wez_x(), przemieszczenie + r.wez_y()  ) - wylicz_potencjal_sceny(r.wez_x(),r.wez_y()) ) / przemieszczenie;   
		norma = sqrt((natezenie_x * natezenie_x) + (natezenie_y * natezenie_y));
		kierunek_x = (natezenie_x / norma) * przemieszczenie;
		kierunek_y = (natezenie_y / norma) * przemieszczenie;
		temp_x = r.wez_x() + kierunek_x;
		temp_y = r.wez_y() + kierunek_y;
		d = sqrt( ((r.wez_x() - c.wez_x()) *(r.wez_x() - c.wez_x())) + ((r.wez_y() - c.wez_y()) *(r.wez_y() - c.wez_y())) );
		cout << temp_x << " " << temp_y << endl;
		cout << d << endl;
		p_sciezka << temp_x << " " <<  temp_y << endl;
		r.ustal_x( temp_x);
		r.ustal_y( temp_y);
		if(d < 5)
		{
			cout << "Cel został osiągnięty." << endl;
			break;
		}
	}

	p_robot <<  temp_x << " " <<  temp_y << " 1" << endl;
	
	// Zamykanie plików //
	p_sciezka.close();
	p_robot.close();
	/////////////////////
	
}

float algorytm::wylicz_potencjal_sceny(float x_sceny, float y_sceny)
{
	unsigned int i = 0;
	float potencjal = 0;
	for(i = 0; i < przeszkody.size(); i++)
	{
		potencjal += przeszkody[i].wylicz_potencjal(x_sceny, y_sceny);
	}
	potencjal += c.wylicz_potencjal(x_sceny, y_sceny);
	return potencjal;
}
