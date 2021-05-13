#pragma once

#include "Dron.hh"


class Scene{

    private:

        Dron DronTab[2];

        std::string Filename_Surface;

        PzG::LaczeDoGNUPlota Link;


    public:

        const Dron& TakeActiveDron() const;

        Dron& UseActiveDron();

        const std::string& TakeFilename_Surface() const { return Filename_Surface; };
    
};