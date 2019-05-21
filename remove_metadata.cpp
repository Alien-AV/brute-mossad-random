#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <random>
#include "utils.h"

void generate_state_with_seed(uint32_t * state, uint32_t seed){
    state[0] = seed;
    for(size_t index = 1; index < 624; index++)
    {
        state[index] = 6069 * state[index-1];
    }
}

int main(){
    std::cout << std::hex;

    char* full_file_content; size_t size; read_from_file("C:\\Hacking\\mossad\\intel.txt.enc.unxored", &full_file_content, size);

    std::mt19937 generator;
    generate_state_with_seed(generator._Ax, 0x61774d56);

    std::cout << "size: " << size << std::endl;
    std::ofstream os("C:\\Hacking\\mossad\\intel.txt.enc.unxored.no_metadata", std::ios::binary);
    int block_size = 49;
    size_t i;
    for(i = 36; i < size; i += (block_size + 4)) {
        auto expected_random = generator();
        if (i + block_size + 4 == 0x6069) block_size--;
        if (*((uint32_t *) &full_file_content[i]) != expected_random) {
            std::cout << "wrong random number, i: 0x" << i << ", in file: 0x" << *((uint32_t *) &full_file_content[i])
                      << ", expected: 0x" << expected_random << std::endl;
            break;
        }
        std::cout << "i: " << i << std::endl;
        os.write(&full_file_content[i + 4], block_size);
    }

    std::cout << "i: " << i << ", size: " << size << std::endl;
    delete[] full_file_content;
    os.close();
}