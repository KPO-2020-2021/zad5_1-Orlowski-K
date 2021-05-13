#pragma once

#include "Drone.hh"


class Scene{

    private:

        Drone DroneTab[2];

        std::string Filename_Surface;

        PzG::LaczeDoGNUPlota Link;


    public:

        const Drone& TakeActiveDron() const;

        Drone& UseActiveDron();

        const std::string& TakeFilename_Surface() const { return Filename_Surface; };
    
};