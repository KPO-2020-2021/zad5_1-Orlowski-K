#ifndef VECTOR_HH
#define VECTOR_HH

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <cassert>




/*!
 * \file Vector.hh
 * \brief Ten plik zawiera definicję szablonu Vector<>
 *
 */

/*!
 *  \brief
 *  Szablon opisujacy wektor w przestrzeni.
 *  Za jego pomoca opisywane sa wierzcholki dowolnej figury jako wektory
 *  o poczatku w poczatku ukladu wspolrzednych. Wektory skladaja sie z 
 *  tablicy typu double, w ktorej przechowywane sa kolejne skladowe.
 * 
 *  Dla klasy zdefiniowano podstawowe przeciazenia operatorow pozwalajace
 *  na korzystanie z danych, ich modyfikacje oraz podstawowa arytmetyke 
 *  wektorowa.
 */
template <typename Templ_Type, unsigned int Templ_Size>
class Vector {

private:

    Templ_Type size[Templ_Size];     //Tablica wektora
    static unsigned int ActiveVectors;
    static unsigned int AllVectors;

public:

    Vector();

   ~Vector() { ActiveVectors--;};

    Vector(const std::initializer_list<Templ_Type> &SizeList);

    Vector(const Vector &V);

    Vector operator + (const Vector &v);

    Vector operator - (const Vector &v) const;

    Vector operator * (const Templ_Type &tmp);

    Vector operator / (const Templ_Type &tmp);

    Vector& operator = (const Vector &v);

    bool   operator == (const Vector &V2) const;

    const Templ_Type &operator [] (unsigned int index) const;

    Templ_Type &operator [] (unsigned int index);

    double lenght() const;

    void scale(const Vector &v);

    unsigned int show_active_vectors(){return ActiveVectors;};

    unsigned int show_all_vectors(){return AllVectors;};

    

};    

template <typename Templ_Typ, unsigned int Templ_Size>
unsigned int Vector<Templ_Typ,Templ_Size>::ActiveVectors = 0;
template <typename Templ_Typ, unsigned int Templ_Size>
unsigned int Vector<Templ_Typ,Templ_Size>::AllVectors = 0;

/******************************************************************************
 *! \brief  Konstruktor bezparametryczny klasy Vector.                        | 
 |  Zwraca:                                                                   |
 |     \retval Tablice wypelniona zerami.                                     |
 */
template <typename Templ_Typ, unsigned int Templ_Size>
Vector<Templ_Typ,Templ_Size>::Vector() {
    for( Templ_Typ &rSize_i : size) rSize_i = 0;
    ++ActiveVectors;
    ++AllVectors;
}



/******************************************************************************
 *! \brief  Konstruktor klasy Vector.                                         |
 |  Argumenty:                                                                |
 |     \param tmp - Jednowymiarowa tablica typu jaki przyjmuje wektor.        |
 |  Zwraca:                                                                   |
 |      \retval Tablice wypelniona wartosciami podanymi w argumencie.         |
 */
template <typename Templ_Typ, unsigned int Templ_Size>
Vector<Templ_Typ,Templ_Size>::Vector(const std::initializer_list<Templ_Typ> &SizeList):
    Vector()
{
    assert(SizeList.size() <= Templ_Size);
    int Ind = -1;
    for (Templ_Typ Size_i : SizeList) size[++Ind] = Size_i;
}

template <typename Templ_Typ, unsigned int Templ_Size>
Vector<Templ_Typ,Templ_Size>::Vector(const Vector &V){
    ++ActiveVectors;
    ++AllVectors;
    for(unsigned int Ind = 0; Ind < Templ_Size; ++Ind){
        size[Ind] = V[Ind];
    }
}


/******************************************************************************
 *! \brief Realizuje dodawanie dwoch wektorow.                                |
 |  Argumenty:                                                                |
 |    \param this - pierwszy skladnik dodawania,                              |
 |    \param v    - drugi skladnik dodawania.                                 |
 |  Zwraca:                                                                   |
 |     \retval Sume dwoch skladnikow przekazanych jako wskaznik na parametr.  |
 */
template <typename Templ_Typ, unsigned int Templ_Size>
Vector<Templ_Typ,Templ_Size> Vector<Templ_Typ,Templ_Size>::operator + (const Vector<Templ_Typ,Templ_Size> &v) {
    Vector<Templ_Typ,Templ_Size> result;
    for (unsigned int i = 0; i < Templ_Size; i++) {
        result[i] = size[i] += v[i];
    }
    return result;
}



/******************************************************************************
 *! \brief Realizuje odejmowanie dwoch wektorow.                              |
 |  Argumenty:                                                                |
 |      \param this - pierwszy skladnik odejmowania,                          |
 |      \param v    - drugi skladnik odejmowania.                             |
 |  Zwraca:                                                                   |
 |      \retval Roznice dwoch skladnikow przekazanych jako wskaznik           |
 |      na parametr.                                                          |
 */
template <typename Templ_Typ, unsigned int Templ_Size>
Vector<Templ_Typ,Templ_Size> Vector<Templ_Typ,Templ_Size>::operator - (const Vector<Templ_Typ,Templ_Size> &v) const {
    Vector<Templ_Typ,Templ_Size> result;
    for (unsigned int i = 0; i < Templ_Size; i++) {
        result[i] = size[i] - v[i];
    }
    return result;
}



template <typename Templ_Typ, unsigned int Templ_Size>
Vector<Templ_Typ,Templ_Size>& Vector<Templ_Typ,Templ_Size>::operator = (const Vector<Templ_Typ,Templ_Size> &v){
    for(unsigned int Ind = 0; Ind < Templ_Size; ++Ind){
        size[Ind] = v[Ind];
    }
    return *this;
}



/******************************************************************************
 *! \brief Realizuje mnozenie wektora przez liczbe zmiennoprzecinkowa.        |
 |  Argumenty:                                                                |
 |      \param this - pierwszy skladnik mnozenia (wektor),                    |
 |      \param tmp  - drugi skladnik mnozenia (liczba typu wektora).          |
 |  Zwraca:                                                                   |
 |      Iloczyn dwoch skladnikow przekazanych jako wskaznik                   |
 |      na parametr.                                                          |
 */
template<typename Templ_Typ, unsigned int Templ_Size>
Vector<Templ_Typ,Templ_Size> Vector<Templ_Typ,Templ_Size>::operator * (const Templ_Typ &tmp) {
    Vector<Templ_Typ,Templ_Size> result;
    for (unsigned int i = 0; i < Templ_Size; i++) {
        result[i] = size[i] *= tmp;
    }
    return result;
}



/******************************************************************************
 * ! \brief ealizuje dzielenie wektora przez liczbe zmiennoprzecinkowa        |
 |  Argumenty:                                                                |
 |      \param this - licznik dzielenia,                                      |
 |      \param tmp  - mianownik dzielenia.                                    |
 |  Zwraca:                                                                   |
 |      Iloraz dwoch skladnikow przekazanych jako wskaznik                    |
 |      na parametr.                                                          |
 */
template<typename Templ_Typ, unsigned int Templ_Size>
Vector<Templ_Typ,Templ_Size> Vector<Templ_Typ,Templ_Size>::operator / (const Templ_Typ &tmp) {
    Vector<Templ_Typ,Templ_Size> result;

    if(tmp == 0)
     throw("Nie dziel przez 0 !!!");

    for (unsigned int i = 0; i < Templ_Size; i++) {
        result[i] = size[i] / tmp;
    }

    return result;
}


/******************************************************************************
 * ! \brief Funktor wektora.                                                  |
 |  Argumenty:                                                                |
 |      \param index - index wektora.                                         |
 |  Zwraca:                                                                   |
 |      \retval Wartosc wektora w danym miejscu tablicy jako stala.           |
 */
template<typename Templ_Typ, unsigned int Templ_Size>
const Templ_Typ &Vector<Templ_Typ,Templ_Size>::operator [] (unsigned int index) const {
    if (index < 0 || index >= Templ_Size) {
        throw("Error: Wektor jest poza zasiegiem!");
    }
    return size[index];
}




/******************************************************************************
 * ! \brief Funktor wektora.                                                  |
 |  Argumenty:                                                                |
 |     \param index - index wektora.                                          |
 |  Zwraca:                                                                   |
 |      \retval Wartosc wektora w danym miejscu tablicy.                      |
 */
template<typename Templ_Typ, unsigned int Templ_Size>
Templ_Typ &Vector<Templ_Typ,Templ_Size>::operator[](unsigned int index) {
    if (index < 0 || index >= Templ_Size) {
        throw("Error: Wektor jest poza zasiegiem!");
    }
    return const_cast<double &>(const_cast<const Vector *>(this)->operator[](index));
}





/******************************************************************************
 * ! \brief Oblicza dlugosc boku                                              |
 |  Argumenty:                                                                |
 |      \param this - zadany wektor                                           |
 |  Zwraca:                                                                   |
 |      \retval Dlugosc wektora jako double                                   |
 */
template<typename Templ_Typ, unsigned int Templ_Size>
double Vector<Templ_Typ,Templ_Size>::lenght() const{
    double result = 0, sum = 0;

    for(unsigned int i = 0; i < Templ_Size; ++i){
        sum += pow(size[i],2);
    }
    result = sqrt(sum);
    return result;
}



/******************************************************************************
 * ! \brief Przeciazenie operatora ==                                         |
 |  Argumenty:                                                                |
 |      \param this - pierwszy wektor,                                        |
 |      \param V2 - drugi wektor.                                             |
 |  Zgodnosc do 10 cyfr po przecinku.                                         |
 */
template<typename Templ_Typ, unsigned int Templ_Size>
bool Vector<Templ_Typ,Templ_Size>::operator == (const Vector<Templ_Typ,Templ_Size> &V2) const {
    for(unsigned int i = 0; i < Templ_Size ; ++i){
        if( fabs(size[i] - V2.size[i]) > 1e-11 )
            return 0;
    }

    return 1;
}



/******************************************************************************
 * ! \brief Przeciazenie operatora <<                                         |
 |  Argumenty:                                                                |
 |      \param out - strumien wyjsciowy,                                      |
 |      \param tmp - wektor.                                                  |
 |   Zwraca:
 |       \retval out -strumien wyjsciowy
 */
template< typename Templ_Typ, unsigned int Templ_Size>
std::ostream &operator << (std::ostream &out, Vector<Templ_Typ,Templ_Size> const &tmp){
    for (unsigned int i = 0; i < Templ_Size; i++) {
        out << std::setw(16) << std::fixed << std::setprecision(10) <<  tmp[i] << "\t";
    }
    return out;
}



/******************************************************************************
 * ! \brief Przeciazenie operatora >>                                         |
 |  Argumenty:                                                                |
 |     \param in - strumien wejsciowy,                                        |
 |     \param tmp - wektor.                                                   |
 |  Zwraca:
 |     \retval in - strumien wejsciowy   
 */
template< typename Templ_Typ, unsigned int Templ_Size>
std::istream &operator >> (std::istream &in, Vector<Templ_Typ,Templ_Size> &tmp){
    for (unsigned int i = 0; i < Templ_Size; i++) {
        in >> tmp[i];
    }
    std::cout << std::endl;
    return in;
}






#endif
