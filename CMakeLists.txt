cmake_minimum_required(VERSION 3.14)
project(brute_random)

set(CMAKE_CXX_STANDARD 14)

add_executable(brute_random brute_random.cpp)
add_executable(unxor_file unxor_file.cpp utils.cpp)
add_executable(remove_metadata remove_metadata.cpp utils.cpp)
add_executable(decrypt_file decrypt_file.cpp utils.cpp)