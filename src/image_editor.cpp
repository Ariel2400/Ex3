#include "image_editor.hpp"

void ImageEditor::rotate(const std::string image_path, const std::string output_path) {
    BMP bmp(image_path);
    bmp.rotate_image();
    bmp.write(output_path);
}

void ImageEditor::convert_to_grayscale(const std::string image_path, const std::string output_path) {
    BMP bmp(image_path);
    bmp.convert_to_grayscale();
    bmp.write(output_path);
}