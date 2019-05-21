#include <cstdint>
#include <Windows.h>
#include <fstream>
#include <iostream>
#include "utils.h"

int main(){
    HCRYPTPROV phProv;
    HCRYPTHASH hHash;
    HCRYPTKEY hKey;
    uint8_t key_material[14] = {0x00, 0x13, 0x37, 0x8E, 0xAB, 0x66, 0x56, 0x4d, 0x77, 0x61, 0x30, 0x30, 0x30, 0x30};

    char* full_file_content; size_t size; read_from_file("C:\\Hacking\\mossad\\intel.txt.enc.unxored.no_metadata", &full_file_content, size);

    CryptAcquireContextW(&phProv, L"DataSafeCryptContainer", 0, PROV_RSA_AES, 0x50u);
    CryptAcquireContextW(&phProv, L"DataSafeCryptContainer", 0, PROV_RSA_AES, 0x48u);
    CryptCreateHash(phProv, CALG_MD5, 0, 0, &hHash);
    CryptHashData(hHash, key_material, 14, 0);
    CryptDeriveKey(phProv, CALG_AES_256, hHash, 0, &hKey);
    DWORD read_bytes = size;

    auto result = CryptDecrypt(hKey, 0, true, 0, (BYTE*)full_file_content, &read_bytes);
    std::cout << "read_bytes: " << read_bytes << ", result: " << result << std::hex << ", GetLastError: " << GetLastError() << std::endl << full_file_content << std::endl;

    write_to_file("C:\\Hacking\\mossad\\intel.txt.result", full_file_content, size);
}