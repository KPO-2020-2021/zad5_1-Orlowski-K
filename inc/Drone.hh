#pragma once

#include "Prism6.hh"
#include "Cuboid.hh"
#include "lacze_do_gnuplota.hh"
#include <vector>
#include <fstream>
#include <iostream>
#include <unistd.h>

#define PRISM_TEMPLETE      "../datasets/templates/prism6.dat"
#define CUBOID_TEMPLETE     "../datasets/templates/cuboid.dat"
#define BASIC_ROTOR_FILE    "../datasets/dat/rotor_"
#define BASIC_BODY_FILE     "../datasets/dat/body_"
#define  FLIGHT_TRACK       "../datasets/dat/flight_track.dat"

class Drone{

    private:

        Vector3D Layout;

        double   OrientAngle;

        Cuboid   Body;

        Prism    Rotor[4];

        bool  Count_Save_BodyGlCoor() const;

        bool  Count_Save_RotorGlCoor(const Prism& Rotor ) const;

        unsigned int Series;

    protected:

        Vector3D  TransformToParentialCoordinate( const Vector3D& Vertex) const;

    public:

        Drone();

        void MakeDrone(Vector3D V_l, double angle, unsigned int &number_of_drones);

        void MakeTrack(/*double rotation_angle,*/ double FlightLen, std::vector<Vector3D>& TracePoints)const ;

        bool MakeVerticalFlight(double FlightLen, PzG::LaczeDoGNUPlota& Link) ;

        bool MakeHorizontalFlight(double FlightLen, PzG::LaczeDoGNUPlota& Link) ;

        bool Change_Orientation(double rotation_angle, PzG::LaczeDoGNUPlota& Link);

        bool Count_Save_GlobalCoor();

        const std::string& TakeFilename_Body() const;

        const std::string& TakeFilename_Rotor(const Prism& Rotor) const;

        const Prism& operator [] (unsigned int Ind) const;



};