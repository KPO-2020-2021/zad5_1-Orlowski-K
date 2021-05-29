#include "Cuboid.hh"



Cuboid::Cuboid():
    Solid(){
    Layout = {0,0,0};
    OrientAngle = 0;
}



/*!
 *   \brief Metoda zmieniajaca uklad
 *    Transformuje wektory do ukladu wyzszego 
 *
 *   \param [in]  Vertex - wektor 3D odpowiadajacy wierzcholkowi w przestrzeni
 *   \retval tmp    - wektor przedstawiony w ukladzie lokalnym zespolu
 */
Vector3D Cuboid::TranformToParentialCoordinate(const Vector3D& Vertex) const{
    Matrix3x3 tmp;
    tmp = create_rotation('z',OrientAngle);

    return tmp * (Cuboid::Scale(Vertex) + Layout );
}




/*!
 *   \brief Konstruktor parametryczny klasy Cuboid
 *
 *   Wykorzystuje wywolanie konstruktora klasy Solid
 * 
 *   \param [in]  File1     - sciezka do pliku ze wzorcowymi brylami
 *   \param [in]  File2     - sciezka do pliku z docelowymi brylami
 *   \param [in]  V_scale   - wektor skalujacy
 *   \param [in]  V         - wektor opisujacy polozenie w przestrzeni
 *   \param [in]  angle     - kat orientacji bryly w przestrzeni
 *   \retval    Obiekt klasy Cuboid z zainicjowanymi polami
 */
Cuboid::Cuboid(std::string File1, std::string File2, const Vector3D &V_scale, const Vector3D &V, double angle ):
    Solid(File1,File2,V_scale){
        Layout = V;
        OrientAngle = angle;
    }
