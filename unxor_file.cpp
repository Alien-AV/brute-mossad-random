#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "utils.h"

int main(){
    char* full_file_contents = nullptr; size_t size;
    read_from_file("C:\\Hacking\\mossad\\intel.txt.enc", &full_file_contents, size);

    uint32_t xor_value = 0x30303030;
//    uint32_t xor_value = ((uint32_t*)&full_file_contents)[0] ^ FILE_MAGIC

    for(size_t i = 0; i < size; i+=4){
        *((uint32_t*)&full_file_contents[i]) ^= xor_value;
    }

    write_to_file("C:\\Hacking\\mossad\\intel.txt.enc.unxored", full_file_contents, size);
    std::cout << "unxored " << size << " bytes" << std::endl;
}