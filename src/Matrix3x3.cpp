#include "Matrix3x3.hh"


/*!
 * \brief Funkcja tworzaca macierz obrotu
 * \param axis - os obrotu
 * \param angle - kat podany w stopniach
 * 
 * \retval Matrix3x3 tmp - maciez obrotu 
 * 
 */
Matrix3x3 create_rotation(char axis, double angle){
    Matrix3x3 tmp;
    angle = angle * M_PI / 180;
    switch(axis){
        case 'x':
            tmp(1,1) = cos(angle);
            tmp(1,2) = -sin(angle);
            tmp(2,1) = sin(angle);
            tmp(2,2) = cos(angle);
            break;
        case 'y':
            tmp(0,0) = cos(angle);
            tmp(0,2) = sin(angle);
            tmp(2,0) = -sin(angle);
            tmp(2,2) = cos(angle);
            break;
        case 'z':
            tmp(0,0) = cos(angle);
            tmp(0,1) = -sin(angle);
            tmp(1,0) = sin(angle);
            tmp(1,1) = cos(angle);
            break;
        default:
            std::cerr << std::endl << "Blad: Niepoprawna opcja" << std::endl;
            break;
    }
    return tmp;
}
