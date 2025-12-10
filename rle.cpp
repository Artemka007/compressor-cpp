#include <filesystem>
#include <fstream>
#include <ostream>
#include <queue>
#include <string>
#include <utility>


void compress_rle(
    std::string filename,
    bool in_place = false
) {
    if (!in_place) {
        std::filesystem::copy_file(filename, "Compressed " + filename);
    }
    std::fstream file{
        in_place ? filename : "Compressed " + filename, 
        file.binary | file.trunc | file.in | file.out
    };

    char prev_symbol;
    int counter;

    std::queue<std::pair<char, int>> compressed_queue;

    char symbol;

    while (file >> symbol) {
        if (prev_symbol != symbol) {
            compressed_queue.push({prev_symbol, counter});
            prev_symbol = symbol;
            counter = 1;
        } else {
            counter++;
        }
    }

    file.clear();
    file.seekp(0);

    while (!compressed_queue.empty()) {
        std::pair<char, int> p = compressed_queue.front();
        file << compressed_queue.front().first << compressed_queue.front().second;
    }
}