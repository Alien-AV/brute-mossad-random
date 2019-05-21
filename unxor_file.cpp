#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>

int main(){
    std::ifstream ifstream("intel.txt.enc", std::ios::binary | std::ifstream::in | std::ifstream::ate);
    auto size = ifstream.tellg();
    uint32_t* memblock = new uint32_t[size/sizeof(uint32_t)];
    ifstream.seekg (0, std::ios::beg);
    ifstream.read ((char*)memblock, size);
    ifstream.close();

    for(size_t i = 0; i<size/ sizeof(uint32_t); i++){
        memblock[i] ^= 0x30303030;
    }
    std::ofstream os("C:\\Hacking\\mossad\\intel.txt.enc.unxored", std::ios::binary);
    os.write((char*)memblock, size);
    delete[] memblock;
}