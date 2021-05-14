#include "Cuboid.hh"



Cuboid::Cuboid(){
}


Vector3D Cuboid::TranformToParentialCoordinate(const Vector3D& Vertex) const{
    Matrix3x3 tmp;
    tmp = create_rotation('z',OrientAngle);

    return tmp * (Cuboid::Scale(Vertex) + Layout );
}


Cuboid::Cuboid(std::string File1, std::string File2, Vector3D V_scale, Vector3D V, double angle ):
    Solid(File1,File2,V_scale){
        Layout = V;
        OrientAngle = angle;
    }
