#include <string>

#include "bmp_parser.hpp"

class ImageEditor {
    public:
        static void rotate(const std::string image_path, const std::string output_path);
        static void convert_to_grayscale(const std::string image_path, const std::string output_path);
};