#include <mutex>
#include <thread>
#include <chrono>
#include <sstream>
#include <array>
#include <random>
#include <algorithm>
#include <vector>
#include <iterator>
#include <fstream>
#include <iostream>
#include "utils.h"

void write_to_file(const char *filename, char* full_file_contents, size_t size) {
    std::ofstream os(filename, std::ios::binary);
    os.write((char *) full_file_contents, size);
    delete[] full_file_contents;
}

void read_from_file(const char *filename, char** full_file_contents, size_t& size){
    std::ifstream ifstream(filename, std::ios::binary | std::ifstream::in | std::ifstream::ate);
    size = (size_t)ifstream.tellg();
    *full_file_contents = new char[size];
    ifstream.seekg (0, std::ios::beg);
    ifstream.read (*full_file_contents, size);
    ifstream.close();
}

void generate_state_with_seed(uint32_t * state, uint32_t seed){
    state[0] = seed;
    for(size_t index = 1; index < 624; index++)
    {
        state[index] = 6069 * state[index-1];
    }
}