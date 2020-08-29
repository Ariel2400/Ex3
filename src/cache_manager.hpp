#include <string>

class Cache {
    private:
        static bool is_file_in_cache(const std::string filepath);
    public:
        Cache();
        Cache(const Cache& other);
        Cache& operator=(const Cache & other);
        static void store(const std::string filepath);
        static void search(const std::string filepath);
        static void clear();
        ~Cache();
};