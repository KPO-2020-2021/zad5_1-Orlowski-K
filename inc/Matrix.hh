#ifndef MATRIX_HH
#define MATRIX_HH


#include <iostream>
#include "Vector.hh"


/*!
 * \file Matrix.hh
 *
 *  \brief Plik zawierajacy definicje szablonu Matrix<>
 */

/*!
 *  \brief
 *  Szablon modeluje pojecie macierzy kwadratowej.
 *  Liczby macierzy sa przechowywane jako tablica wielowymiarowa
 *  wybranego typu. Przeciazenia operatorow pozwalaja na modyfikacje i 
 *  dostep do danych macierzy.
 * 
 *  Szablon przyjmuje wartosci typu danych ich ilosci(wymiar macierzy).
 * 
 *  Metody pozwalaja na mnozenie macierzy z wektorem.
 */
template <typename Templ_Type, unsigned int Templ_Size>
class Matrix {

private:
    Templ_Type value[Templ_Size][Templ_Size];               // Wartosci macierzy

public:
    Matrix(Templ_Type tmp[Templ_Size][Templ_Size]);            // Konstruktor klasy
  
    Matrix();                               // Konstruktor klasy

    Matrix operator * (Matrix tmp);

    Vector<Templ_Type,Templ_Size> operator * (Vector<Templ_Type,Templ_Size> tmp);           // Operator mnożenia przez wektor

    Matrix operator + (Matrix tmp);

    Templ_Type  &operator () (unsigned int row, unsigned int column);
    
    const Templ_Type &operator () (unsigned int row, unsigned int column) const;

    double det() const;
};


/******************************************************************************
 * ! \brief Konstruktor klasy Matrix.                                         |
 |  Argumenty:                                                                |
 |      Brak argumentow.                                                      |
 |  Zwraca:                                                                   |
 |   \retval Macierz jednostkowa                                              |
 */
template <typename Templ_Type, unsigned int Templ_Size>
Matrix<Templ_Type,Templ_Size>::Matrix() {
    for (unsigned int i = 0; i < Templ_Size; i++) {
        for (unsigned int j = 0; j < Templ_Size; j++) {
            if( i == j)
                value[i][j] = 1;
            else
                value[i][j] = 0;
        }
    }
}



/******************************************************************************
 * ! \brief Konstruktor parametryczny klasy Matrix.                           |
 |  Argumenty:                                                                |
 |  \param tmp - dwuwymiarowa tablica z elementami typu double.               |
 |  Zwraca:                                                                   |
 |   \retval Macierz wypelniona wartosciami podanymi w argumencie.            |
 */
template <typename Templ_Type, unsigned int Templ_Size>
Matrix<Templ_Type,Templ_Size>::Matrix(Templ_Type tmp[Templ_Size][Templ_Size]) {
    for (unsigned int i = 0; i < Templ_Size; i++) {
        for (unsigned int j = 0; j < Templ_Size; j++) {
            value[i][j] = tmp[i][j];
        }
    }
}


/******************************************************************************
 * ! \brief Realizuje mnozenie macierzy przez wektor.                         |
 |  Argumenty:                                                                |
 |    \param  this - macierz, czyli pierwszy skladnik mnozenia,               |
 |    \param  tmp - wektor, czyli drugi skladnik mnozenia.                    |
 |  Zwraca:                                                                   |
 |     \retval Iloczyn dwoch skladnikow przekazanych jako wektor.             |
 */
template <typename Templ_Type, unsigned int Templ_Size>
Vector<Templ_Type,Templ_Size> Matrix<Templ_Type,Templ_Size>::operator * (Vector<Templ_Type,Templ_Size> tmp) {
    Vector<Templ_Type,Templ_Size> result;


    for (unsigned int i = 0; i < Templ_Size; i++) {
        for (unsigned int j = 0; j < Templ_Size; j++) {
            result[i] += value[i][j] * tmp[j];
        }
    }
    return result;
}



/******************************************************************************
 * ! \brief Funktor macierzy                                                  |
 |  Argumenty:                                                                |
 |    \param  row - numer wiersza.                                            |
 |    \param  column - numer kolumny.                                         |
 |  Zwraca:                                                                   |
 |     \retval Wartosc macierzy w danym miejscu tablicy.                      |
 */
template <typename Templ_Type, unsigned int Templ_Size>
Templ_Type &Matrix<Templ_Type,Templ_Size>::operator()(unsigned int row, unsigned int column) {

    if (row >= Templ_Size) {
        throw("Error: Macierz jest poza zasiegiem"); 
    }

    if (column >= Templ_Size) {
        throw("Error: Macierz jest poza zasiegiem");
    }

    return value[row][column];
}


/******************************************************************************
 * ! \brief Funktor macierzy                                                  |
 |  Argumenty:                                                                |
 |   \param row - numer wiersza.                                              |
 |   \param column - numer kolumny.                                           |
 |  Zwraca:                                                                   |
 |    \retval  Wartosc macierzy w danym miejscu tablicy jako stala.           |
 */
template <typename Templ_Type, unsigned int Templ_Size>
const Templ_Type &Matrix<Templ_Type,Templ_Size>::operator () (unsigned int row, unsigned int column) const {

    if (row >= Templ_Size) {
        throw("Error: Macierz jest poza zasiegiem");
    }

    if (column >= Templ_Size) {
        throw("Error: Macierz jest poza zasiegiem");
    }

    return value[row][column];
}

/******************************************************************************
 * ! \brief Przeciążenie dodawania macierzy                                   |
 |  Argumenty:                                                                |
 |   \param this - macierz, czyli pierwszy skladnik dodawania,                |
 |   \param v - wektor, czyli drugi skladnik dodawania.                       |
 |  Zwraca:                                                                   |
 |    \retval Macierz - iloczyn dwóch podanych macierzy.                      |
 */
template <typename Templ_Type, unsigned int Templ_Size>
Matrix<Templ_Type,Templ_Size> Matrix<Templ_Type,Templ_Size>::operator + (Matrix<Templ_Type,Templ_Size> tmp) {
    Matrix<Templ_Type,Templ_Size> result;
    for (unsigned int i = 0; i < Templ_Size; i++) {
        for (unsigned int j = 0; j < Templ_Size; j++) {
            result(i, j) = this->value[i][j] + tmp(i, j);
        }
    }
    return result;
}



/******************************************************************************
 * ! \brief Realizuje mnozenie dwoch macierzy                                 |
 |  Argumenty:                                                                |
 |    \param  this - macierz z lewej strony                                   |
 |    \param  tmp  - macierz z prawej strony                                  |
 |  Zwraca:                                                                   |
 |     \retval Nowa macierz kwadratowa                                        |
 */
template <typename Templ_Type, unsigned int Templ_Size>
Matrix<Templ_Type,Templ_Size> Matrix<Templ_Type,Templ_Size>::operator * (Matrix<Templ_Type,Templ_Size> tmp){
    Matrix Result;
    double sum;

    for(unsigned int i = 0; i < Templ_Size; ++i){

        for(unsigned int j = 0; j < Templ_Size ; ++j){
            sum = 0;
            for(unsigned int k = 0; k < Templ_Size; ++k){
                sum += value[i][k] * tmp(k,j);
            }
            Result(i,j) = sum;
        }
    }

    return Result;
}


/******************************************************************************
 * ! \brief Przeciazenie operatora >>                                         |
 |  Argumenty:                                                                |
 |    \param in  - strumien wyjsciowy,                                        |
 |    \param mat - macierz.                                                   |
 */
template <typename Templ_Type, unsigned int Templ_Size>
std::istream &operator>>(std::istream &in, Matrix<Templ_Type,Templ_Size> &mat) {
    for (unsigned int i = 0; i < Templ_Size; i++) {
        for (unsigned int j = 0; j < Templ_Size; j++) {
            in >> mat(i, j);
        }
    }
    return in;
}

/******************************************************************************
 * ! \brief Przeciazenie operatora <<                                         |
 |  Argumenty:                                                                |
 |      \param out - strumien wejsciowy,                                      |
 |      \param mat - macierz.                                                 |
 |  Zwraca:
 |      \retval out - strumien
 */
template <typename Templ_Type, unsigned int Templ_Size>
std::ostream &operator<<(std::ostream &out, const Matrix<Templ_Type,Templ_Size> &mat) {
    for (unsigned int i = 0; i < Templ_Size; i++) {
        for (unsigned int j = 0; j < Templ_Size; j++) {
            out << std::setw(17) << std::fixed << std::setprecision(10) << "| " << mat(i, j) << " | ";
        }
        std::cout << std::endl;
    }
    return out;
}


/******************************************************************************
 * ! \brief Wyznacznik macierzy                                               |
 |  Argumenty:                                                                |
 |      \param this - macierz, ktorej wyznacznik obliczamy                    
 |  Wynik:                                                                    |
 |       \retval Wyliczenie wyznacznika macierzy metoda eliminacji Gaussa     |
 */
template <typename Templ_Type, unsigned int Templ_Size>
double Matrix<Templ_Type,Templ_Size>::det() const{
    Matrix<Templ_Type,Templ_Size> tmp;
    tmp = *this;
    double ratio, result = 1;
    
    for(unsigned int i = 0; i < Templ_Size -1; ++i){
        if(tmp(i,i) == 0){
            std::cerr << "Macierz osobliwa " << std::endl;
            return 0;
        }
            
        for(unsigned int j = i + 1; j < Templ_Size; ++j){
            ratio = tmp(j,i)/tmp(i,i);
            for(unsigned int k = 0; k < Templ_Size; ++k){
                tmp(j,k) = tmp(j,k) - ratio * tmp(i,k);
            }
        }
    }

    for(unsigned int i = 0; i < Templ_Size; ++i){
        result *= tmp(i,i);
    }

    return result;
}





#endif
