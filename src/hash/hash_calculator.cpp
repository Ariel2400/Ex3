#include <iostream>

#include "hash_calculator.hpp"

bool HashCalculator::encode(std::string path, uint32_t *remainder) {
  std::ifstream file{path, std::ios::binary};
  if (!file) {
    std::cerr << "Can't open file " << path << std::endl;
    return false;
  } else {
    std::string buffer((std::istreambuf_iterator<char>(file)),
                       (std::istreambuf_iterator<char>()));
    const unsigned char *c_buffer =
        reinterpret_cast<const unsigned char *>(buffer.c_str());
    *remainder = calculate_crc32c(0, c_buffer, buffer.length());
    file.close();
    return true;
  }
}

bool HashCalculator::write(std::string path, uint32_t remainder) {
  std::ofstream file{path};
  if (!file) {
    std::cerr << "Can't write into file " << path << std::endl;
    return false;
  } else {
    file << std::to_string(remainder) << std::endl;
    file.close();
    return true;
  }
}

bool HashCalculator::crc32(std::string input, std::string output) {
  uint32_t remainder;
  if (!encode("../" + input, &remainder)) {
    return false;
  }
  if (!write("../" + output, remainder)) {
    return false;
  }
  return true;
}
