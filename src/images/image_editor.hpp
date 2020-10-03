#include <string>

#include "bmp_parser.hpp"

class ImageEditor {
public:
  /* takes a bmp-format image and rotates it, writing the result in a diffrent
  path returns true of the operation was done successfully, false if not */
  static bool rotate(const std::string image_path,
                     const std::string output_path);

  /* takes a bmp-format image and convers it to grayscale, writing the result in
  a diffrent path
  returns true of the operation was done successfully, false if not */
  static bool convert_to_grayscale(const std::string image_path,
                                   const std::string output_path);
};