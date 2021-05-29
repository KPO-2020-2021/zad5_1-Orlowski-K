#include "Scene.hh"



Scene::Scene(){
}


/*!
 *   \brief Konstruktor parametryczny klasy Scena
 *
 * 
 *   \param [in]  DroneContener      - kontener zawierajacy drony
 *   \param [in]  Filename           - sciezka do pliku z powierzchnia
 *   \param [in]  Link_2             - lacze do modulu z programem GNUPlot
 *   \retval  Tworzy obiekt klasy Scene z polami wypelnionymi przez podane wartosci
 */
Scene::Scene(std::vector<Drone*> &DroneContener,std::string Filename, PzG::LaczeDoGNUPlota &Link_2 ){
    Drones = DroneContener;
    Filename_Surface = Filename;
    Link = Link_2;
    Active = 0;
}


/*!
 *   \brief Metoda dodajaca drona do sceny
 *
 *   \param [in] NewDrone - dodawnay dron 
 *   \retval  Dodanie zadanego drona do pola konteneru w scenie
 */
void Scene::AddDrone(Drone &NewDrone){
    Drones.push_back(&NewDrone);
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



/*!
 *   \brief Metoda tworzaca plaszczyzne do rysowania
 *
 *   \retval  Dodanie sciezki do plaszczyzny do lacza do rysowania
 */
void Scene::CreateSurface() {
    Link.DodajNazwePliku(Filename_Surface.c_str());
}



/*!
 *   \brief Metoda zmieniajaca aktywnego drona.
 *   Wyswietla aktywne drony wraz z polozeniami i pozwala uzytkownikowi na wybor.
 *   Numery dronow sa odzwierciedlone w kolejnosci dodawania ich do kontenera.
 *   Drony sa numerowane od 0 kolejnymi liczbami naturalnymi.
 *
 *   \retval  Zmiana wartosci pola Active sceny na podany przez uzytkownika.
 */
void Scene::SwitchActiveDrone(){

    std::cout << "Wybor aktywnego drona" << std::endl << std::endl;
    unsigned int option;
    for(unsigned int i=0; i < Drones.size(); ++i){
        std::cout << i << " - Polozenie (x,y): " << Drones.at(i)->TakeLayout()[0]<< "  " << Drones.at(i)->TakeLayout()[1];
        if( i == Active)
            std::cout << " <--- Dron aktywny";
        std::cout << std::endl << std::endl;
    }
    std::cout << "Wprowadz numer aktywnego drona > ";
    std::cin >> option;
    std::cout << std::endl << std::endl;

    if(option >= Drones.size()){
        std::cerr << std::endl << "Podany numer nie istnieje!!!" << std::endl;
        std::cout << "Powrot do menu. Brak zmiany !!!" << std::endl << std::endl;
    }
    else{
        Active = option;
    }

}

/*!
 *   \brief Metoda Metoda pozwalajaca na dostep do aktywnego drona z mozliwoscia modyfikacji
 *   \retval Dron z kontenera wskazywany przez parametr Actve
 */
Drone* Scene::UseActiveDrone(){
    return Drones.at(Active);
}

/*!
 *   \brief Metoda Metoda pozwalajaca na dostep do aktywnego drona w trybie tylko do odczytu
 *   \retval Dron z kontenera wskazywany przez parametr Actve
 */
const Drone* Scene::TakeActiveDrone() const{
    return Drones.at(Active);
}