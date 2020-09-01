#include <string>

class Cache {
public:
  // returns true if cache has a file with name file_name_in_cache, else false
  static bool is_file_in_cache(const std::string action_description);

  // searches the cache for a file with corresponding name, and prints a message
  static void search(const std::string action_description);

  // prints the file from cache
  static void print(const std::string action_description);

  // add file to cache
  static void store_into(const std::string src_file_name,
                         const std::string action_description);

  // retrieve a file from cache
  static void load_from(const std::string action_description,
                        const std::string dest_file_name);

  // clears the cache
  static void clear();

private:

  static std::string get_suffix(const std::string action_description);

  /* returns the described action's file's serial number in the cash or 0 if
     it's not there or if an error occurred */
  static int get_action_serial_number(const std::string action_description);

  // returns the serial number of the next file to be added or 0 if an error occurred
  static int get_next_serial_number();
};