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
#include "../inc/lacze_do_gnuplota.hh"


int main() {
    PzG::LaczeDoGNUPlota Link;
    Vector3D Layout = {20,20,0};
    double   Orient = 0;
    Drone FirstDrone;
    std::vector<Vector3D> TracePoints;

    FirstDrone.MakeDrone(Layout,Orient);
    FirstDrone.Count_Save_GlobalCoor();

    Link.DodajNazwePliku("../datasets/templates/surface.dat");
    Link.DodajNazwePliku("../datasets/dat/body.dat");
    Link.DodajNazwePliku("../datasets/dat/rotor_1.dat");
    Link.DodajNazwePliku("../datasets/dat/rotor_2.dat");
    Link.DodajNazwePliku("../datasets/dat/rotor_3.dat");
    Link.DodajNazwePliku("../datasets/dat/rotor_4.dat");
    

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
    Link.DodajNazwePliku("../datasets/dat/flight_track.dat");
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
