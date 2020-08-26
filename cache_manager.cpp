#include "cache_manager.hpp"

#include <string.h>
#include <fstream>
#include <memory>
#include <iostream>
#include <stdlib.h>
#include <dirent.h>

#define CACHE_PREFIX_LENGTH 6

Cache::Cache() {}

Cache::Cache(const Cache& other) {}

Cache&Cache:: operator=(const Cache & other) {
    return *this;
}

void Cache::store(char* filepath) {
    char* cache_filepath = static_cast<char*>(malloc(CACHE_PREFIX_LENGTH * sizeof(char)));
    strcpy(cache_filepath, "cache/");
    strcat(cache_filepath, filepath);
    std::ifstream ifs(filepath, std::ios::binary);
    std::ofstream ofs(cache_filepath, std::ios::binary);
    if (!ifs || !ofs) {
        throw std::runtime_error("Unable to store file in cache");
    }
    ofs << ifs.rdbuf();
}

void Cache::search(char* filepath) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("cache")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strcmp(ent->d_name, filepath) == 0) {
                std::cout << "result found in cache" << std::endl;
                closedir (dir);
                return;
            }
        }
        std::cout << "result not found in cache" << std::endl;
        closedir (dir);
    } else {
        throw std::runtime_error("Unable to open cache");
    }
}

void Cache::clear() {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("cache")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            char* cache_filepath = static_cast<char*>(malloc(CACHE_PREFIX_LENGTH * sizeof(char)));
            strcpy(cache_filepath, "cache/");
            strcat(cache_filepath, ent->d_name);
            remove(cache_filepath);
        }
        closedir (dir);
    } else {
        throw std::runtime_error("Unable to open cache");
    }
}

Cache::~Cache(){}


int main() {
    auto cache = std::make_unique<Cache>();
    char* filepath = static_cast<char*>(malloc(11));
    strcpy(filepath, "matrix1.txt");
    //cache->store(filepath);
    //cache->search(filepath);
    cache->clear();
}