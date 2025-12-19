#include <iostream>
#include <string>
#include "compress_rle.hpp"
#include "decompress_rle.hpp"

int main() {
    while (true) {
        std::string command;
        std::string filename;
        std::cout << "Enter the command (compress or decompress) and after space enter filename" << std::endl;
        std::cin >> command >> filename;
        if (command == "compress") {
            compress_rle(filename);
        } else if (command == "decompress") {
            decompress_rle(filename);
        }
    }

    return 0;
}