#include "Drone.hh"

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
         tmp = Body.TranformToParentialCoordinate(tmp);
         File_DroneBody << tmp << std::endl;
         File_CuboidTempl >> tmp;

         assert(VertexNumber == 3 || !File_DroneBody.fail());

      }
    File_DroneBody << std::endl;
  }

  return !File_DroneBody.fail();
}






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



Vector3D Drone::TransformToParentialCoordinate(const Vector3D& Vertex) const{
    Matrix3x3 tmp_matrix;
    Vector3D tmp_vector;

    tmp_matrix = create_rotation('z',OrientAngle);
    tmp_vector = tmp_matrix * Vertex;

    return tmp_vector + Layout;
}




bool Drone::Count_Save_GlobalCoor() const{
    if(!this->Count_Save_BodyGlCoor()) return false;

    for(unsigned int Ind; Ind < 4; ++Ind){
        if(!this->Count_Save_RotorGlCoor(Rotor[Ind])) return false;
    }

    return true;
}



void Drone::MakeTrack(double rotation_angle, double FlightLen, std::vector<Vector3D>& TracePoints){

};


bool Drone::MakeHorizontalFlight(double FlightLen, PzG::LaczeDoGNUPlota& Link){
    FlightLen = FlightLen + Layout[0];
    for(;Layout[0] <= FlightLen ; Layout[0] += 1, Layout[1] += 1){
        if(!this->Count_Save_GlobalCoor()) return false;
        usleep(100000);
        Link.Rysuj();
    }
    Layout[0] -= 1; Layout[1] -= 1;
}



