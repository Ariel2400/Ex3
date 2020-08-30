#include "hash_calculator.hpp"

uint32_t HashCalculator::encode(std::string path) {
  std::ifstream file{path, std::ios::in};
  if (!file) {
    std::runtime_error("can't open file!");
  } else {
    std::string buffer((std::istreambuf_iterator<char>(file)),
                       (std::istreambuf_iterator<char>()));
    const unsigned char *c_buffer =
        reinterpret_cast<const unsigned char *>(buffer.c_str());
    uint32_t remainder = calculate_crc32c(0, c_buffer, buffer.length());
    file.close();
    return remainder;
  }
}
void HashCalculator::write(std::string path, uint32_t remainder) {
  std::ofstream file{path};
  if (!file) {
    std::runtime_error("can't open this file to write!");
  } else {
    file << (char *)remainder << std::endl;
    file.close();
  }
}

void HashCalculator::crc32(std::string input, std::string output){
  write(output, encode(input));
}
