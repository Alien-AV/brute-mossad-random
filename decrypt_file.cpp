#include <cstdint>
#include <Windows.h>
#include <fstream>
#include <iostream>

int main(){
    HCRYPTPROV phProv;
    HCRYPTHASH hHash;
    HCRYPTKEY hKey;
    uint8_t key_material[14] = {0x00, 0x13, 0x37, 0x8E, 0xAB, 0x66, 0x61, 0x77, 0x4D, 0x56, 0x30, 0x30, 0x30, 0x30};
//    uint8_t key_material[14] = {0x00, 0x13, 0x37, 0x8E, 0xAB, 0x66, 0x56, 0x4d, 0x77, 0x61, 0x30, 0x30, 0x30, 0x30}; //bios key inverted

    std::ifstream ifstream("C:\\Hacking\\mossad\\intel.txt.enc.unxored.no_metadata", std::ios::binary | std::ifstream::in | std::ifstream::ate);
    auto size = ifstream.tellg();
    uint8_t* memblock = new uint8_t[size];
    ifstream.seekg (0, std::ios::beg);
    ifstream.read ((char*)memblock, size);
    ifstream.close();

    CryptAcquireContextW(&phProv, L"DataSafeCryptContainer", 0, PROV_RSA_AES, 0x50u);
    CryptAcquireContextW(&phProv, L"DataSafeCryptContainer", 0, PROV_RSA_AES, 0x48u);
    CryptCreateHash(phProv, CALG_MD5, 0, 0, &hHash);
    CryptHashData(hHash, key_material, 14, 0);
    CryptDeriveKey(phProv, CALG_AES_256, hHash, 0, &hKey);
    DWORD read_bytes = size;

    auto result = CryptDecrypt(hKey, 0, true, 0, memblock, &read_bytes);
    std::cout << "read_bytes: " << read_bytes << ", result: " << result << std::hex << ", GetLastError: " << GetLastError() << std::endl << memblock << std::endl;
}