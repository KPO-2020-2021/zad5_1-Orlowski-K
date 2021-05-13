#pragma once

#include "GeometricSolid.hh"


class Prism: public Solid{

    private:

        Vector3D Layout;

        double OrientAngle;

    public:

         Vector3D TranformToParentialCoordinate(const Vector3D& Vertex) const;

};