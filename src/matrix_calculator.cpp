#include "matrix_calculator.hpp"

bool MatrixCalculator::is_matrix(std::string path) {
  std::ifstream file{path};
  if (!file) {
    return false;
  }
  uint32_t row_size = -1; // flag value -1
  std::string line;
  std::regex line_format{
      "(\\ *[0-9]+\\ *,)*\\ *[0-9]+\\ *"}; // how a line should look
  while (std::getline(file, line)) {
    if (!std::regex_search(line, line_format)) {
      std::cout << line << std::endl;
      file.close();
      return false;
    } else {
      uint32_t counter = 0;
      for (char &c : line) { //number of commas + 1 = number of numbers
        if (c == ',') {
          counter++;
        }
      }
      counter++;
      if (row_size == -1) {
        row_size == counter;
      } else if (row_size != counter) {
        file.close();
        return false;
      }
    }
  }
  file.close();
  return true;
}

Matrix MatrixCalculator::to_matrix(std::string path) {
  if (!is_matrix(path)) {
    std::cerr << "Matrix is invalid, exiting..." << std::endl;
    // return garbage matrix
    Matrix matrix(1, 1);
    return matrix;
  }
  std::ifstream file{path};
  std::string line;
  int height, width = 0;
  while (std::getline(file, line)) { //get the width and height
    if (width == 0) {
      for (char &c : line) {
        if (c == ',') {
          width++;
        }
      }
      width++;
    }
    height++;
  }
  auto matrix = std::make_unique<Matrix>(width, height);
  std::regex space("/s+"); // how spaces look in regex
  auto current_line = 0;
  while (std::getline(file, line)) {
    auto line_for_parse = std::regex_replace(
        line, space, ""); // delete all spaces, helps with parsing
    std::vector<std::string> nums;
    std::stringstream check(line_for_parse);
    std::string num;
    while (getline(check, num, ',')) {
      nums.push_back(num);
    }
    auto j = 0;
    for (auto &num : nums) {
      matrix->set_value(current_line, j, stod(num));
      j++;
    }
    current_line++;
  }
  file.close();
  return *matrix;
}


void MatrixCalculator::to_file(Matrix matrix, std::string path) {
  auto height = matrix.get_height(), width = matrix.get_width();
  std::ofstream file{path};
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (j == width - 1) {
        file << std::to_string(matrix.get_value(i, j));
      } else {
        file << std::to_string(matrix.get_value(i, j)) + ", ";
      }
    }
    file << std::endl;
  }
  file.close();
}

//take two file, each describes a matrix and adds them if possible
//and writes the result in an output file
// return true if both files do describe a matrix and false if not
bool MatrixCalculator::add(std::string path1, std::string path2, std::string output) {
  if (!is_matrix(path1) || !is_matrix(path2)) {
    std::cerr << "Either " << path1 << " or " << path2 << " is not a valid matrix file" << std::endl;
    return false;
  } else {
    auto matrix1 = to_matrix(path1);
    auto matrix2 = to_matrix(path2);
    matrix1.add_matrix(matrix2);
    to_file(matrix1, output);
    return true;
  }
}

// take two file, each describes a matrix and nultyplies them if possible
// and writes the result in an output file.
// return true if both files do describe a matric and false if not
bool MatrixCalculator::multiply(std::string path1, std::string path2,
                           std::string output) {
  if (!is_matrix(path1) || !is_matrix(path2)) {
    std::cerr << "Either " << path1 << " or " << path2 << " is not a valid matrix file" << std::endl;
    return false;
  } else {
    auto matrix1 = to_matrix(path1);
    auto matrix2 = to_matrix(path2);
    matrix1.multiply_by_matrix(matrix2);
    to_file(matrix1, output);
    return true;
  }
}