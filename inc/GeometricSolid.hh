#pragma once

#include <iostream>
#include "Vector3D.hh"

class Solid{

    private:
        std::string Filename_TemplateSolid;
        std::string Filename_FinalSolid;
        Vector3D    Scale;

    public:
        
        Vector3D Scale(const Vector3D& Vertex) const;

        const std::string& TakeFilename_TemplateSolid() const { return Filename_TemplateSolid; };

        const std::string& TakeFilename_FinalSolid() const {return Filename_FinalSolid;}; 
};

