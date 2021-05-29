#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../tests/doctest/doctest.h"

#include "example.h"
#include "Vector3D.hh"
#include "Matrix3x3.hh"
#include "Drone.hh"
#include "Scene.hh"
// This is all that is needed to compile a test-runner executable.
// More tests can be added here, or in a new tests/*.cpp file.



TEST_CASE("Test konstruktora dla klasy Solid"){
    Solid Test;
    Vector3D Vertex = {1,1,1};
    unsigned int Errors = 0;

    if(Test.TakeFilename_FinalSolid() != "" || Test.TakeFilename_TemplateSolid() != "" )
        ++Errors;

    CHECK(!Errors);

}


TEST_CASE("Test konstruktora dla klasy Solid"){
    Solid Test;
    Vector3D Vertex = {1,1,1}, V;

    CHECK( V == Test.Scale(Vertex) );
}


TEST_CASE("Test konstruktora parametrycznego dla klasy Solid"){
    Vector3D V1 = {2,2,2};
    Solid Test("abc","cdb",V1);
    Vector3D Vertex = {1,1,1}, V = {2,2,2};

    CHECK( V == Test.Scale(Vertex) );
}

TEST_CASE("Test konstruktora parametrycznego dla klasy Solid"){
    Vector3D V1 = {2,2,2};
    Solid Test("abc","cdb",V1);
    Vector3D Vertex = {1,1,1}, V = {2,2,2};
    unsigned int Errors = 0;

    if(Test.TakeFilename_FinalSolid() != "cdb" || Test.TakeFilename_TemplateSolid() != "abc" )
        ++Errors;

    CHECK(!Errors);
}



