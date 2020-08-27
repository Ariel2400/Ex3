#include <cstdbool>
#include <fstream>
#include <regex>
#include <MatrixClass.hpp>

Matrix read_matrix_from_file(const char* file_path){
    std::ifstream file(file_path);
    if(is_matrix(file)){
        
    }
}
bool is_matrix(std::ifstream file){
    std::basic_regex number = "[0-9]+"
    std::regex valid_line = "(/s*[0-9]+/s*,)*[0-9]+/s*"

}