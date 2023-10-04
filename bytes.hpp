#ifndef PROC_ARRAY_BYTES_HPP
#define PROC_ARRAY_BYTES_HPP


#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace bytes {
    std::vector<std::string> read_hex_bytes(const std::string& filePath) {
        std::ifstream inputFile(filePath, std::ios::in | std::ios::binary);
        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open file for reading." << std::endl;
            exit(1);
        }

        std::vector<char> rawBytes(
                (std::istreambuf_iterator<char>(inputFile)),
                (std::istreambuf_iterator<char>()));

        inputFile.close();

        std::vector<std::string> hexBytes;
        for (const auto& byte : rawBytes) {
            std::string hexByte(2, '0');
            hexByte[0] = "0123456789ABCDEF"[static_cast<unsigned char>(byte) >> 4];
            hexByte[1] = "0123456789ABCDEF"[static_cast<unsigned char>(byte) & 0x0F];
            hexBytes.push_back(hexByte);
        }

        return hexBytes;
    }
}

#endif //PROC_ARRAY_BYTES_HPP
