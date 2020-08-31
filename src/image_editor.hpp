#include <string>

#include "bmp_parser.hpp"

class ImageEditor {
    public:
        //takes a bmp-format image and rotates it, writing the result in a diffrent path
        static void rotate(const std::string image_path, const std::string output_path);
        //converts a bmp-format image to grayscale
        static void convert_to_grayscale(const std::string image_path, const std::string output_path);
};