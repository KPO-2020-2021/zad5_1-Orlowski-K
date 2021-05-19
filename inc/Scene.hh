#pragma once

#include "Drone.hh"


class Scene{

    private:

        std::vector<Drone> Drones;

        std::string Filename_Surface;

        PzG::LaczeDoGNUPlota Link;

        unsigned int Active;

    public:
        Scene();

        Scene(std::vector<Drone> &DroneContener,std::string Filename, PzG::LaczeDoGNUPlota &Link_2 );

        void AddDrone(const Drone &NewDrone);

        void SwitchActiveDrone();

        const Drone& TakeActiveDrone() const;

        Drone& UseActiveDrone();

        void CreateSurface();

        const std::string& TakeFilename_Surface() const { return Filename_Surface; };
    
};