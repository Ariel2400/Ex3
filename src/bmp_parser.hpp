#pragma once

#include <fstream>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <memory>

#include "matrix_class.hpp"


using std::vector;

#pragma pack(push, 1)
struct BMPFileHeader {
  uint16_t file_type{0x4D42}; // File type always BM which is 0x4D42
  uint32_t file_size{0};      // Size of the file (in bytes)
  uint16_t reserved1{0};      // Reserved, always 0
  uint16_t reserved2{0};      // Reserved, always 0
  uint32_t offset_data{0}; // Start position of pixel data (bytes from the beginning of the file)
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BMPInfoHeader {
  uint32_t size{0};   // Size of this header (in bytes)
  int32_t width{0};   // Width of bitmap in pixels
  int32_t height{0};  // Width of bitmap in pixels
  uint16_t planes{1}; // No. of planes for the target device, this is always 1
  uint16_t bit_count{0}; // No. of bits per pixel
  uint32_t compression{
      0}; // Compression method. We assume no compression, therefore always 0
  uint32_t size_image{0}; // 0 - for uncompressed images
  int32_t x_pixels_per_meter{0};
  int32_t y_pixels_per_meter{0};
  uint32_t colors_used{0}; // No. color indexes in the color table. Use 0 for
                           // The max number of colors allowed by bit_count
  uint32_t colors_important{0}; // No. of colors used for displaying the bitmap
                                // If 0 all colors are required
};
#pragma pack(pop)

#pragma pack(push, 1)
// BMPColorPalette is only used for 8 bits per pixels bmp files
struct BMPColorPalette {
  std::unique_ptr<Matrix> color_list = nullptr; // The list of colors for the image
  std::unique_ptr<Matrix> pixel_color_indexes = nullptr; // Each pixel's color's index according to the color list
};
#pragma pack(pop)
struct BMP {
  BMPFileHeader file_header;
  BMPInfoHeader bmp_info_header;
  BMPColorPalette bmp_color_palette;

  //Matrix "pixels" has the same height and thrice the width of the image
  //The bgr values of pixel (i,j) are stored in pixels(i, 3j), pixels(i, 3j+1), pixels(i, 3j+2)
  std::unique_ptr<Matrix> pixels = nullptr;

public:
  BMP(const std::string fname);
  BMP(const BMP& other);
  BMP& operator=(const BMP& other);
  void read(const std::string fname);
  void write(const std::string fname);
  void convert_to_grayscale();
  void rotate_image();
  ~BMP();

private:
  void init(const BMP& other);
  uint32_t padding_to(uint32_t num, uint32_t align) const;
  std::unique_ptr<Matrix> vector_to_matrix(vector<uint8_t> vector, int height, int width) const;
  vector<uint8_t> matrix_to_vector(std::unique_ptr<Matrix> & matrix);
  void write_headers(std::ofstream &of) const;
  void write_headers_and_data(std::ofstream &of, vector<uint8_t> data) const;
  void read_24_bit(std::ifstream *inp, vector<uint8_t> data);
  void read_8_bit(std::ifstream *inp);
  void write_24_bit(std::ofstream &of, vector<uint8_t> data) const;
  void write_8_bit(std::ofstream &of);
};
