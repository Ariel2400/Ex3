#include "matrix_calculator.hpp"

bool MatrixCalculator::is_matrix(std::string path) {
  std::ifstream file{path};
  uint32_t row_size = -1; // flag value -1
  std::string line;
  std::regex line_format{"(/s*[0-9]+/s*,)*/s*[0-9]+/s*"};
  while (std::getline(file, line)) {
    if (!std::regex_search(line, line_format)) {
      return false;
      file.close();
    } else {
      uint32_t counter = 0;
      for (char &c : line) {
        if (c == ',') {
          counter++;
        }
      }
      counter++;
      if (row_size == -1) {
        row_size == counter;
      } else if (row_size != counter) {
        return false;
        file.close();
      }
    }
  }
  return true;
}

Matrix MatrixCalculator::parse_matrix(std::string path){
    if(!is_matrix(path)){
        std::cerr << "Matrix is invalid, exiting..." << std::endl;
        return;
    }
    auto matrix = std::make_unique<Matrix>();
}