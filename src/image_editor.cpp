#include "image_editor.hpp"

void ImageEditor::rotate_image(const std::string imagePath, const std::string outputPath) {
    BMP bmp(imagePath);
    bmp.rotate_image();
    bmp.write(outputPath);
}

void ImageEditor::convert_to_grayscale(const std::string imagePath, const std::string outputPath) {
    BMP bmp(imagePath);
    bmp.convert_to_grayscale();
    bmp.write(outputPath);
}