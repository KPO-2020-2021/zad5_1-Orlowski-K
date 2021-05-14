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


int main() {
    PzG::LaczeDoGNUPlota Link;
    unsigned int number_of_drones = 0;
    Vector3D Layout1 = {20,20,0}, Layout2 = {130,130,0}, Layout3 = {90,180,0};
    double   Orient1 = 0, Orient2 = 25, Orient3 = 90;
    Drone FirstDrone, SecondDrone, ThirdDrone;
    std::vector<Vector3D> TracePoints;
    std::vector<Drone>    Drones;
    Scene Scene(Drones,SURFACE,Link);

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

    Link.ZmienTrybRys(PzG::TR_3D);
    Link.Inicjalizuj();

    Link.UstawZakresX(0, 200);
    Link.UstawZakresY(0, 200);
    Link.UstawZakresZ(0, 120);


    Link.UstawRotacjeXZ(64,65);

    Link.Rysuj();
    std::cout << "Nacisnij ENTER, aby pokazac sciezke przelotu drona " << std::flush;
    std::cin.ignore(10000,'\n');

    FirstDrone.MakeTrack(130,TracePoints);
    Link.DodajNazwePliku(FLIGHT_TRACK);
    Link.Rysuj();
    
    std::cout << "Nacisnij ENTER, aby wykonac animacje lotu drona " << std::flush;
    std::cin.ignore(10000,'\n');


    if(!FirstDrone.MakeVerticalFlight(80,Link)) return 1;

    if(!FirstDrone.Change_Orientation(45,Link)) return 1;

    if(!FirstDrone.MakeHorizontalFlight(130,Link)) return 1;

    if(!FirstDrone.MakeVerticalFlight(-80,Link)) return 1;

    std::cout << std::endl << "Nacisnij ENTER, aby usunac sciezke ... " << std::flush;
    std::cin.ignore(10000,'\n');

    Link.UsunOstatniaNazwe();
    Link.Rysuj();
    
    std::cout << "Nacisnij ENTER, aby zakonczyc ... " << std::flush;
    std::cin.ignore(10000,'\n');




}
