

#ifndef MATRIX_H
#define MATRIX_H
#include "Matrix.h"
class Matrix{

public:
    Matrix(int width, int height);
    int getHeight() const;
    int getWidth() const;
    void setValue(int i, int j, double value);
    double getValue(int i, int j) const;
    void addMatrix(const Matrix matToAdd);
    ~Matrix();
private:
    PMatrix matrix = nullptr;
    PMatrix getMatrix() const;
};
#endif