#include "matrix_class.hpp"
#include "matrix_class.hpp"
#include <fstream>
#include <regex>
#include <iostream>


struct MatrixCalculator{
    public:
    static void add(std::string path1, std::string path2, std::string output);
    static void multiply(std::string path1, std::string path2, std::string output);
    private:
    static bool is_matrix(std::string path);
    static Matrix parse_matrix(std::string path);
    static void parse_file(Matrix matrix, std::string path);
};