#pragma once

#include "Prism6.hh"
#include "Cuboid.hh"
#include "lacze_do_gnuplota.hh"
#include <vector>
#include <fstream>
#include <iostream>
#include <unistd.h>



#define  FLIGHT_TRACK       "../datasets/dat/flight_track.dat"



/*!
 * \file
 * \brief Klasa opisujaca drona
 *
 * Klasa opisujaca drona
 */


/*!
 * \brief Klasa opisujaca drona
 *
 *  Klasa opisuje pojecie drona w przestrzeni.
 *  Jest to klasa uzywajaca klasy bryly geometrycznej oraz
 *  dziedziczacych od niej. Cialo drona jest opisane przez
 *  prostopadloscian, a rotory przez graniastoslupy. Sklada
 *  sie z pol przechowujacych bryly oraz danych opisujacych
 *  polozenie calego drona w ukladzie globalnym. Przechowuje
 *  tez numer utworzonego drona.
 */
class Drone{

    private:
        /*!
        *   \brief Wektor polozenia
        */
        Vector3D Layout;
        /*!
        *   \brief Kat orientacji
        */
        double   OrientAngle;
        /*!
        *   \brief Cialo drona jako prostopadloscian
        */
        Cuboid   Body;
        /*!
        *   \brief Tablica rotorow drona jako graniastoslupow
        */
        Prism    Rotor[4];
        /*!
        *   \brief Prywatna metoda zapisu wspolrzednych ciala
        */
        bool  Count_Save_BodyGlCoor() const;
        /*!
        *   \brief Prywatna metoda zapisu wspolrzednych rotorow
        */
        bool  Count_Save_RotorGlCoor(const Prism& Rotor ) const;
        /*!
        *   \brief Numer drona
        */
        unsigned int Series;

    protected:
        /*!
        *   \brief Metoda chroniona transformujaca wierzcholki do ukladu globalnego
        */
        Vector3D  TransformToParentialCoordinate( const Vector3D& Vertex) const;

    public:

        Drone();

        /*!
        *   \brief Metoda tworzaca drona
        */
        void MakeDrone(const Vector3D &V_l, double angle, unsigned int &number_of_drones);
        /*!
        *   \brief Metoda tworzaca trase przelotu
        */
        void MakeTrack(double rotation_angle, double FlightLen, std::vector<Vector3D>& TracePoints)const ;
        /*!
        *   \brief Metoda animujaca lot pionowy
        */
        bool MakeVerticalFlight(double FlightLen, PzG::LaczeDoGNUPlota& Link) ;
        /*!
        *   \brief Metoda animujaca lot poziomy
        */
        bool MakeHorizontalFlight(double FlightLen, PzG::LaczeDoGNUPlota& Link) ;
        /*!
        *   \brief Metoda animujaca obrot drona
        */
        bool Change_Orientation(double rotation_angle, PzG::LaczeDoGNUPlota& Link);
        /*!
        *   \brief Metoda publiczna zapisujaca wspolrzedne drona
        */
        bool Count_Save_GlobalCoor();
        /*!
        *   \brief Metoda udostepniajaca sciezke do pliku prostopadlosianu
        */
        const std::string& TakeFilename_Body() const;
        /*!
        *   \brief Metoda udostepniajaca sciezke do pliku graniastoslupa
        */
        const std::string& TakeFilename_Rotor(const Prism& Rotor) const;
        /*!
        *   \brief Metoda udostepniajaca wektor polozenia drona
        */
        const Vector3D TakeLayout() const;
        /*!
        *   \brief Metoda udostepniajaca orientacje
        */
        double TakeOrient() const;
        /*!
        *   \brief Operator indeksujacy udostepniajaca wybrany rotor
        */
        const Prism& operator [] (unsigned int Ind) const;



};