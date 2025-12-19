#include <fstream>
#include <iostream>
#include <ostream>
#include <queue>
#include <string>
#include <utility>


void decompress_rle(
    std::string filename,
    bool in_place = false
) {
    std::fstream rfile{filename, rfile.in | rfile.binary};
    std::fstream wfile{in_place ? filename : "Decompressed " + filename, wfile.out | wfile.binary};

    std::queue<std::pair<char, int>> compressed_queue;

    char symbol;

    std::string s;

    while (rfile >> symbol) {
        if (static_cast<char32_t>(symbol) == 0) {
            continue;
        }
        int count;
        rfile >> count;
        std::cout << symbol << count << std::endl;
        for (int i = 0; i < count; i++) {
            s += symbol;
        }
    }


    wfile.clear();
    wfile.seekp(0);

    wfile << s;
}