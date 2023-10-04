#include "bytes.hpp"
#include <thread>
#include <iostream>
#include <fstream>

int main() {
    std::string filePath;
    std::cout << "Enter the file path: ";
    std::cin >> filePath;

    std::cout << "Loading";
    std::thread animationThread([]() {
        for (int i = 0; i < 3; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << ".";
        }
        std::cout << std::endl;
    });

    std::vector<std::string> hexBytes = bytes::read_hex_bytes(filePath);
    animationThread.join();

    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        exit(1);
    }

    for (size_t i = 0; i < hexBytes.size(); ++i) {
        outputFile << "{0x" << hexBytes[i] << "}";
        std::cout << hexBytes[i];
        if (i < hexBytes.size() - 1) {
            outputFile << ", ";
        }
    }
    outputFile.close();

    std::cout << "\nThere have been " << hexBytes.size() << " hex written to output.txt" << std::endl;

    return 0;
}