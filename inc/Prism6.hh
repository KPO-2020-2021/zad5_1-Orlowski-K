#pragma once

#include "GeometricSolid.hh"

#define PRISM_TEMPLETE      "../datasets/templates/prism6.dat"
#define BASIC_ROTOR_FILE    "../datasets/dat/rotor_"

/*!
 * \file
 * \brief Klasa opisujaca graniastoslup o podstawie szesciokatnej
 *
 * Klasa opisujaca graniastoslup o podstawie szesciakatnej
 */


/*!
 * \brief Klasa opisujaca graniastoslup o podstawie szesciokatnej
 *
 *  Klasa opisuje pojecie graniastoslupa w przestrzeni.
 *  Jest to klasa dziedziczaca po klasie Solid w trybie 
 *  publicznym. Zawiera pola opisujace polozenie bryly w
 *  ukladzie lokalnym zespolu (drona).
 */
class Prism: public Solid{

    private:
        /*!
        *   \brief Wektor polozenia
        */
        Vector3D Layout;
        /*!
        *   \brief Kat orientacji
        */
        double OrientAngle;

    public:

        Prism();

        /*!
        *   \brief Konstruktor parametryczny klasy
        */
        Prism(std::string File1, std::string File2,const Vector3D &V_scale,const Vector3D &V, double angle );

        /*!
        *   \brief Metoda przechodzaca z ukladu lokalnego bryly do ukladu lokalnego zespolu (drona)
        */
        Vector3D TranformToParentialCoordinate(const Vector3D& Vertex) const;

        /*!
        *   \brief Metoda odpowiadajaca za obracanie w ukladzie lokalnym bryly
        */
        void Rotate(double angle);

        /*!
        *   \brief Metoda odpowiadajaca za dostep do wektora polozenia
        */
        const Vector3D& Take_Layout() const {return Layout;}; 

        /*!
        *   \brief Metoda odpowiadajaca za dostep do orientacji
        */
        double Take_OrientAngle() const {return OrientAngle;}; 


};