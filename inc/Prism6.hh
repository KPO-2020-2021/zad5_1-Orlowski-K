#pragma once

#include "GeometricSolid.hh"


class Prism: public Solid{

    private:

        Vector3D Layout;

        double OrientAngle;

    public:

        Prism();

        Prism(std::string File1, std::string File2, Vector3D V_scale, Vector3D V, double angle );

        Vector3D TranformToParentialCoordinate(const Vector3D& Vertex) const;

        void Rotate(double angle);


};