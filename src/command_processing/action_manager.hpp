#include <string>
#include <vector>

using std::vector;

struct action {
  std::string department;
  std::string command;
  vector<std::string> args;
};

class ActionManager {
private:
  static bool is_a_text_file(const std::string file_name);
  static bool is_a_bmp_file(const std::string file_name);
  static void matrix_add(vector<std::string> args);
  static void matrix_multiply(vector<std::string> args);
  static void image_rotate(vector<std::string> args);
  static void image_convert(vector<std::string> args);
  static void hash_crc32(vector<std::string> args);
  static void cache_clear(vector<std::string> args);
  static void cache_search(vector<std::string> args);

public:
  // takes an action struct and preforms the matching action
  static void perform_action(struct action action);
};