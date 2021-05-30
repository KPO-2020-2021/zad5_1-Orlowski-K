#include "Drone.hh"



Drone::Drone(){

  
  OrientAngle = 0;
  Layout = {0,0,0};
  Series = 0;
  Body = Cuboid();
  for(unsigned int Ind = 0; Ind < 4; ++Ind) Rotor[Ind] = Prism();

}



/*!
 *   \brief Metoda tworzaca drona
 *
 * 
 *   \param [in]  V_l                - wektor polozenia
 *   \param [in]  angle              - kat orientacji
 *   \param [in]  number_of_drones   - zmienna zliczajaca ilosc dronow w aktualnej sesji
 *   \retval  Tworzy pliki tekstowe z zapisanymi wierzcholkami w formacie dla gnuplota, tworzy klase drona.
 */
void Drone::MakeDrone(const Vector3D &V_l, double angle, unsigned int &number_of_drones){
    Vector3D Scale_body = {10,8,4},Scale_rotor = {8,8,2} ,V ={0,0,2};
    Vector3D Rotor_Trans[4] = {{5,4,5},{5,-4,5},{-5,4,5},{-5,-4,5}};
    unsigned int number_of_rotors = number_of_drones * 4;
    std::string File_rotor;
    std::string File_body;

    File_body = BASIC_BODY_FILE + std::to_string(number_of_drones + 1)  + ".dat";

    Cuboid tmp_body(CUBOID_TEMPLETE,File_body,Scale_body,V,0);
  
    File_rotor = BASIC_ROTOR_FILE + std::to_string(number_of_rotors + 1)  + ".dat";
    Prism LFront(PRISM_TEMPLETE,File_rotor,Scale_rotor,Rotor_Trans[0],0);
    ++number_of_rotors;
    File_rotor = BASIC_ROTOR_FILE + std::to_string(number_of_rotors + 1)  + ".dat";
    Prism RFront(PRISM_TEMPLETE,File_rotor,Scale_rotor,Rotor_Trans[1],0);
    ++number_of_rotors;
    File_rotor = BASIC_ROTOR_FILE + std::to_string(number_of_rotors + 1)  + ".dat";
    Prism LBack(PRISM_TEMPLETE,File_rotor,Scale_rotor,Rotor_Trans[2],0);
    ++number_of_rotors;
    File_rotor = BASIC_ROTOR_FILE + std::to_string(number_of_rotors + 1)  + ".dat";
    Prism RBack(PRISM_TEMPLETE,File_rotor,Scale_rotor,Rotor_Trans[3],0);
    ++number_of_rotors;
    Prism tmp_rotor[4] = {LFront,RFront,LBack,RBack};

    Layout = V_l;
    OrientAngle = angle;
    Body = tmp_body;
    Series = number_of_drones;
    for(unsigned int Ind = 0; Ind < 4; ++Ind) Rotor[Ind] = tmp_rotor[Ind];

    ++number_of_drones;
  
}



/*!
 *   \brief Metoda zmieniajaca dane ciala drona
 *    Przelicza opcjonalne zmiany w ukladzie drona i zapisuje je do plikow 
 *
 *   \retval true  - udalo sie zapisac zmiany do plikow
 *   \retval false - w przeciwnym wypadku 
 */
bool  Drone::Count_Save_BodyGlCoor() const{
    std::ifstream File_CuboidTempl(Body.TakeFilename_TemplateSolid());
    std::ofstream File_DroneBody(Body.TakeFilename_FinalSolid());

    if (!File_CuboidTempl.is_open()) {
    std::cerr << std::endl
	 << " Blad otwarcia do odczytu pliku: " << Body.TakeFilename_TemplateSolid() << std::endl
	 << std::endl;
    return false;
  }

  if (!File_DroneBody.is_open()) {
    std::cerr << std::endl
	 << " Blad otwarcia do odczytu pliku: " << Body.TakeFilename_FinalSolid() << std::endl
	 << std::endl;
    return false;
  }

  Vector3D tmp;
  File_CuboidTempl >> tmp;
  while(!File_CuboidTempl.fail()){

      for(unsigned int VertexNumber = 0; VertexNumber < 4; ++VertexNumber){
         tmp = this->TransformToParentialCoordinate( Body.TranformToParentialCoordinate(tmp) );
         File_DroneBody << tmp << std::endl;
         File_CuboidTempl >> tmp;

         assert(VertexNumber == 3 || !File_DroneBody.fail());

      }
    File_DroneBody << std::endl;
  }

  return !File_DroneBody.fail();
}





/*!
 *   \brief Metoda zmieniajaca dane rotorow drona
 *    Przelicza opcjonalne zmiany w ukladzie drona i zapisuje je do plikow 
 *    
 *   \param [in] Rotor - Rotor, ktorego dane maja byc zapisane
 *   \retval true      - udalo sie zapisac zmiany do plikow
 *   \retval false     - w przeciwnym wypadku 
 */
bool  Drone::Count_Save_RotorGlCoor(const Prism& Rotor ) const{
    std::ifstream File_PrismTempl(Rotor.TakeFilename_TemplateSolid());
    std::ofstream File_DroneRotor(Rotor.TakeFilename_FinalSolid());

    if (!File_PrismTempl.is_open()) {
    std::cerr << std::endl
	 << " Blad otwarcia do odczytu pliku: " << Rotor.TakeFilename_TemplateSolid() << std::endl
	 << std::endl;
    return false;
  }

  if (!File_DroneRotor.is_open()) {
    std::cerr << std::endl
	 << " Blad otwarcia do odczytu pliku: " << Rotor.TakeFilename_FinalSolid() << std::endl
	 << std::endl;
    return false;
  }

  Vector3D tmp;
  File_PrismTempl >> tmp;
  while(!File_PrismTempl.fail()){

      for(unsigned int VertexNumber = 0; VertexNumber < 4; ++VertexNumber){
         tmp =  this->TransformToParentialCoordinate( Rotor.TranformToParentialCoordinate(tmp) );
         File_DroneRotor << tmp << std::endl;
         File_PrismTempl >> tmp;

         assert(VertexNumber == 3 || !File_DroneRotor.fail());

      }
    File_DroneRotor << std::endl;
  }

  return !File_DroneRotor.fail();
}


/*!
 *   \brief Metoda transformujaca wierzcholki do ukladu globalnego
 *    Transformuje dane do ukladu globalnego przez wektor polozenia
 *    oraz kat orientacji.
 *
 *   \param [in] Vertex - wektor przeznaczony do translacji 
 *   \retval  Wektor przedstawiony w ukladzie globalnym
 */
Vector3D Drone::TransformToParentialCoordinate(const Vector3D& Vertex) const{
    Matrix3x3 tmp_matrix;
    Vector3D tmp_vector;

    tmp_matrix = create_rotation('z',OrientAngle);
    tmp_vector = tmp_matrix * Vertex;

    return tmp_vector + Layout;
}



/*!
 *   \brief Metoda zzapisujaca dane globalne drona
 *    Wykorzystuje transformacje lokalne bryl, pozniej
 *    transformacje do ukladu drona i ostatecznie do 
 *    ukladu globalnego. Odpowiada za zmiane oboru
 *    rotorow (animacja obracania podczas lotu).
 *
 *   \retval true  - udalo sie zapisac zmiany do plikow
 *   \retval false - w przeciwnym wypadku 
 */
bool Drone::Count_Save_GlobalCoor() {
    if(!this->Count_Save_BodyGlCoor()) return false;

    static double Rotor_angle = 0;
    for(unsigned int Ind = 0; Ind < 4; ++Ind){
        if(Ind == 1 || Ind == 2){
          Rotor[Ind].Rotate(-Rotor_angle);
        }
        else{
          Rotor[Ind].Rotate(Rotor_angle);
        }
        if(!this->Count_Save_RotorGlCoor(Rotor[Ind])) return false;
    }

    Rotor_angle += 10;
    return true;
}


/*!
 *   \brief Metoda lotu poziomego
 *  
 *    Animuje lot drona w kierunku poziomym 
 *   
 *   \param [in]  FlightLen - dlugosc lotu
 *   \param [in]  Link      - lacze do gnuplota
 *
 *   \retval true  - udalo sie wykonac lot
 *   \retval false - w przeciwnym wypadku 
 */
bool Drone::MakeHorizontalFlight(double FlightLen, PzG::LaczeDoGNUPlota& Link){
    Vector3D Destination = {cos(OrientAngle*M_PI/180),sin(OrientAngle*M_PI/180),0};
    std::cout << "Lot do przodu ..." << std::endl;

    for(double Part = 0; Part <= FlightLen   ; Layout = Layout + Destination, ++Part){
        if(!this->Count_Save_GlobalCoor()) return false;
        usleep(100000);
        Link.Rysuj();
    }
    Layout = Layout - Destination;
    return true;
}


/*!
 *   \brief Metoda lotu pionowego
 *  
 *    Animuje lot drona w kierunku pionowym 
 *   
 *   \param [in]  FlightLen - dlugosc lotu
 *   \param [in]  Link      - lacze do gnuplota
 *
 *   \retval true  - udalo sie wykonac lot
 *   \retval false - w przeciwnym wypadku 
 */
bool Drone::MakeVerticalFlight(double FlightLen, PzG::LaczeDoGNUPlota& Link){
    FlightLen = FlightLen + Layout[2];
    if(FlightLen > 0 ){
      std::cout << "Wznoszenie ... " << std::endl;
      for(;Layout[2] <= FlightLen ; Layout[2] += 2){
          if(!this->Count_Save_GlobalCoor()) return false;
          usleep(100000);
          Link.Rysuj();
      }
      Layout[2] -= 2;
    }
    else{
      std::cout << "Opadanie ... " << std::endl;
      for(;Layout[2] >= FlightLen ; Layout[2] -= 2){
          if(!this->Count_Save_GlobalCoor()) return false;
          usleep(100000);
          Link.Rysuj();
      }
      Layout[2] += 2;
    }
  return true;
}

/*!
 *   \brief Metoda obotu drona
 *  
 *    Animuje obracanie sie drona
 *   
 *   \param [in]  rotation_angle - kat obrotu
 *   \param [in]  Link           - lacze do gnuplota
 *
 *   \retval true  - udalo sie wykonac obrot
 *   \retval false - w przeciwnym wypadku 
 */
bool Drone::Change_Orientation(double rotation_angle, PzG::LaczeDoGNUPlota& Link){
  std::cout << "Zmiana orientacji ..." << std::endl;
  double destination;
  destination = rotation_angle + OrientAngle;
  if(rotation_angle > 0){
    for(;OrientAngle <= destination; OrientAngle += 5){
      if(!this->Count_Save_GlobalCoor()) return false;
      usleep(100000);
      Link.Rysuj();
    }
    OrientAngle -= 5;
  }
  else{
    for(;OrientAngle >= destination; OrientAngle -= 5){
      if(!this->Count_Save_GlobalCoor()) return false;
      usleep(100000);
      Link.Rysuj();
    }
    OrientAngle += 5;
  }
  
  return true;
}


/*!
 *   \brief Metoda tworzenia trasy przelotu
 *  
 *    Tworzy sciezke przelotu i zapisuje ja do pliku 
 *   
 *   \param [in]  rotation_angle - kat rotacji
 *   \param [in]  FlightLen      - dlugosc lotu
 *   \param [in]  TracePoints    - kontener z wierzcholkami trasy
 *
 *   \retval Oblicza i zapisuje trase do predefiniowanego pliku
 */
void Drone::MakeTrack(double rotation_angle, double FlightLen, std::vector<Vector3D>& TracePoints)const {
  std::ofstream OutFile;
  double FlightHeight = 80;
  Vector3D tmp = {Layout[0],Layout[1],Layout[2]};

  TracePoints.clear();
  
  if(OutFile.is_open())
    OutFile.close();

  OutFile.open(FLIGHT_TRACK, std::ios::trunc);
  OutFile.clear();
  rotation_angle = rotation_angle + OrientAngle;
  if(!OutFile.is_open()){
  std::cerr << std::endl
	 << " Nie mozna otworzyc do zapisu pliku:" << FLIGHT_TRACK << std::endl
	 << std::endl;
  }

  TracePoints.push_back(tmp);
  tmp[2] += FlightHeight;
  
  TracePoints.push_back(tmp);

  Vector3D Destination = {cos(rotation_angle*M_PI/180),sin(rotation_angle*M_PI/180),0};
  for(double Part = 0; Part < FlightLen ; tmp = tmp + Destination, ++Part);

  TracePoints.push_back(tmp);
  
  tmp[2] -= FlightHeight;
  TracePoints.push_back(tmp);


  for(unsigned int Ind = 0; Ind < TracePoints.size(); ++Ind){
    OutFile << TracePoints.at(Ind) << std::endl;
  }


  OutFile.close();
  TracePoints.clear();


}



/*!
 *   \brief Metoda zwracajaca sciezke do pliku koncowego ciala
 *
 *   \retval Sciezka do pliku z przeksztalconym prostopadloscianem
 */
const std::string& Drone::TakeFilename_Body() const{
    return Body.TakeFilename_FinalSolid();
}



/*!
 *   \brief Metoda zwracajaca sciezke do pliku koncowego rotora
 *
 *   \param [in] Rotor - rotor, ktorego sciezka ma byz zwrocona
 *   \retval Sciezka do pliku z przeksztalconym graniastoslupem
 */
const std::string& Drone::TakeFilename_Rotor(const Prism& Rotor) const{
    return Rotor.TakeFilename_FinalSolid();
}



/*!
 *   \brief Metoda zwracajaca rotor drona
 *
 *   \retval Zadany rotor drona
 */
const Prism&  Drone::operator [] (unsigned int Ind) const{
  return Rotor[Ind];
}

/*!
 *   \brief Metoda zwracajaca polozenie drona
 *
 *   \retval Wektor polozenia drona
 */
const Vector3D Drone::TakeLayout() const{
  return Layout;
}


/*!
 *   \brief Metoda zwracajaca orientacje drona
 *
 *   \retval Orientacja drona
 */
double Drone::TakeOrient() const{
  return OrientAngle;
}







