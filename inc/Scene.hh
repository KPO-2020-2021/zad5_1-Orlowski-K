#pragma once

#include "Drone.hh"

/*!
 * \file
 * \brief Klasa opisujaca scene
 *
 * Klasa opisujaca scene
 */


/*!
 * \brief Klasa opisujaca scene
 *
 *  Klasa opisuje pojecie sceny jako przestrzeni,
 *  w której znajduja sie zadane obiekty. Moze
 *  zawierac wiele obiektow typu Drone. Jako pola
 *  prywatne zzwiera kontener dronow, sciezke do pliku
 *  z plaszczyzna, Lacze do programu GNUPlot i numer
 *  aktywnego drona.
 */
class Scene{

    private:
        /*!
        *   \brief Kontener z dronami
        */
        std::vector<Drone*> Drones;
        /*!
        *   \brief Sciezka do pliku z plaszczyzna
        */
        std::string Filename_Surface;
        /*!
        *   \brief Lacze do GNUPlota
        */
        PzG::LaczeDoGNUPlota Link;
        /*!
        *   \brief Numer aktywnego drona
        */
        unsigned int Active;

    public:
        Scene();
        /*!
        *   \brief Konstruktor parametryczny sceny
        */
        Scene(std::vector<Drone*> &DroneContener,std::string Filename, PzG::LaczeDoGNUPlota &Link_2 );
        /*!
        *   \brief Metoda dodajaca drona do sceny
        */
        void AddDrone(Drone &NewDrone);
        /*!
        *   \brief Metoda zmieniajaca aktualnie wybranego drona
        */
        void SwitchActiveDrone();
        /*!
        *   \brief Metoda pozwalajaca na dostep do aktywnego drona w trybie tylko do odczytu
        */
        const Drone* TakeActiveDrone() const;
        /*!
        *   \brief Metoda pozwalajaca na dostep do aktywnego drona z mozliwoscia modyfikacji
        */
        Drone* UseActiveDrone();
        /*!
        *   \brief Metoda rysujaca plaszczyzne
        */
        void CreateSurface();
        /*!
        *   \brief Metoda pozwalajaca na dostep do sciezki do powierzchni w trybie tylko do odczytu
        */
        const std::string& TakeFilename_Surface() const { return Filename_Surface; };
    
};