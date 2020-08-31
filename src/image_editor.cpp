#include <memory>

#include "image_editor.hpp"

bool ImageEditor::rotate(const std::string image_path, const std::string output_path) {
    auto bmp = std::make_unique<BMP>();
    if (!bmp->read(image_path)) {
        return false;
    }
    bmp->rotate_image();
    bmp->write(output_path);
    return true;
}

bool ImageEditor::convert_to_grayscale(const std::string image_path, const std::string output_path) {
    auto bmp = std::make_unique<BMP>();
    if (!bmp->read(image_path)) {
        return false;
    }
    bmp->convert_to_grayscale();
    bmp->write(output_path);
    return true;
}