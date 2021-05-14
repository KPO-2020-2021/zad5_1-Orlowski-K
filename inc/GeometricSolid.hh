#pragma once

#include <iostream>
#include "Vector3D.hh"
#include "Matrix3x3.hh"

class Solid{

    private:
        std::string Filename_TemplateSolid;
        std::string Filename_FinalSolid;
        Vector3D    scale;

    public:

        Solid();

        Solid(std::string FirstFile,std::string SecFile, Vector3D V_scale);

        const std::string& TakeFilename_TemplateSolid() const { return Filename_TemplateSolid; };

        const std::string& TakeFilename_FinalSolid() const {return Filename_FinalSolid;};

        Vector3D Scale(const Vector3D& Vertex) const;

};

