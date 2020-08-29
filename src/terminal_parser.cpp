#include <string>
#include <vector>
#include <iostream>

#include "action_manager.hpp"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "The program requires a department and command input" << std::endl;
    } else {
        vector<std::string> args;
        for (int i = 3; i < argc; i ++) {
            args.emplace_back(argv[i]);
        }
        struct action action = {argv[1], argv[2], args};
        ActionManager::perform_action(action);
    }
}