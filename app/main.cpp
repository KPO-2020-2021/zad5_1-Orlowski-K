// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "exampleConfig.h"
#include "example.h"
#include "Vector3D.hh"
#include "Matrix3x3.hh"
#include "Drone.hh"
#include "Scene.hh"
#include "../inc/lacze_do_gnuplota.hh"

#define SURFACE "../datasets/templates/surface.dat"
#define FLIGHTHEIHGT 80


int main() {
    PzG::LaczeDoGNUPlota Link;
    unsigned int number_of_drones = 0;
    Vector3D Layout1 = {20,30,0}, Layout2 = {130,130,0}, Layout3 = {90,180,0};
    double   Orient1 = 0, Orient2 = 25, Orient3 = 90, Angle = 0;
    double   FlightLen;
    Drone FirstDrone, SecondDrone, ThirdDrone;
    std::vector<Vector3D> TracePoints;
    std::vector<Drone>    Drones;
    Scene Scene(Drones,SURFACE,Link);
    char option[1] = {'m'};

    FirstDrone.MakeDrone(Layout1,Orient1,number_of_drones);
    FirstDrone.Count_Save_GlobalCoor();

    SecondDrone.MakeDrone(Layout2,Orient2,number_of_drones);
    SecondDrone.Count_Save_GlobalCoor();

    ThirdDrone.MakeDrone(Layout3,Orient3,number_of_drones);
    ThirdDrone.Count_Save_GlobalCoor();

    Scene.CreateSurface();
    Scene.AddDrone(FirstDrone);
    Scene.AddDrone(SecondDrone);
    Scene.AddDrone(ThirdDrone);


    while(option[0] != 'k'){
        switch(option[0]){
            case 'a':
                Scene.SwitchActiveDrone();
                std::cout << "Polozenie Drona aktywnego (x,y): " << Scene.TakeActiveDrone().TakeLayout()[0]<< "  " << Scene.TakeActiveDrone().TakeLayout()[1] << std::endl;
                break;
            case 'p':
                std::cout << "Podaj kierunek lotu (kat w stopniach) > ";
                std::cin >> Angle;
                std::cout << "Podaj dlugosc lotu > ";
                std::cin >> FlightLen;
                std::cin.ignore(10000,'\n');

                Link.ZmienTrybRys(PzG::TR_3D);
                Link.Inicjalizuj();

                Link.UstawZakresX(0, 200);
                Link.UstawZakresY(0, 200);
                Link.UstawZakresZ(0, 120);


                Link.UstawRotacjeXZ(64,65);

                Link.Rysuj();
                std::cout << "Nacisnij ENTER, aby pokazac sciezke przelotu drona " << std::flush;
                std::cin.ignore(10000,'\n');

                Scene.UseActiveDrone().MakeTrack(Angle,FlightLen,TracePoints);
                Link.DodajNazwePliku(FLIGHT_TRACK);
                Link.Rysuj();
                
                std::cout << "Nacisnij ENTER, aby wykonac animacje lotu drona " << std::flush;
                std::cin.ignore(10000,'\n');


                if(!Scene.UseActiveDrone().MakeVerticalFlight(FLIGHTHEIHGT,Link)) return 1;

                if(!Scene.UseActiveDrone().Change_Orientation(Angle,Link)) return 1;

                if(!Scene.UseActiveDrone().MakeHorizontalFlight(FlightLen,Link)) return 1;

                if(!Scene.UseActiveDrone().MakeVerticalFlight(-FLIGHTHEIHGT,Link)) return 1;

                std::cout << std::endl << "Nacisnij ENTER, aby usunac sciezke ... " << std::flush;
                std::cin.ignore(10000,'\n');

                Link.UsunOstatniaNazwe();
                Link.Rysuj();
                
                std::cout << "Nacisnij ENTER, aby zakonczyc ... " << std::flush;
                std::cin.ignore(10000,'\n');

                std::cout << "Polozenie Drona aktywnego (x,y): " << Scene.TakeActiveDrone().TakeLayout()[0]<< "  " << Scene.TakeActiveDrone().TakeLayout()[1] << std::endl;

                break;
            case 'm':
                std::cout << "Polozenie Drona aktywnego (x,y): " << Scene.TakeActiveDrone().TakeLayout()[0] << "  "<<Scene.TakeActiveDrone().TakeLayout()[1] << std::endl;
                std::cout << "a - wybierz aktywnego drona\n";
                std::cout << "p - zadaj parametry przelotu\n";
                std::cout << "m - wyswietl menu\n\n";
                std::cout << "k - koniec dzialania programu\n";
                break;
            default:
                exit(1);
        }
        std::cout << "Twoj wybor <m - menu> ";
        std::cin >> option;
        std::cout <<std::endl;
    }
    std::cout << "Koniec dzialania programu Dragonfly\n";




    




}
