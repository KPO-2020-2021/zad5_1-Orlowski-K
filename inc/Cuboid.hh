#pragma once

#include "GeometricSolid.hh"



/*!
 * \file
 * \brief Klasa opisujaca prostopadloscian
 *
 * Klasa opisujaca prostopadloscian
 */


/*!
 * \brief Klasa opisujaca prostopadloscian
 *
 *  Klasa opisuje pojecie prostopadloscianu w przestrzeni.
 *  Jest to klasa dziedziczaca po klasie Solid w trybie 
 *  publicznym. Zawiera pola opisujace polozenie bryly w
 *  ukladzie lokalnym zespolu (drona).
 */
class Cuboid: public Solid{

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

        Cuboid();


        /*!
        *   \brief Konstruktor parametryczny klasy
        */
        Cuboid(std::string File1, std::string File2, Vector3D V_scale, Vector3D V, double angle );

        /*!
        *   \brief Metoda przechodzaca z ukladu lokalnego bryly do ukladu lokalnego zespolu (drona)
        */
        Vector3D TranformToParentialCoordinate(const Vector3D& Vertex) const;


};