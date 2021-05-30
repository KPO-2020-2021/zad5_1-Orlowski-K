#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../tests/doctest/doctest.h"

#include "example.h"
#include "Vector3D.hh"
#include "Matrix3x3.hh"
#include "Drone.hh"
#include "Scene.hh"
// This is all that is needed to compile a test-runner executable.
// More tests can be added here, or in a new tests/*.cpp file.

TEST_CASE("Test zliczania wektorow"){
    Vector3D V;

    CHECK( V.show_active_vectors() == 1);
}

TEST_CASE("Test zliczania wektorow"){
    Vector3D V;

    CHECK( V.show_all_vectors() == 2); /* Zlicza wektory z powyzszych testow wiec trzeba je uwzglednic */
}


TEST_CASE("Test zliczania wektorow"){
    Vector3D V, V2 = {2,4,1};

    CHECK( V.show_active_vectors() == 2);
}

TEST_CASE("Test zliczania wektorow"){
    Vector3D V, V2 = {2,4,1};

    CHECK( V.show_all_vectors() == 6); /* Zlicza wektory z powyzszych testow wiec trzeba je uwzglednic */
}



TEST_CASE("Test zliczania wektorow"){
    Vector3D V, V2 = {2,4,1};

    {
        Vector3D V3_tymczasowy;
    }

    CHECK( V.show_active_vectors() == 2);
}

TEST_CASE("Test zliczania wektorow"){
    Vector3D V, V2 = {2,4,1};

    {
        Vector3D V3_tymczasowy;
    }

    CHECK( V.show_all_vectors() == 12); /* Zlicza wektory z powyzszych testow wiec trzeba je uwzglednic */
}

TEST_CASE("Test zliczania wektorow"){
    Vector3D V, V2 = {2,4,1};

    V = V2 * 2;

    CHECK( V.show_active_vectors() == 2);
}

TEST_CASE("Test zliczania wektorow"){
    Vector3D V, V2 = {2,4,1};

    V = V2 * 2;

    CHECK( V.show_all_vectors() == 18); /* Zlicza wektory z powyzszych testow wiec trzeba je uwzglednic */
}



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



TEST_CASE("Test konstruktora dla klasy Cuboid (dziedziczenie)"){
    Cuboid Test;
    Vector3D Vertex = {1,1,1};
    unsigned int Errors = 0;

    if(Test.TakeFilename_FinalSolid() != "" || Test.TakeFilename_TemplateSolid() != "" )
        ++Errors;

    CHECK(!Errors);
}


TEST_CASE("Test konstruktora dla klasy Cuboid (dziedziczenie)"){
    Cuboid Test;
    Vector3D Vertex = {1,1,1}, V;

    CHECK( V == Test.Scale(Vertex) );
}

TEST_CASE("Test konstruktora  dla klasy Cuboid"){
    Cuboid Test;
    Vector3D  V = {0,0,0};
    unsigned int Errors = 1;

    if(Test.Take_Layout() == V && Test.Take_OrientAngle() == 0 )
        --Errors;

    CHECK(!Errors);
}



TEST_CASE("Test konstruktora parametrycznego dla klasy Cuboid (dziedziczenie)"){
    Vector3D V1 = {2,2,2};
    Cuboid Test("abc","cdb",V1,V1,90);
    Vector3D Vertex = {1,1,1}, V = {2,2,2};

    CHECK( V == Test.Scale(Vertex) );
}

TEST_CASE("Test konstruktora parametrycznego dla klasy Cuboid (dziedziczenie)"){
    Vector3D V1 = {2,2,2};
    Cuboid Test("abc","cdb",V1,V1,90);
    Vector3D Vertex = {1,1,1}, V = {2,2,2};
    unsigned int Errors = 0;

    if(Test.TakeFilename_FinalSolid() != "cdb" || Test.TakeFilename_TemplateSolid() != "abc" )
        ++Errors;

    CHECK(!Errors);
}

TEST_CASE("Test konstruktora dla klasy Prism (dziedziczenie)"){
    Prism Test;
    Vector3D Vertex = {1,1,1};
    unsigned int Errors = 0;

    if(Test.TakeFilename_FinalSolid() != "" || Test.TakeFilename_TemplateSolid() != "" )
        ++Errors;

    CHECK(!Errors);
}


TEST_CASE("Test konstruktora parametrycznego dla klasy Cuboid"){
    Vector3D V1 = {2,2,2};
    Cuboid Test("abc","cdb",V1,V1,90);
    Vector3D Vertex = {1,1,1}, V = {2,2,2};
    unsigned int Errors = 1;

    if(Test.Take_Layout() == V && Test.Take_OrientAngle() == 90 )
        --Errors;

    CHECK(!Errors);
}


TEST_CASE("Test konstruktora dla klasy Prism (dziedziczenie)"){
    Prism Test;
    Vector3D Vertex = {1,1,1};
    unsigned int Errors = 0;

    if(Test.TakeFilename_FinalSolid() != "" || Test.TakeFilename_TemplateSolid() != "" )
        ++Errors;

    CHECK(!Errors);
}


TEST_CASE("Test konstruktora dla klasy Prism (dziedziczenie)"){
    Prism Test;
    Vector3D Vertex = {1,1,1}, V;

    CHECK( V == Test.Scale(Vertex) );
}

TEST_CASE("Test konstruktora  dla klasy Prism"){
    Prism Test;
    Vector3D  V = {0,0,0};
    unsigned int Errors = 1;

    if(Test.Take_Layout() == V && Test.Take_OrientAngle() == 0 )
        --Errors;

    CHECK(!Errors);
}



TEST_CASE("Test konstruktora parametrycznego dla klasy Prism (dziedziczenie)"){
    Vector3D V1 = {2,2,2};
    Prism Test("abc","cdb",V1,V1,90);
    Vector3D Vertex = {1,1,1}, V = {2,2,2};

    CHECK( V == Test.Scale(Vertex) );
}

TEST_CASE("Test konstruktora parametrycznego dla klasy Prism (dziedziczenie)"){
    Vector3D V1 = {2,2,2};
    Prism Test("abc","cdb",V1,V1,90);
    Vector3D Vertex = {1,1,1}, V = {2,2,2};
    unsigned int Errors = 0;

    if(Test.TakeFilename_FinalSolid() != "cdb" || Test.TakeFilename_TemplateSolid() != "abc" )
        ++Errors;

    CHECK(!Errors);
}


TEST_CASE("Test konstruktora parametrycznego dla klasy Cuboid"){
    Vector3D V1 = {2,2,2};
    Prism Test("abc","cdb",V1,V1,90);
    Vector3D Vertex = {1,1,1}, V = {2,2,2};
    unsigned int Errors = 1;

    if(Test.Take_Layout() == V && Test.Take_OrientAngle() == 90 )
        --Errors;

    CHECK(!Errors);
}



TEST_CASE("Test konstruktora klasy Drone"){
    Drone Test;
    unsigned int Errors = 1;
    Vector3D V;

    if(Test.TakeLayout() == V && Test.TakeOrient() == 0 )
        --Errors;


    CHECK(!Errors);
}



TEST_CASE("Test tworzenia drona"){
    Drone Test;
    Vector3D V_Layout ={2,2,0}, V = {2,2,0};
    unsigned int number_of_drones = 0;
    unsigned int Errors = 1;

    Test.MakeDrone(V_Layout,90,number_of_drones);

    if(Test.TakeLayout() == V && Test.TakeOrient() == 90 )
        --Errors;

    CHECK(!Errors);
}




TEST_CASE("Transforamcja miedzy ukladem prostokata a drona"){
    Vector3D Layout = {2,2,1};
    Vector3D Scale = {2,2,2};
    Vector3D Transform = {3,3,1};
    Vector3D Result = {8,8,3};
    Cuboid Test("abc","cdb",Scale,Layout,0);

    CHECK( Test.TranformToParentialCoordinate(Transform) == Result);
}

TEST_CASE("Transforamcja miedzy ukladem prostokata a drona"){
    Vector3D Layout = {2,2,1};
    Vector3D Scale = {2,2,2};
    Vector3D Transform = {3,3,1};
    Vector3D Result = {-8,8,3};
    Cuboid Test("abc","cdb",Scale,Layout,90);

    CHECK( Test.TranformToParentialCoordinate(Transform) == Result);
}


TEST_CASE("Transforamcja miedzy ukladem graniastoslupa a drona"){
    Vector3D Layout = {2,2,1};
    Vector3D Scale = {2,2,2};
    Vector3D Transform = {3,3,1};
    Vector3D Result = {8,8,3};
    Prism Test("abc","cdb",Scale,Layout,0);

    CHECK( Test.TranformToParentialCoordinate(Transform) == Result);
}

TEST_CASE("Transforamcja miedzy ukladem graniastoslupa a drona"){
    Vector3D Layout = {2,2,1};
    Vector3D Scale = {2,2,2};
    Vector3D Transform = {3,3,1};
    Vector3D Result = {-4,8,3};
    Prism Test("abc","cdb",Scale,Layout,-270);

    CHECK( Test.TranformToParentialCoordinate(Transform) == Result);
}



TEST_CASE("Zmiana orientacji graniastoslupa w ukladzie lokalnym (obrot wokol wlasnej osi)"){
    Vector3D Layout = {2,2,1};
    Vector3D Scale = {2,2,2};
    Prism Test("abc","cdb",Scale,Layout,90);

    Test.Rotate(90);

    CHECK( Test.Take_OrientAngle() == 180);
}









