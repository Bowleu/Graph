#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "squareMatrix.h"
#include <QDebug>
using namespace std;


template <class Number>
class Matrix
{
protected:
    int n, m;  // n - height; m - length
    Number* values;
    int borderingMinorsMaxRank(int row, int column, int size);
public:
    Matrix();
    Matrix(int n, int m);
    Matrix(const Matrix &m);
    Matrix* algComp(int row, int column, int a);
    Number determinant();
    Matrix transponate();
    int rank();
    template <class M>
    friend ostream& operator << (ostream &st, Matrix<M> m);
    Number &operator [](int index);
    int getN();
    int getM();
    ~Matrix();
};

template <class Number>
Matrix<Number>::Matrix() {
    m = 0;
    n = 0;
    values = nullptr;
}

template <class Number>
Matrix<Number>::Matrix(int n, int m) {
    this->n = n;
    this->m = m;
    values = new Number[n * m];
    for (int i = 0; i < n * m; i++) {
        values[i] = 0;
    }
}

template <class Number>
Matrix<Number>::~Matrix() {
    if (values)
        delete [] values;
}

template <class Number>
Matrix<Number>::Matrix(const Matrix &mat) {
    m = mat.m;
    n = mat.n;
    values = new Number[n * m];
    for (int i = 0; i < n * m; i++) {
        values[i] = mat.values[i];
    }
}

template <class Number>
Number& Matrix<Number>::operator[](int i){
    return values[i];
}

template <class Number>
Matrix<Number> Matrix<Number>::transponate() {
    Matrix transponatedMatrix(m, n);
    for (int i = 0; i < m * n; i++) {
        int row = i / m;
        int column = i % m;
        transponatedMatrix[column * n + row] = values[i];
    }
    swap(m, n);
    return transponatedMatrix;
}

template <class Number>
int Matrix<Number>::borderingMinorsMaxRank(int row, int column, int size) {
    int rang = 1;
    int maxRang = min(m, n);
    Matrix<Number> currMinor(size, size);
    int k = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            currMinor[k] = values[(row + i) * m + column + j];
            k++;
        }
    }
    if (currMinor.determinant() != 0) {
        rang = size;
    }
    if (row > 0 and column + size < m) { // right-up
        rang = max(borderingMinorsMaxRank(row - 1, column, size + 1), rang);
        if (rang == maxRang) {
            return rang;
        }
    }
    if (row + size < n and column + size < m) { // right-down
        rang = max(borderingMinorsMaxRank(row, column, size + 1), rang);
        if (rang == maxRang) {
            return rang;
        }
    }
    if (row + size < n and column > 0) {  // left-down
        rang = max(borderingMinorsMaxRank(row, column - 1, size + 1), rang);
        if (rang == maxRang) {
            return rang;
        }
    }
    if (row > 0 and column > 0) { // left-up
        rang = max(borderingMinorsMaxRank(row - 1, column - 1, size + 1), rang);
        if (rang == maxRang) {
            return rang;
        }
    }
    return rang;
}

template <class Number>
ostream& operator << (ostream &st, Matrix<Number> mat) {
    for (int i = 0; i < mat.m * mat.n; i++) {
        st << mat[i] << ' ';
        if ((i + 1) % mat.m == 0)
            st << '\n';
    }
    return st;
}

template <class Number>
int Matrix<Number>::rank() {
    int rang = 0;
    //qDebug() << n << ' ' << m;
    for (int i = 0; i < n * m; i++) {
        if (values[i] != 0) {
            rang = max(borderingMinorsMaxRank(i / m, i % m, 1), rang);
            if (rang == min(n, m))
                return rang;
        }
    }
    return rang;
}

template <class Number>
Matrix<Number>* Matrix<Number>::algComp(int row, int column, int a) {
    Matrix* newSquareMatrix = new Matrix(m-1, m-1);
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
Number Matrix<Number>::determinant() {
    if (m!=n) return 0;
    if (m == 1) {
        return this->values[0];
    }
    if (m == 2) {
        Number determinant = this->values[0] * this->values[3] - this->values[1] * this->values[2];
        return determinant;
    }
    Number determinant = 0;
    Matrix* algCompMat = nullptr;
    for (int i = 0; i < m; i++) {
        if (this->values[i] != 0) {
            algCompMat = algComp(0, i, m);
            Number algCompDet = algCompMat->determinant();
            delete algCompMat;
            determinant = determinant + this->values[i] * pow(-1, i) * algCompDet;
        }
    }
    return determinant;
}

template <class Number>
int Matrix<Number>::getN() {
    return n;
}

template <class Number>
int Matrix<Number>::getM() {
    return m;
}

#endif // MATRIX_H
