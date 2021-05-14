#include "Scene.hh"

Scene::Scene(){
}

Scene::Scene(std::vector<Drone> &DroneContener,std::string Filename, PzG::LaczeDoGNUPlota &Link_2 ){
    Drones = DroneContener;
    Filename_Surface = Filename;
    Link = Link_2;
}



void Scene::AddDrone(const Drone &NewDrone){
    Drones.push_back(NewDrone);
    std::string Filename;

    Filename = NewDrone.TakeFilename_Body();
    
    Link.DodajNazwePliku( Filename.c_str() );
    for(unsigned int Ind = 0; Ind < 4 ; ++Ind){
        Filename = NewDrone.TakeFilename_Rotor(NewDrone[Ind]);
        Link.DodajNazwePliku(Filename.c_str());
    }

}




void Scene::CreateSurface(){
    Link.DodajNazwePliku(Filename_Surface.c_str());
}