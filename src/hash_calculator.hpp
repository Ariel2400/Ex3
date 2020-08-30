#include "crc32.h"
#include <fstream>
#include <string>
struct HashCalculator {
  private:
  static uint32_t encode(std::string path);
  static void write(std::string path, uint32_t remainder);
  static void crc32(std::string input, std::string output);
};
