#pragma once

#include "Prism6.hh"
#include "Cuboid.hh"
#include "lacze_do_gnuplota.hh"
#include <vector>
#include <fstream>
#include <iostream>
#include <unistd.h>

class Drone{

    private:

        Vector3D Layout;

        double   OrientAngle;

        Cuboid   Body;

        Prism    Rotor[4];

        bool  Count_Save_BodyGlCoor() const;

        bool  Count_Save_RotorGlCoor(const Prism& Rotor ) const;

    protected:

        Vector3D  TransformToParentialCoordinate( const Vector3D& Vertex) const;

    public:

        Drone();

        void MakeDrone(Vector3D V_l, double angle);

        void MakeTrack(/*double rotation_angle,*/ double FlightLen, std::vector<Vector3D>& TracePoints)const ;

        bool MakeVerticalFlight(double FlightLen, PzG::LaczeDoGNUPlota& Link) ;

        bool MakeHorizontalFlight(double FlightLen, PzG::LaczeDoGNUPlota& Link) ;

        bool Change_Orientation(double rotation_angle, PzG::LaczeDoGNUPlota& Link);

        bool Count_Save_GlobalCoor();


};