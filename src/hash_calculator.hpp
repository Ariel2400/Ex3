#include "crc32.h"
#include <fstream>
#include <string>
struct hash {
  uint32_t remainder;
  void read(std::string path);
  void write(std::string path);
};
