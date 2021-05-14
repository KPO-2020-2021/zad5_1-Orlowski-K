#pragma once

#include "GeometricSolid.hh"

class Cuboid: public Solid{

    private:

        Vector3D Layout;

        double OrientAngle;

    public:

        Cuboid();

        Cuboid(std::string File1, std::string File2, Vector3D V_scale, Vector3D V, double angle );

        Vector3D TranformToParentialCoordinate(const Vector3D& Vertex) const;

        void Move(Vector3D V, double angle);

};