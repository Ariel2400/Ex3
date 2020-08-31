#include "matrix_class.hpp"
#include <fstream>
#include <regex>
#include <iostream>
#include <bits/stdc++.h>


struct MatrixCalculator{
    public:
        static bool add(std::string path1, std::string path2, std::string output);
        static bool multiply(std::string path1, std::string path2, std::string output);
    private:
        static bool is_matrix(std::string path);
        static Matrix to_matrix(std::string path);
        static void to_file(Matrix matrix, std::string path);
};