#include <string>

#include "bmp_parser.hpp"

class ImageEditor {
    public:
        static void rotate(const std::string imagePath, const std::string outputPath);
        static void convert_to_grayscale(const std::string imagePath, const std::string outputPath);
};