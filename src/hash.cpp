#include <fstream>
#include "crc32.h"
 struct hash
 {
    uint32_t remainder;
    void read(std::string path){
        std::ifstream file{path, std::ios::in};
        if(!file){
            std::runtime_error("can't open file!");
        }else{
            std::string buffer;
            file.read(&buffer, );
        }
        
 };
 