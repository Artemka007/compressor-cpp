#include <filesystem>
#include <fstream>
#include <ostream>
#include <queue>
#include <string>
#include <utility>


void decompress_rle(
    std::string filename,
    bool in_place = false
) {
    if (!in_place) {
        std::filesystem::copy_file(filename, "Decompressed " + filename);
    }
    std::fstream file{
        in_place ? filename : "Decompressed " + filename, 
        file.binary | file.trunc | file.in | file.out
    };

    char prev_symbol;
    int counter;

    std::queue<std::pair<char, int>> compressed_queue;

    char symbol;

    std::string s;

    while (file >> symbol) {
        int count;
        file >> count;
        for (int i = 0; i < count; i++) {
            s += symbol;
        }
    }

    file.clear();
    file.seekp(0);

    file << s;
}