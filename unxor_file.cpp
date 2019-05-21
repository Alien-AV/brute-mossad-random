#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "utils.h"

int main(){
    char* full_file_contents = nullptr; size_t size;
    read_from_file("C:\\Hacking\\mossad\\intel.txt.enc", &full_file_contents, size);

    for(size_t i = 0; i < size; i+=4){
        *((uint32_t*)&full_file_contents[i]) ^= 0x30303030;
    }

    write_to_file("C:\\Hacking\\mossad\\intel.txt.enc.unxored", full_file_contents, size);
    std::cout << "unxored " << size << " bytes" << std::endl;
}