#include "Prism6.hh"


Prism::Prism():
    Solid(){
    Layout = {0,0,0};
    OrientAngle = 0;
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
Prism::Prism(std::string File1, std::string File2, const Vector3D &V_scale,const Vector3D &V, double angle ):
    Solid(File1,File2,V_scale){
        Layout = V;
        OrientAngle = angle;
}


/*!
 *   \brief Metoda zmieniajaca uklad
 *    Transformuje wektory do ukladu wyzszego 
 *
 *   \param [in]  Vertex - wektor 3D odpowiadajacy wierzcholkowi w przestrzeni
 *   \retval tmp    - wektor przedstawiony w ukladzie lokalnym zespolu
 */
Vector3D Prism::TranformToParentialCoordinate(const Vector3D& Vertex) const{
    Matrix3x3 tmp;
    Vector3D result;

    tmp = create_rotation('z',OrientAngle);
    result = tmp * Vertex;

    return Prism::Scale(result) + Layout;
}


/*!
 *   \brief Metoda odpowiadajaca za obracanie w ukladzie lokalnym bryly
 *   \param [in] angle - kat obrotu
 *   \retval Zmiana orientacji o zadany kat
 */
void Prism::Rotate(double angle){
    OrientAngle += angle;
}