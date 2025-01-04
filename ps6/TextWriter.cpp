// Copyright [2024] Ashish Kosana
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "RandWriter.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./TextWriter <order> <length>\n";
        return 1;
    }

    size_t k = 0, L = 0;
    try {
        k = std::stoi(argv[1]);
        L = std::stoi(argv[2]);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing arguments: " << e.what() << std::endl;
        return 1;
    }

    std::string text((std::istreambuf_iterator<char>(std::cin)),
                     std::istreambuf_iterator<char>());

    if (text.empty()) {
        std::cerr << "Error: No input text provided.\n";
        return 1;
    }

    try {
        RandWriter writer(text, k);


        auto generateKgram = [&text, k]() { return text.substr(0, k); };

        std::string kgram = generateKgram();
        std::cout << writer.generate(kgram, L) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
