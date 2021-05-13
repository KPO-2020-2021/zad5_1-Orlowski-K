#include "GeometricSolid.hh"



Vector3D Solid::Scale(const Vector3D& Vertex) const{
    Vector3D tmp;
    for(unsigned int i = 0; i < 3; ++i){
        tmp[i] = Vertex[i] * scale[i];
    }
    return tmp;
}
