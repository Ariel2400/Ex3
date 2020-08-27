#include <vector>
#include <time.h>
#include <string>

class Cache {
    public:
        Cache();
        Cache(const Cache& other);
        Cache& operator=(const Cache & other);
        void store(std::string filepath);
        void search(std::string filepath);
        void clear();
        ~Cache();
};