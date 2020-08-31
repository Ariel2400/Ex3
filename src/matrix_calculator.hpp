#include "matrix_class.hpp"
#include <fstream>
#include <regex>
#include <iostream>
#include <bits/stdc++.h>


struct MatrixCalculator{
    public:
    /*take two file, each describes a matrix and adds them if possible
    and writes the result in an output file*/
    static bool add(std::string path1, std::string path2, std::string output);
    /*take two file, each describes a matrix and nultyplies them if possible
    and writes the result in an output file*/
    static bool multiply(std::string path1, std::string path2, std::string output);
    private:
    /* checks if a file has a legal matrix(numbers with comma seperators, same
    number of numbers in each line)*/
    static bool is_matrix(std::string path);
    // read file to a matrix object
    static Matrix to_matrix(std::string path);
    // write matrix object to file
    static void to_file(Matrix matrix, std::string path);

};