#include "cache_manager.hpp"

#include <fstream>
#include <iostream>
#include <dirent.h>

Cache::Cache() {}

Cache::Cache(const Cache& other) {}

Cache&Cache:: operator=(const Cache & other) {
    return *this;
}

bool Cache::is_file_in_cache(const std::string filepath) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("cache")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (filepath.compare(ent->d_name) == 0) {
                closedir (dir);
                return true;
            }
        }
        closedir (dir);
        return false;
    } else {
        throw std::runtime_error("Unable to open cache");
    }
}

void Cache::store(const std::string filepath) {
    if (!is_file_in_cache(filepath)) {
        std::string cache_filepath("cache/" + filepath);
        std::ifstream ifs(filepath, std::ios::binary);
        std::ofstream ofs(cache_filepath, std::ios::binary);
        if (!ifs || !ofs) {
            throw std::runtime_error("Unable to store file in cache");
        }
        ofs << ifs.rdbuf();
        remove(filepath.c_str());
    }
}

void Cache::search(const std::string filepath) {
    if (is_file_in_cache(filepath)) {
        std::cout << "result found in cache" << std::endl;
    } else {
        std::cout << "result not found in cache" << std::endl;
    }
}

void Cache::clear() {
    DIR *dir;
    struct dirent *ent;
    std::string cache_filepath;
    if ((dir = opendir("cache")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            cache_filepath = "cache/" + static_cast<std::string>(ent->d_name);
            remove(cache_filepath.c_str());
        }
        closedir (dir);
    } else {
        throw std::runtime_error("Unable to open cache");
    }
}

Cache::~Cache(){}