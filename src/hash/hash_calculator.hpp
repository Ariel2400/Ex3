#include <fstream>
#include <iostream>
#include <string>

#include "crc32.hpp"

struct HashCalculator {
private:
  /* encodes a file in crc32 hash
  returns true of the operation was done successfully, false if not */
  static bool encode(std::string path, uint32_t *remainder);

  /* writes the remainder in a file
  returns true of the operation was done successfully, false if not */
  static bool write(std::string path, uint32_t remainder);

public:
  /* reads a file and writes it's hashcode in an output file
  returns true of the operation was done successfully, false if not */
  static bool crc32(std::string input, std::string output);
};
