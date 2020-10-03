cmake_minimum_required(VERSION 3.0.0)
project(ex3.exe VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror -Wnon-virtual-dtor -Wshadow)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# add the .cpp files of the project
add_executable(ex3.out 
                cache_managment/cache_manager.cpp
                command_processing/action_manager.cpp
                command_processing/terminal_parser.cpp
                hash/crc32.cpp
                hash/hash_calculator.cpp
                images/bmp_parser.cpp
                images/image_editor.cpp
                matrices/error_code.cpp
                matrices/matrix.cpp
                matrices/matrix_calculator.cpp
                matrices/matrix_class.cpp)

# add the folders of the .h files (to be able to include them)
target_include_directories(ex3.out PUBLIC
                            ${CMAKE_SOURCE_DIR}/cache_managment
                            ${CMAKE_SOURCE_DIR}/command_processing
                            ${CMAKE_SOURCE_DIR}/hash
                            ${CMAKE_SOURCE_DIR}/images
                            ${CMAKE_SOURCE_DIR}/matrices
                            )

# make the cache directory
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/cache)

# include the src directory
target_link_directories(ex3.out PUBLIC ${PROJECT_SOURCE_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)