#include "Cuboid.hh"

Vector3D Cuboid::TranformToParentialCoordinate(const Vector3D& Vertex) const{
    Matrix3x3 tmp;
    tmp = create_rotation('z',OrientAngle);

    return tmp * (Cuboid::Scale(Vertex) + Layout );
}