#include "crc32.h"
#include <fstream>
#include <string>
#include <iostream>
struct HashCalculator {
  private:
  static uint32_t encode(std::string path);
  static void write(std::string path, uint32_t remainder);
  public:
  static void crc32(std::string input, std::string output);
};
