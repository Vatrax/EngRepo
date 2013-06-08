#include <unistd.h>
#include <iostream>
#include <list>
#include <string>
#include "bloki.hh"
#include "uklad.hh"


using namespace std;

int main(int argc, char *argv[ ])
{
    extern char *optarg;
    extern int optopt;
    char c;
    int pamiec;
    string nazwa_pliku;
    char znak;

    Uklad *System;
    System = new Uklad;

    while ((c = getopt(argc, argv, ":i:o:GP:SCD:W:")) != -1)
    {
        switch (c)
        {
        case 'i':
            nazwa_pliku = optarg;
            System->ZmienWejscie( nazwa_pliku );
            break;

        case 'o':
            nazwa_pliku = optarg;
            System->ZmienWyjscie( nazwa_pliku );
            break;

        case 'G':
            System->DodajBlok('G',0);
            break;

        case 'P':
            pamiec = atoi(optarg);
            System->DodajBlok('P', pamiec);
            break;

        case 'S':
            System->DodajBlok('S',0);
            break;

        case 'C':
            System->DodajBlok('C',0);
            break;

        case 'D':
            pamiec = atoi(optarg);
            System->DodajBlok('D', pamiec);
            break;

        case 'W':
            pamiec = atoi(optarg);
            System->DodajBlok('W', pamiec);
            break;

        case ':':
            cout << "Opcja -" << static_cast<char>(optopt) << " wywolana bez parametru." << endl;
            break;

        case '?':
            cout << "Zly parametr: -" << static_cast<char>(optopt) << endl;
            break;
        }
    }

    System->WczytajWejscie();
    System->WyswietlWykres();
    delete System;
    cin>>znak;
}
