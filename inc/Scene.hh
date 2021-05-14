#pragma once

#include "Drone.hh"


class Scene{

    private:

        std::vector<Drone> Drones;

        std::string Filename_Surface;

        PzG::LaczeDoGNUPlota Link;


    public:
        Scene();

        Scene(std::vector<Drone> &DroneContener,std::string Filename, PzG::LaczeDoGNUPlota &Link_2 );

        void AddDrone(const Drone &NewDrone);

        const Drone& TakeActiveDron() const;

        Drone& UseActiveDron();

        void CreateSurface();

        const std::string& TakeFilename_Surface() const { return Filename_Surface; };
    
};