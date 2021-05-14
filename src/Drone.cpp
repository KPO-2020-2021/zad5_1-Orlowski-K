#include "Drone.hh"



Drone::Drone(){
}


void Drone::MakeDrone(const Vector3D V_l, double angle){
    Vector3D Scale_body = {10,8,4},Scale_rotor = {8,8,2} ,V ={0,0,2};
    Cuboid tmp_body("../datasets/templates/cuboid.dat","../datasets/dat/body.dat",Scale_body,V,0);
    Vector3D Rotor_Trans[4] = {{5,4,5},{5,-4,5},{-5,4,5},{-5,-4,5}};

    Prism LFront("../datasets/templates/prism6.dat","../datasets/dat/rotor_1.dat",Scale_rotor,Rotor_Trans[0],0);
    Prism RFront("../datasets/templates/prism6.dat","../datasets/dat/rotor_2.dat",Scale_rotor,Rotor_Trans[1],0);
    Prism LBack("../datasets/templates/prism6.dat","../datasets/dat/rotor_3.dat",Scale_rotor,Rotor_Trans[2],0);
    Prism RBack("../datasets/templates/prism6.dat","../datasets/dat/rotor_4.dat",Scale_rotor,Rotor_Trans[3],0);

    Prism tmp_rotor[4] = {LFront,RFront,LBack,RBack};

    Layout = V_l;
    OrientAngle = angle;
    Body = tmp_body;
    for(unsigned int Ind = 0; Ind < 4; ++Ind) Rotor[Ind] = tmp_rotor[Ind];

  
}




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

  std::cout << "Tutaj jestem" << std::endl;
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



bool Drone::MakeHorizontalFlight(double FlightLen, PzG::LaczeDoGNUPlota& Link){
    FlightLen = FlightLen + Layout[0];
    std::cout << "Lot do przodu ..." << std::endl;
    for(;Layout[0] <= FlightLen ; Layout[0] += 1, Layout[1] += 1){
        if(!this->Count_Save_GlobalCoor()) return false;
        usleep(100000);
        Link.Rysuj();
    }
    Layout[0] -= 1; Layout[1] -= 1;
    return true;
}



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
      Layout[2] -= 2;
    }
  return true;
}


bool Drone::Change_Orientation(double rotation_angle, PzG::LaczeDoGNUPlota& Link){
  rotation_angle += OrientAngle;
  std::cout << "Zmiana orientacji ..." << std::endl;
  for(;OrientAngle <= rotation_angle; OrientAngle += 5){
    if(!this->Count_Save_GlobalCoor()) return false;
    usleep(100000);
    Link.Rysuj();
  }
  OrientAngle -= 5;
  return true;
}



void Drone::MakeTrack(double FlightLen, std::vector<Vector3D>& TracePoints)const {
  std::ofstream OutFile("../datasets/dat/flight_track.dat");
  double FlightHeight = 80;
  Vector3D tmp = {Layout[0],Layout[1],Layout[2]};

  if(!OutFile.is_open()){
  std::cerr << std::endl
	 << " Nie mozna otworzyc do zapisu pliku: ../datasets/dat/flight_track.dat" << std::endl
	 << std::endl;
  }

  TracePoints.push_back(tmp);
  tmp[2] += FlightHeight;
  TracePoints.push_back(tmp);
  tmp[0] += FlightLen; tmp[1] += FlightLen;
  TracePoints.push_back(tmp);
  tmp[2] -= FlightHeight;
  TracePoints.push_back(tmp);


  for(unsigned int Ind = 0; Ind < TracePoints.size(); ++Ind){
    OutFile << TracePoints.at(Ind) << std::endl;
  }


}












