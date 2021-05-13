#ifndef VECTOR3D_HH
#define VECTOR3D_HH


#include "Vector.hh"


/*!
 * \file  Vector3D.hh
 * \brief Plik zawiera definicje klasy wektora 3D opartego na szablonie
 *
 */


/*!
 * \brief Klasa Wektor3D jako instancja szablonu klasy
 *
 *  Instancja szablonu opisuje wektor posiadajacy trzy wartosci x,y,z.
 *  W ten sposob przedstawia polozenie w trzech wymiarach. Mozliwe sa
 *  dokladnie takie same operacje jak w przypadku wektorow innych wymiarow.
 */
typedef Vector<double,3> Vector3D;


#endif
