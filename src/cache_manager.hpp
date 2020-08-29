#include <string>

class Cache {
    private:
        bool is_file_in_cache(std::string filepath);
    public:
        Cache();
        Cache(const Cache& other);
        Cache& operator=(const Cache & other);
        void store(std::string filepath);
        void search(std::string filepath);
        void clear();
        ~Cache();
};