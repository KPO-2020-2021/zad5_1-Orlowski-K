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

    if(Drones.size() == 1)
        Active = 0;


}




void Scene::CreateSurface(){
    Link.DodajNazwePliku(Filename_Surface.c_str());
}



void Scene::SwitchActiveDrone(){

    std::cout << "Wybor aktywnego drona" << std::endl << std::endl;
    unsigned int option;
    for(unsigned int i=0; i < Drones.size(); ++i){
        std::cout << i << " - Polozenie (x,y): " << Drones.at(i).TakeLayout()[0]<< "  " << Drones.at(i).TakeLayout()[1];
        if( i == Active)
            std::cout << " <--- Dron aktywny";
        std::cout << std::endl << std::endl;
    }
    std::cout << "Wprowadz numer aktywnego drona > ";
    std::cin >> option;
    std::cout << std::endl << std::endl;

    Active = option;

}


Drone& Scene::UseActiveDrone(){
    return Drones.at(Active);
}


const Drone& Scene::TakeActiveDrone() const{
    return Drones.at(Active);
}