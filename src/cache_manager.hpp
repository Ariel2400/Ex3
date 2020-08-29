#include <string>

class Cache {
    private:
        
    public:
        Cache();
        Cache(const Cache& other);
        Cache& operator=(const Cache & other);
        static bool is_file_in_cache(const std::string file_name_in_cache);
        static void search(const std::string file_name_in_cache);
        static void print(const std::string file_name_in_cache);
        static void store_into(const std::string src_file_name, const std::string file_name_in_cache);
        static void load_from(const std::string file_name_in_cache, const std::string dest_file_name);
        static void clear();
        ~Cache();
};