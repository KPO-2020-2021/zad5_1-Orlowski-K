#pragma once

#include "Prism6.hh"
#include "Cuboid.hh"
#include "lacze_do_gnuplota.hh"
#include <vector>

class Dron{

    private:

        Vector3D Layout;

        double   OrientAngle;

        Cuboid   Body;

        Prism    Rotor;

        bool  Count_Save_BodyGlCoor() const;

        bool  Count_Save_RotorGlCoor(const Prism& Rotor ) const;

    protected:

        Vector3D  TransformToParentialCoordinate( const Vector3D& Vertex) const;

    public:

        void MakeTrack(double rotation_angle, double FlightLen, std::vector<Vector3D>& TracePoints);

        bool MakeVerticalFlight(double FlightLen, PzG::LaczeDoGNUPlota& Link) ;

        bool MakeHorizontalFlight(double FlightLen, PzG::LaczeDoGNUPlota& Link) ;

        bool Count_Save_GlobalCoor() const;


};