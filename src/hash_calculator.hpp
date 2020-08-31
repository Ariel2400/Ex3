#include <fstream>
#include <string>
#include <iostream>

#include "crc32.h"

struct HashCalculator {
  private:
    //encodes a file in crc32 hash
    static uint32_t encode(std::string path);
    // writes the remainder in a file
    static void write(std::string path, uint32_t remainder);
  public:
    //reads a file and writes it's hashcode in an output file
    static void crc32(std::string input, std::string output);
};
