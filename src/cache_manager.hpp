#include <string>

class Cache {        
    public:
        //returns true if cache has a file with name file_name_in_cache, else false
        static bool is_file_in_cache(const std::string file_name_in_cache);

        //searches the cache for a file with corresponding name, and prints a message
        static void search(const std::string file_name_in_cache);

        //prints the file from cache
        static void print(const std::string file_name_in_cache);

        //add file to cache
        static void store_into(const std::string src_file_name, const std::string file_name_in_cache);

        //retrieve a file from cache
        static void load_from(const std::string file_name_in_cache, const std::string dest_file_name);
        
        //clears the cache
        static void clear();
};