#include "GeometricSolid.hh"


Solid::Solid(){
    Filename_TemplateSolid = "";
    Filename_FinalSolid = "";
    scale = {0,0,0};
}


/*!
 *   \brief Metoda skalujaca wektor
 *    Mnozy odpowiadajace sobie wartosci wektorow 
 *
 *   \param [in]  Vertex - wektor 3D stanowiacy podstawe skalowania
 *   \retval tmp    - wynikowy wektor
 */
Vector3D Solid::Scale(const Vector3D& Vertex) const{
    Vector3D tmp;
    for(unsigned int i = 0; i < 3; ++i){
        tmp[i] = Vertex[i] * scale[i];
    }
    return tmp;
}


/*!
 *   \brief Konstruktor parametryczny klasy Solid
 *
 *   \param [in]  FirstFile - sciezka do pliku ze wzorcowymi brylami
 *   \param [in]  SecFile   - sciezka do pliku z docelowymi brylami
 *   \param [in]  V_scale   - wektor skalujacy
 *   \retval    Obiekt klasy Solid z zainicjowanymi polami
 */
Solid::Solid(std::string FirstFile,std::string SecFile, const Vector3D &V_scale){
    Filename_TemplateSolid = FirstFile;
    Filename_FinalSolid = SecFile;
    scale = V_scale;
}
