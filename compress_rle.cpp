#include <fstream>
#include <iostream>
#include <ostream>
#include <queue>
#include <string>
#include <utility>


void compress_rle(
    std::string filename,
    bool in_place = false
) {
    std::fstream rfile{filename, rfile.in | rfile.binary};
    std::fstream wfile{in_place ? filename : "Compressed " + filename, wfile.out | wfile.binary};

    char prev_symbol;
    int counter;

    std::queue<std::pair<char, int>> compressed_queue;

    char symbol;
    rfile.seekp(0);

    auto append_symbol = [&compressed_queue](char symbol, int count) {
        if (static_cast<char32_t>(symbol) != 0) {
            compressed_queue.push({symbol, count});
        }
    };

    while (rfile >> symbol) {
        if (prev_symbol != symbol) {
            append_symbol(prev_symbol, counter);
            prev_symbol = symbol;
            counter = 1;
        } else {
            counter++;
        }
    }
    append_symbol(prev_symbol, counter);

    wfile.clear();
    wfile.seekp(0);

    while (!compressed_queue.empty()) {
        std::pair<char, int> p = compressed_queue.front();
        compressed_queue.pop();
        wfile << p.first << p.second;
        std::cout << p.first << ": " << p.second << " ";
    }
    std::cout << "\n";
}