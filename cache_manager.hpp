#include <vector>
#include <time.h>

class Cache {
    public:
        Cache();
        Cache(const Cache& other);
        Cache& operator=(const Cache & other);
        void store(char* filepath);
        void search(char* filepath);
        void clear();
        ~Cache();
};