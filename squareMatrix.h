#ifndef SquareMatrix_H
#define SquareMatrix_H
#include <iostream>
#include <cmath>

#include "matrix.h"

using namespace std;
template <class Number>
class SquareMatrix : public Matrix<Number>
{

    int a;
    SquareMatrix* algComp(int row, int column, int a);
public:
    SquareMatrix();
    SquareMatrix(int a);
    SquareMatrix(const SquareMatrix &m);
    Number determinant();
    Number &operator [](int index);
    int size();
    SquareMatrix transponate();
};

template <class Number>
SquareMatrix<Number>::SquareMatrix() : Matrix<Number>(){
    a = 0;
}

template <class Number>
SquareMatrix<Number>::SquareMatrix(int a) : Matrix<Number>(a, a)
{
    this->a = a;
}

template <class Number>
int SquareMatrix<Number>::size() {
    return a;
}

template <class Number>
SquareMatrix<Number>::SquareMatrix(const SquareMatrix<Number> &mat) {
    a = mat.a;
    this->m = a; //this-> нужен для того чтобы при наследовании шаблона child видел переменные без <Number>. можно заменить на Matrix<Number>m = a;
    this->n = a;
    this->values = new Number[a * a];
    for (int i = 0; i < a * a; i++) {
        this->values[i] = mat.values[i];
    }
}

template <class Number>
SquareMatrix<Number>* SquareMatrix<Number>::algComp(int row, int column, int a) {
    SquareMatrix* newSquareMatrix = new SquareMatrix(a - 1);
    int k = 0;
    for (int i = 0; i < a * a; i++) {
        if (i / a != row) {
            if (i % a != column) {
                (*newSquareMatrix)[k] = (*this)[i];
                k++;
            }
        }
    }
    return newSquareMatrix;
}

template <class Number>
Number SquareMatrix<Number>::determinant() {
    if (a == 1) {
        return this->values[0];
    }
    if (a == 2) {
        Number determinant = this->values[0] * this->values[3] - this->values[1] * this->values[2];
        return determinant;
    }
    Number determinant = 0;
    SquareMatrix* algCompMat = nullptr;
    for (int i = 0; i < a; i++) {
        if (this->values[i] != 0) {
            algCompMat = algComp(0, i, a);
            Number algCompDet = algCompMat->determinant();
            delete algCompMat;
            determinant = determinant + this->values[i] * pow(-1, i) * algCompDet;
        }
    }
    return determinant;
}

template <class Number>
Number &SquareMatrix<Number>::operator[](int index) {
    return Matrix<Number>::operator[](index);
}

template <class Number>
SquareMatrix<Number> SquareMatrix<Number>::transponate() {
    SquareMatrix transponatedMatrix(a);
    for (int i = 0; i < a * a; i++) {
        int row = i / a;
        int column = i % a;
        transponatedMatrix[column * a + row] = this->values[i];
    }
    return transponatedMatrix;
}

#endif // SquareMatrix_H

