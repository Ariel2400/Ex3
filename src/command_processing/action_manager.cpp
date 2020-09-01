#include <algorithm>
#include <iostream>

#include "action_manager.hpp"
#include "../cache_managment/cache_manager.hpp"
#include "../hash/hash_calculator.hpp"
#include "../images/image_editor.hpp"
#include "../matrices/matrix_calculator.hpp"

bool ActionManager::is_a_text_file(const std::string file_name) {
  std::string suffix(".txt");
  return file_name.size() >= suffix.size() &&
         file_name.compare(file_name.size() - suffix.size(), file_name.size(),
                           suffix) == 0;
}

bool ActionManager::is_a_bmp_file(const std::string file_name) {
  std::string suffix(".bmp");
  return file_name.size() >= suffix.size() &&
         file_name.compare(file_name.size() - suffix.size(), file_name.size(),
                           suffix) == 0;
}

void ActionManager::matrix_add(vector<std::string> args) {
  if (args.size() != 3) {
    std::cerr << "Invalid number of matrix add arguments, expected 3"
              << std::endl;
  } else {
    std::string action_description("matrix add " + args[0] + " " + args[1]);
    if (Cache::is_file_in_cache(action_description)) {
      if (args[2].compare("stdout") == 0) {
        Cache::print(action_description);
      } else if (is_a_text_file(args[2])) {
        Cache::load_from(action_description, args[2]);
      } else {
        std::cerr << args[2] << " is not a text file" << std::endl;
      }
    } else {
      if (args[2].compare("stdout") == 0) {
        if (MatrixCalculator::add(args[0], args[1], "temp.txt")) {
          Cache::store_into("temp.txt", action_description);
          Cache::print(action_description);
          remove("temp.txt");
        }
      } else if (is_a_text_file(args[2])) {
        if (MatrixCalculator::add(args[0], args[1], args[2])) {
          Cache::store_into(args[2], action_description);
        }
      } else {
        std::cerr << args[2] << " is not a text file" << std::endl;
      }
    }
  }
}

void ActionManager::matrix_multiply(vector<std::string> args) {
  if (args.size() != 3) {
    std::cerr << "Invalid number of matrix multiply arguments, expected 3"
              << std::endl;
  } else {
    std::string file_name("matrix_multiply_" + args[0] + "_" + args[1]);
    std::replace(file_name.begin(), file_name.end(), '.', '_');
    file_name += ".txt";
    if (Cache::is_file_in_cache(file_name)) {
      if (args[2].compare("stdout") == 0) {
        Cache::print(file_name);
      } else if (is_a_text_file(args[2])) {
        Cache::load_from(file_name, args[2]);
      } else {
        std::cerr << args[2] << " is not a text file" << std::endl;
      }
    } else {
      if (args[2].compare("stdout") == 0) {
        if (MatrixCalculator::multiply(args[0], args[1], "temp.txt")) {
          Cache::store_into("temp.txt", file_name);
          Cache::print(file_name);
          remove("temp.txt");
        }
      } else if (is_a_text_file(args[2])) {
        if (MatrixCalculator::multiply(args[0], args[1], args[2])) {
          Cache::store_into(args[2], file_name);
        }
      } else {
        std::cerr << args[2] << " is not a text file" << std::endl;
      }
    }
  }
}

void ActionManager::image_rotate(vector<std::string> args) {
  if (args.size() != 2) {
    std::cerr << "Invalid number of image rotate arguments, expected 2"
              << std::endl;
  } else if (is_a_bmp_file(args[1])) {
    std::string file_name("image_rotate_" + args[0]);
    std::replace(file_name.begin(), file_name.end(), '.', '_');
    file_name += ".bmp";
    if (Cache::is_file_in_cache(file_name)) {
      if (is_a_bmp_file(args[1])) {
        Cache::load_from(file_name, args[1]);
      } else {
        std::cerr << args[1] << " is not a bmp file" << std::endl;
      }
    } else {
      if (is_a_bmp_file(args[1])) {
        if (ImageEditor::rotate(args[0], args[1])) {
          Cache::store_into(args[1], file_name);
        }
      } else {
        std::cerr << args[1] << " is not a bmp file" << std::endl;
      }
    }
  } else {
    std::cerr << args[1] << " is not a bmp file" << std::endl;
  }
}

void ActionManager::image_convert(vector<std::string> args) {
  if (args.size() != 2) {
    std::cerr << "Invalid number of image convert arguments, expected 2"
              << std::endl;
  } else if (is_a_bmp_file(args[1])) {
    std::string file_name("image_convert_" + args[0]);
    std::replace(file_name.begin(), file_name.end(), '.', '_');
    file_name += ".bmp";
    if (Cache::is_file_in_cache(file_name)) {
      if (is_a_bmp_file(args[1])) {
        Cache::load_from(file_name, args[1]);
      } else {
        std::cerr << args[1] << " is not a bmp file" << std::endl;
      }
    } else {
      if (is_a_bmp_file(args[1])) {
        if (ImageEditor::convert_to_grayscale(args[0], args[1])) {
          Cache::store_into(args[1], file_name);
        }
      } else {
        std::cerr << args[1] << " is not a bmp file" << std::endl;
      }
    }
  } else {
    std::cerr << args[1] << " is not a bmp file" << std::endl;
  }
}

void ActionManager::hash_crc32(vector<std::string> args) {
  if (args.size() != 2) {
    std::cerr << "Invalid number of hash crc32 arguments, expected 2"
              << std::endl;
  } else {
    std::string file_name("crc32_" + args[0]);
    std::replace(file_name.begin(), file_name.end(), '.', '_');
    file_name += ".txt";
    if (Cache::is_file_in_cache(file_name)) {
      if (args[1].compare("stdout") == 0) {
        Cache::print(file_name);
      } else if (is_a_text_file(args[1])) {
        Cache::load_from(file_name, args[1]);
      } else {
        std::cerr << args[1] << " is not a text file" << std::endl;
      }
    } else {
      if (args[1].compare("stdout") == 0) {
        if (HashCalculator::crc32(args[0], "temp.txt")) {
          Cache::store_into("temp.txt", file_name);
          Cache::print(file_name);
          remove("temp.txt");
        }
      } else if (is_a_text_file(args[1])) {
        if (HashCalculator::crc32(args[0], args[1])) {
          Cache::store_into(args[1], file_name);
        }
      } else {
        std::cerr << args[1] << " is not a text file" << std::endl;
      }
    }
  }
}

void ActionManager::cache_clear(vector<std::string> args) {
  if (args.size() != 0) {
    std::cerr << "cache clear command requires no arguments" << std::endl;
  } else {
    Cache::clear();
  }
}

void ActionManager::cache_search(vector<std::string> args) {
  if (args.size() == 0) {
    std::cerr << "cache searc command requires search parameters" << std::endl;
  } else {
    std::string file_name(args[0]);
    for (size_t i = 1; i != args.size(); ++i) {
      file_name += "_";
      file_name += args[i];
    }
    std::replace(file_name.begin(), file_name.end(), '.', '_');
    if (args[0].compare("matrix") == 0 || args[0].compare("crc32") == 0) {
      file_name += ".txt";
    } else if (args[0].compare("image") == 0) {
      file_name += ".bmp";
    }
    Cache::search(file_name);
  }
}

void ActionManager::perform_action(struct action action) {
  if (action.department.compare("matrix") == 0) {
    if (action.command.compare("add") == 0) {
      matrix_add(action.args);
    } else if (action.command.compare("multiply") == 0) {
      matrix_multiply(action.args);
    } else {
      std::cerr << "Unknown matrix command: " << action.command << std::endl;
    }
  } else if (action.department.compare("image") == 0) {
    if (action.command.compare("rotate") == 0) {
      image_rotate(action.args);
    } else if (action.command.compare("convert") == 0) {
      image_convert(action.args);
    } else {
      std::cerr << "Unknown image command: " << action.command << std::endl;
    }
  } else if (action.department.compare("hash") == 0) {
    if (action.command.compare("crc32") == 0) {
      hash_crc32(action.args);
    } else {
      std::cerr << "Unknown hash algorithm: " << action.command << std::endl;
    }
  } else if (action.department.compare("cache") == 0) {
    if (action.command.compare("clear") == 0) {
      cache_clear(action.args);
    } else if (action.command.compare("search") == 0) {
      cache_search(action.args);
    } else {
      std::cerr << "Unknown cache command: " << action.command << std::endl;
    }
  } else {
    std::cerr << "Unknown department: " << action.department << std::endl;
  }
}

/*
int main() {
    vector<std::string> args1;
    vector<std::string> args2;
    args1.emplace_back("image");
    args1.emplace_back("convert");
    args1.emplace_back("lena-color.bmp");
    args2.emplace_back("sdfgsgdf");
    args2.emplace_back("nwgfrnbfgn");
    struct action action1 = {"cache", "search", args1};
    struct action action2 = {"cache", "search", args2};
    ActionManager::perform_action(action1);
    ActionManager::perform_action(action2);
}
*/