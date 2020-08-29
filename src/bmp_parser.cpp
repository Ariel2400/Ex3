#include <memory>
#include <iostream>

#include "bmp_parser.hpp"

#define BMP_DECLARATION 0x4D42
#define FILE_INFO_END 14
#define FILE_DATA_HEAD_END 54
#define COLORS_IN_A_PIXEL 3
#define BLUE_COEF 0.0722
#define GREEN_COEF 0.7152
#define RED_COEF 0.2126
#define ALIGN_STRIDE 4
#define BITS_IN_A_BYTE 8

using std::vector;
class Matrix;

void BMP::init(const BMP& other) {
  file_header.file_type = other.file_header.file_type;
  file_header.file_size = other.file_header.file_size;
  file_header.reserved1 = other.file_header.reserved1;
  file_header.reserved2 = other.file_header.reserved2;
  file_header.offset_data = other.file_header.offset_data;
  bmp_info_header.size = other.bmp_info_header.size;
  bmp_info_header.width = other.bmp_info_header.width;
  bmp_info_header.height = other.bmp_info_header.height;
  bmp_info_header.planes = other.bmp_info_header.planes;
  bmp_info_header.bit_count = other.bmp_info_header.bit_count;
  bmp_info_header.compression = other.bmp_info_header.compression;
  bmp_info_header.size_image = other.bmp_info_header.size_image;
  bmp_info_header.x_pixels_per_meter = other.bmp_info_header.x_pixels_per_meter;
  bmp_info_header.y_pixels_per_meter = other.bmp_info_header.y_pixels_per_meter;
  bmp_info_header.colors_used = other.bmp_info_header.colors_used;
  bmp_info_header.colors_important = other.bmp_info_header.colors_important;
  bmp_color_palette.color_list = std::make_unique<Matrix>(*other.bmp_color_palette.color_list);
  bmp_color_palette.pixel_color_indexes = std::make_unique<Matrix>(*other.bmp_color_palette.pixel_color_indexes);
  pixels = std::make_unique<Matrix>(*other.pixels);
}

BMP::BMP(const std::string fname) { 
  read(fname); 
}

BMP::BMP(const BMP& other) {
  init(other);
}

BMP& BMP::operator=(const BMP& other) {
  if(this != &other) {
    init(other);
  }
  return *this;
}

void BMP::read(const std::string fname) {
  vector<uint8_t> data;
  std::ifstream inp{fname, std::ios_base::binary};
  if (inp) {
    //read headers
    inp.read((char *)&file_header, sizeof(file_header));
    if (file_header.file_type != BMP_DECLARATION) {
      throw std::runtime_error("Error! Unrecognized file format.");
    }
    inp.seekg(FILE_INFO_END, inp.beg);
    inp.read((char *)&bmp_info_header, sizeof(bmp_info_header));

    // Jump to the pixel data location
    inp.seekg(file_header.offset_data, inp.beg);

    data.resize(bmp_info_header.width * bmp_info_header.height *
                bmp_info_header.bit_count / BITS_IN_A_BYTE);

    if (bmp_info_header.bit_count == 24) {
      read_24_bit(&inp, data);
    } else if (bmp_info_header.bit_count == 8) {
      read_8_bit(&inp);
    } else {
      throw std::runtime_error(
          "The program can treat only 24 or 8 bits per pixel BMP files");
    }
  } else {
    throw std::runtime_error("Unable to open the input image file.");
  }
}

void BMP::write(const std::string fname) {
  vector<uint8_t> data = matrix_to_vector(pixels);
  std::ofstream of{fname, std::ios_base::binary};
  if (of) {
    if (bmp_info_header.bit_count == 24) {
      write_24_bit(of, data);
    } else if (bmp_info_header.bit_count == 8) {
      write_8_bit(of);
    } else {
      throw std::runtime_error(
          "The program can treat only 24 or 8 bits per pixel BMP files");
    }
  } else {
    throw std::runtime_error("Unable to open the output image file.");
  }
}

void BMP::convert_to_grayscale() {
  //convert pixel matrix
  for (int i = 0; i < bmp_info_header.height; ++i) {
    for (int j = 0; j < bmp_info_header.width; ++j) {
      double b = pixels->get_value(i, COLORS_IN_A_PIXEL * j);
      double g = pixels->get_value(i, COLORS_IN_A_PIXEL * j + 1);
      double r = pixels->get_value(i, COLORS_IN_A_PIXEL * j + 2);
      double grayscale = BLUE_COEF * b + GREEN_COEF * g + RED_COEF * r;
      pixels->set_value(i, COLORS_IN_A_PIXEL * j, grayscale);
      pixels->set_value(i, COLORS_IN_A_PIXEL * j + 1, grayscale);
      pixels->set_value(i, COLORS_IN_A_PIXEL * j + 2, grayscale);
    }
  }
  if (bmp_info_header.bit_count == 8) {
    //convert color pallette
    for (int i = 0; i < bmp_color_palette.color_list->get_height(); ++i) {
      double b = bmp_color_palette.color_list->get_value(i, 0);
      double g = bmp_color_palette.color_list->get_value(i, 1);
      double r = bmp_color_palette.color_list->get_value(i, 2);
      double grayscale = BLUE_COEF * b + GREEN_COEF * g + RED_COEF * r;
      bmp_color_palette.color_list->set_value(i, 0, grayscale);
      bmp_color_palette.color_list->set_value(i, 1, grayscale);
      bmp_color_palette.color_list->set_value(i, 2, grayscale);
    }
  }
}

void BMP::rotate_image() {
  //swap height and width values
  uint32_t temp = bmp_info_header.height;
  bmp_info_header.height = bmp_info_header.width;
  bmp_info_header.width = temp;
  //swap x and y pixels per meter values
  temp = bmp_info_header.x_pixels_per_meter;
  bmp_info_header.x_pixels_per_meter = bmp_info_header.y_pixels_per_meter;
  bmp_info_header.y_pixels_per_meter = temp;
  //pixel (i,j) in the new image corresponds to pixel (j,height-i-1) in the existing image
  std::unique_ptr<Matrix> rotated_pixels =
      std::make_unique<Matrix>(bmp_info_header.height, bmp_info_header.width * COLORS_IN_A_PIXEL);
  for (int i = 0; i < bmp_info_header.height; ++i) {
    for (int j = 0; j < bmp_info_header.width; ++j) {
      rotated_pixels->set_value(
          i, COLORS_IN_A_PIXEL * j, pixels->get_value(j, COLORS_IN_A_PIXEL * (bmp_info_header.height - i - 1)));
      rotated_pixels->set_value(
          i, COLORS_IN_A_PIXEL * j + 1,
          pixels->get_value(j, COLORS_IN_A_PIXEL * (bmp_info_header.height - i - 1) + 1));
      rotated_pixels->set_value(
          i, COLORS_IN_A_PIXEL * j + 2,
          pixels->get_value(j, COLORS_IN_A_PIXEL * (bmp_info_header.height - i - 1) + 2));
    }
  }
  pixels = std::make_unique<Matrix>(*rotated_pixels);
  if (bmp_info_header.bit_count == 8) {
    //rotate the indexes matrix
    std::unique_ptr<Matrix> rotated_pixel_color_indexes = std::make_unique<Matrix>(bmp_info_header.height, bmp_info_header.width);
    for (int i = 0; i < bmp_info_header.height; ++i) {
      for (int j = 0; j < bmp_info_header.width; ++j) {
        rotated_pixel_color_indexes->set_value(
            i, j,
            bmp_color_palette.pixel_color_indexes->get_value(
                j, bmp_info_header.height - i - 1));
      }
    }
    bmp_color_palette.pixel_color_indexes = std::make_unique<Matrix>(*rotated_pixel_color_indexes);
  }
}

BMP::~BMP() {}

//calculate the minimum number that needs to be added to 'num' to make it divisible by 'align'
uint32_t BMP::padding_to(uint32_t num, uint32_t align) {
  uint32_t padding = 0;
  while((num + padding) % align != 0) {
    padding++;
  }
  return padding;
}

std::unique_ptr<Matrix> BMP::vector_to_matrix(vector<uint8_t> vector, int height, int width) {
  std::unique_ptr<Matrix> matrix = std::make_unique<Matrix>(height, width);
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      matrix->set_value(i, j, vector[i * width + j]);
    }
  }
  return matrix;
}

vector<uint8_t> BMP::matrix_to_vector(std::unique_ptr<Matrix> & matrix) {
  vector<uint8_t> vector;
  vector.resize(matrix->get_height() * matrix->get_width());
  for (int i = 0; i < matrix->get_height(); ++i) {
    for (int j = 0; j < matrix->get_width(); ++j) {
      vector.at(i * matrix->get_width() + j) = matrix->get_value(i, j);
    }
  }
  return vector;
}

void BMP::write_headers(std::ofstream &of) {
  of.write((const char *)&file_header, sizeof(file_header));
  of.write((const char *)&bmp_info_header, sizeof(bmp_info_header));
}

void BMP::write_headers_and_data(std::ofstream &of, vector<uint8_t> data) {
  write_headers(of);
  of.write((const char *)data.data(), data.size());
}

void BMP::read_24_bit(std::ifstream *inp, vector<uint8_t> data) {
  if (bmp_info_header.width % ALIGN_STRIDE == 0) {
    inp->read((char *)data.data(), data.size());
    file_header.file_size += data.size();
  } else {
    uint32_t row_stride =
        bmp_info_header.width * bmp_info_header.bit_count / BITS_IN_A_BYTE;
    uint32_t padding_size = padding_to(row_stride, ALIGN_STRIDE);
    std::vector<uint8_t> padding_row(padding_size);
    for (int i = 0; i < bmp_info_header.height; ++i) {
      inp->read((char *)(data.data() + row_stride * i), row_stride);
      inp->read((char *)padding_row.data(), padding_row.size());
    }
    file_header.file_size +=
        data.size() + bmp_info_header.height * padding_row.size();
  }
  pixels =
      vector_to_matrix(data, bmp_info_header.height, bmp_info_header.width * COLORS_IN_A_PIXEL);
}

void BMP::read_8_bit(std::ifstream *inp) {
  inp->seekg(FILE_DATA_HEAD_END, inp->beg);
  int color_palette_size = file_header.offset_data - FILE_DATA_HEAD_END;
  int num_of_colors = color_palette_size / ALIGN_STRIDE;
  std::vector<uint8_t> bgr_values(num_of_colors * COLORS_IN_A_PIXEL);
  std::vector<uint8_t> padding(ALIGN_STRIDE - COLORS_IN_A_PIXEL);
  for (int i = 0; i < num_of_colors; ++i) {
    inp->read((char *)(bgr_values.data() + COLORS_IN_A_PIXEL * i), COLORS_IN_A_PIXEL);
    inp->read((char *)padding.data(), padding.size());
  }
  //bgr values of color number i are stored in color_list(i,0), color_list(i,1), color_list(i,2)
  bmp_color_palette.color_list = vector_to_matrix(bgr_values, num_of_colors, COLORS_IN_A_PIXEL);
  std::vector<uint8_t> color_indexes(bmp_info_header.height *
                                     bmp_info_header.width);
  if (bmp_info_header.width % ALIGN_STRIDE == 0) {
    inp->read((char *)color_indexes.data(), color_indexes.size());
  } else {
    uint32_t row_stride = bmp_info_header.width * bmp_info_header.bit_count / BITS_IN_A_BYTE;
    uint32_t padding_size = padding_to(row_stride, ALIGN_STRIDE);
    std::vector<uint8_t> padding_row(padding_size);
    for (int i = 0; i < bmp_info_header.height; ++i) {
      inp->read((char *)(color_indexes.data() + row_stride * i),
                row_stride);
      inp->read((char *)padding_row.data(), padding_row.size());
    }
  }
  bmp_color_palette.pixel_color_indexes = vector_to_matrix(
      color_indexes, bmp_info_header.height, bmp_info_header.width);
  //update the pixels matrix according to the color list and the indexes matrix
  pixels = std::make_unique<Matrix>(bmp_info_header.height, bmp_info_header.width * COLORS_IN_A_PIXEL);
  for (int i = 0; i < bmp_info_header.height; ++i) {
    for (int j = 0; j < bmp_info_header.width; ++j) {
      pixels->set_value(
          i, COLORS_IN_A_PIXEL * j,
          bmp_color_palette.color_list->get_value(
              bmp_color_palette.pixel_color_indexes->get_value(i, j), 0));
      pixels->set_value(
          i, COLORS_IN_A_PIXEL * j + 1,
          bmp_color_palette.color_list->get_value(
              bmp_color_palette.pixel_color_indexes->get_value(i, j), 1));
      pixels->set_value(
          i, COLORS_IN_A_PIXEL * j + 2,
          bmp_color_palette.color_list->get_value(
              bmp_color_palette.pixel_color_indexes->get_value(i, j), 2));
    }
  }
}

void BMP::write_24_bit(std::ofstream &of, vector<uint8_t> data) {
  if (bmp_info_header.width % ALIGN_STRIDE == 0) {
    write_headers_and_data(of, data);
  } else {
    write_headers(of);
    uint32_t row_stride = bmp_info_header.width * bmp_info_header.bit_count / BITS_IN_A_BYTE;
    uint32_t padding_size = padding_to(row_stride, ALIGN_STRIDE);
    std::vector<uint8_t> padding_row(padding_size);  
    for (int y = 0; y < bmp_info_header.height; ++y) {
      of.write((const char *)(data.data() + row_stride * y), row_stride);
      of.write((const char *)padding_row.data(), padding_row.size());
    }
  }
}

void BMP::write_8_bit(std::ofstream &of) {
  write_headers(of);
  std::vector<uint8_t> color_palette =
      matrix_to_vector(bmp_color_palette.color_list);
  std::vector<uint8_t> color_palette_padding(ALIGN_STRIDE - COLORS_IN_A_PIXEL);
  int num_of_colors = bmp_color_palette.color_list->get_height();
  for (int i = 0; i < num_of_colors; ++i) {
    of.write((const char *)(color_palette.data() + COLORS_IN_A_PIXEL * i), COLORS_IN_A_PIXEL);
    of.write((const char *)color_palette_padding.data(), color_palette_padding.size());
  }
  std::vector<uint8_t> pixel_color_indexes =
      matrix_to_vector(bmp_color_palette.pixel_color_indexes);
  if (bmp_info_header.width % ALIGN_STRIDE == 0) {
    of.write((const char *)pixel_color_indexes.data(),
             pixel_color_indexes.size());
  } else {
    uint32_t row_stride = bmp_info_header.width * bmp_info_header.bit_count / BITS_IN_A_BYTE;
    uint32_t padding_size = padding_to(row_stride, ALIGN_STRIDE);
    std::vector<uint8_t> pixel_color_indexes_padding(padding_size);
    for (int i = 0; i < bmp_info_header.height; ++i) {
      of.write((const char *)(pixel_color_indexes.data() + row_stride * i),
               row_stride);
      of.write((const char *)pixel_color_indexes_padding.data(),
               pixel_color_indexes_padding.size());
    }
  }
}