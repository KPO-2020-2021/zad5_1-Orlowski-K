#pragma once

#include "GeometricSolid.hh"

class Cuboid: public Solid{

    private:

        Vector3D Layout;

        double OrientAngle;

    public:

         Vector3D TranformToParentialCoordinate(const Vector3D& Vertex) const;

};