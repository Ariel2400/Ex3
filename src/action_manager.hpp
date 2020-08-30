#include <string>
#include <vector>

using std::vector;

struct action {
    std::string department;
    std::string command;
    vector<std::string> args;
};

class ActionManager {
    public:
        static void perform_action(struct action action);

    private:
        static void matrix_add(vector<std::string> args);
        static void matrix_multiply(vector<std::string> args);
        static void image_rotate(vector<std::string> args);
        static void image_convert(vector<std::string> args);
        static void hash_crc32(vector<std::string> args);
        static void cache_clear();
        static void cache_search(vector<std::string> args);
};