#include "Prism6.hh"


Prism::Prism(){
}


Prism::Prism(std::string File1, std::string File2, Vector3D V_scale, Vector3D V, double angle ):
    Solid(File1,File2,V_scale){
        Layout = V;
        OrientAngle = angle;
}



Vector3D Prism::TranformToParentialCoordinate(const Vector3D& Vertex) const{
    Matrix3x3 tmp;
    Vector3D result;

    tmp = create_rotation('z',OrientAngle);
    result = tmp * Vertex;

    return Prism::Scale(result) + Layout;
}


void Prism::Rotate(double angle){
    OrientAngle += angle;
}