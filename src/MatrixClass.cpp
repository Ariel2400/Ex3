#include <memory>
#include <iostream>

#include <stdexcept>

#include "MatrixClass.hpp"

using namespace std;

Matrix::Matrix(int height, int width) { 
  ErrorCode code = matrix_create(&matrix, height, width);
  if (!error_isSuccess(code)) {
    throw std::runtime_error(error_getErrorMessage(code));
  }
}

Matrix::Matrix(const Matrix& other) {
  ErrorCode code = matrix_copy(&matrix, other.matrix);
  if (!error_isSuccess(code)) {
    throw std::runtime_error(error_getErrorMessage(code));
  }
}

Matrix & Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    matrix_destroy(matrix);
    ErrorCode code = matrix_copy(&matrix, other.matrix);
    if (!error_isSuccess(code)) {
      throw std::runtime_error(error_getErrorMessage(code));
    }
  }
  return *this;
}

PMatrix Matrix::getMatrix() const{
  return this->matrix;
}

int Matrix::getHeight() const {
  uint32_t height;
  ErrorCode code = matrix_getHeight(matrix, &height);
  if (!error_isSuccess(code)) {
    throw std::runtime_error(error_getErrorMessage(code));
  }
  return height;
}

int Matrix::getWidth() const {
  uint32_t width;
  ErrorCode code = matrix_getWidth(matrix, &width);
  if (!error_isSuccess(code)) {
    throw std::runtime_error(error_getErrorMessage(code));
  }
  return width;
}

void Matrix::setValue(int i, int j, double value) {
  ErrorCode code = matrix_setValue(matrix, i, j, value);
  if (!error_isSuccess(code)) {
    throw std::runtime_error(error_getErrorMessage(code));
  }
}

double Matrix::getValue(int i, int j) const {
  double result;
  ErrorCode code = matrix_getValue(matrix, i, j, &result);
  if (!error_isSuccess(code)) {
    throw std::runtime_error(error_getErrorMessage(code));
  }
  return result;
}

void Matrix::addMatrix(Matrix matToAdd){
  ErrorCode code = matrix_add(&matrix, matrix, matToAdd.matrix);
  if (!error_isSuccess(code)) {
    throw std::runtime_error(error_getErrorMessage(code));
  }
}

void Matrix::multiplyByMatrix(const Matrix matToMultiplyBy) {
  ErrorCode code = matrix_multiplyMatrices(&matrix, matrix, matToMultiplyBy.matrix);
  if (!error_isSuccess(code)) {
    throw std::runtime_error(error_getErrorMessage(code));
  }
}

Matrix::~Matrix() { 
  matrix_destroy(matrix); 
}


int main() {
  auto mat1 = std::make_unique<Matrix>(4, 4);
  auto mat2 = std::make_unique<Matrix>(4, 4);
  for (int i = 0; i < mat1->getHeight(); i++) {
    for (int j = 0; j < mat1->getWidth(); j++) {
      mat1->setValue(i, j, i * 10 + j);
    }
  }
  for (int i = 0; i < mat2->getHeight(); i++) {
    for (int j = 0; j < mat2->getWidth(); j++) {
      mat2->setValue(i, j, 2 * (i * 10 + j));
    }
  }
  for (int i = 0; i < mat1->getHeight(); i++) {
    for (int j = 0; j < mat1->getWidth(); j++) {
      std::cout << mat1->getValue(i, j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  for (int i = 0; i < mat2->getHeight(); i++) {
    for (int j = 0; j < mat2->getWidth(); j++) {
      std::cout << mat2->getValue(i, j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  mat1->addMatrix(*mat2);
  for (int i = 0; i < mat1->getHeight(); i++) {
    for (int j = 0; j < mat1->getWidth(); j++) {
      std::cout << mat1->getValue(i, j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  mat1->multiplyByMatrix(*mat2);
  for (int i = 0; i < mat1->getHeight(); i++) {
    for (int j = 0; j < mat1->getWidth(); j++) {
      std::cout << mat1->getValue(i, j) << " ";
    }
    std::cout << std::endl;
  }
}