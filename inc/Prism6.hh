#pragma once

#include "GeometricSolid.hh"

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


};