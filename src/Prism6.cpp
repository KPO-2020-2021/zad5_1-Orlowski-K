#include "Prism6.hh"

Vector3D Prism::TranformToParentialCoordinate(const Vector3D& Vertex) const{
    Matrix3x3 tmp;
    tmp = create_rotation('z',OrientAngle);

    return tmp * (Prism::Scale(Vertex) + Layout );
}