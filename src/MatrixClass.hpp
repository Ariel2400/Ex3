#pragma once

#include "Matrix.hpp"
class Matrix{

public:
    Matrix(int width, int height);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    int getHeight() const;
    int getWidth() const;
    void setValue(int i, int j, double value);
    double getValue(int i, int j) const;
    void addMatrix(const Matrix matToAdd);
    void multiplyByMatrix(const Matrix matToMultiplyBy);
    ~Matrix();
private:
    PMatrix matrix = nullptr;
    PMatrix getMatrix() const;
};