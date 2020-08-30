#include "cache_manager.hpp"

#include <fstream>
#include <iostream>
#include <dirent.h>

Cache::Cache() {}

Cache::Cache(const Cache& other) {}

Cache& Cache::operator=(const Cache & other) {
    return *this;
}

bool Cache::is_file_in_cache(const std::string file_name_in_cache) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("cache")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (file_name_in_cache.compare(ent->d_name) == 0) {
                closedir (dir);
                return true;
            }
        }
        closedir (dir);
        return false;
    } else {
        std::cerr << "Unable to open cache" << std::endl;
        return false;
    }
}

void Cache::search(const std::string file_name_in_cache) {
    if (is_file_in_cache(file_name_in_cache)) {
        std::cout << "result found in cache" << std::endl;
    } else {
        std::cout << "result not found in cache" << std::endl;
    }
}

void Cache::store_into(const std::string src_file_name, const std::string file_name_in_cache) {
    if (!is_file_in_cache(file_name_in_cache)) {
        std::string cache_path("cache/" + file_name_in_cache);
        std::ifstream ifs(src_file_name, std::ios::binary);
        std::ofstream ofs(cache_path, std::ios::binary);
        if (!ifs || !ofs) {
            std::cerr << "Unable to store file in cache" << std::endl;
        }
        ofs << ifs.rdbuf();
    }
}

void Cache::load_from(const std::string file_name_in_cache, const std::string dest_file_name) {
    if (is_file_in_cache(file_name_in_cache)) {
        std::string cache_path("cache/" + file_name_in_cache);
        std::ifstream ifs(cache_path, std::ios::binary);
        std::ofstream ofs(dest_file_name, std::ios::binary);
        if (!ifs || !ofs) {
            std::cerr << "Unable to load file from cache" << std::endl;
        }
        ofs << ifs.rdbuf();
    } else {
        std::cerr << "File not in cache" << std::endl;
    }
}

void Cache::print(const std::string file_name_in_cache) {
    if (is_file_in_cache(file_name_in_cache)) {
        std::string cache_path("cache/" + file_name_in_cache);
        std::ifstream ifs(cache_path);
        if (ifs.is_open()) {
            std::cout << ifs.rdbuf();
            std::cout << std::endl;
        } else {
            std::cerr << "Unable to open file" << std::endl;
        }      
    } else {
        std::cerr << "File not in cache" << std::endl;
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
        std::cerr << "Unable to open cache" << std::endl;
    }
}

Cache::~Cache(){}