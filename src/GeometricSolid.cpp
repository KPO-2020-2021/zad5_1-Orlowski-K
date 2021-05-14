#include "GeometricSolid.hh"


Solid::Solid(){
}


Vector3D Solid::Scale(const Vector3D& Vertex) const{
    Vector3D tmp;
    for(unsigned int i = 0; i < 3; ++i){
        tmp[i] = Vertex[i] * scale[i];
    }
    return tmp;
}


Solid::Solid(std::string FirstFile,std::string SecFile, Vector3D V_scale){
    Filename_TemplateSolid = FirstFile;
    Filename_FinalSolid = SecFile;
    scale = V_scale;
}
