#pragma once

#include <iostream>
#include "Vector3D.hh"
#include "Matrix3x3.hh"


/*!
 * \file
 * \brief Klasa opisujaca bryle geometryczna
 *
 * Klasa opisujaca bryle geometryczna
 */


/*!
 * \brief Klasa opisujaca bryle geometryczna
 *
 *  Klasa opisuje pojecie bryly geometrycznej w przestrzeni.
 *  Sklada sie z pol przechowujacych sciezki do plikow z
 *  wzorcowymi brylami oraz docelowym miejscem skladowania
 *  bryl. Wektor jest uzywany do slkalowania bryl.
 */
class Solid{

    private:
        /*!
        *   \brief Sciezka do pliku z bryla wzorcowa
        */
        std::string Filename_TemplateSolid;
        /*!
        *   \brief Sciezka do pliku przechowywania finalnych bryl
        */
        std::string Filename_FinalSolid;
        /*!
        *   \brief Wektor skalujacy
        */
        Vector3D    scale;

    public:
        
        Solid();

        /*!
        *   \brief Konstruktor parametryczny klasy Solid
        */
        Solid(std::string FirstFile,std::string SecFile,const Vector3D &V_scale);

        /*!
        *   \brief Metoda zwracajaca sciezke do pliku wzorcowego
        */
        const std::string& TakeFilename_TemplateSolid() const { return Filename_TemplateSolid; };

        /*!
        *   \brief Metoda zwracajaca sciezke do pliku z docelowa bryla
        */
        const std::string& TakeFilename_FinalSolid() const {return Filename_FinalSolid;};


        /*!
        *   \brief Metoda skalujaca wektor
        */
        Vector3D Scale(const Vector3D& Vertex) const;

};

