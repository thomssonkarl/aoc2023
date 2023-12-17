#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>

uint64_t solve(const std::vector<std::string>& input, size_t expansion_factor) {
    uint64_t result{}; 
    
    size_t key = 1; 
    std::map<size_t, std::pair<size_t, size_t>> coords;
    std::vector<bool> empty_rows(input.size(), false);
    std::vector<bool> empty_cols(input.size(), false);


    for(size_t row = 0; row < input.size(); ++row) {
        for(size_t col = 0; col < input[0].size(); ++col) {
            if(input[row][col] == '#') {
                coords[key] = std::make_pair(row, col);
                ++key;
            }
        }
    }

    for(size_t row = 0; row < input.size(); ++row) {
        if (input[row].find('#') == std::string::npos) empty_rows[row] = true;
    }

    for(size_t col = 0; col < input[0].size(); ++col) {
        bool empty = true;
        for(size_t row = 0; row < input.size(); ++row) {
            if(input[row][col] != '.') {
                empty = false;
                break;
            }
        }
        if(empty) empty_cols[col] = true;
    }

    std::vector<std::pair<size_t, size_t>> key_pairs;

    for (auto it1 = coords.begin(); it1 != coords.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != coords.end(); ++it2) {
            size_t key1 = it1->first;
            size_t key2 = it2->first;
            if (key1 < key2) key_pairs.push_back(std::make_pair(key1, key2));
        }
    }
     
    for (auto& keys : key_pairs) {
        std::pair<size_t, size_t> start = coords[keys.first]; 
        std::pair<size_t, size_t> end   = coords[keys.second]; 
        
        size_t rs = std::min(start.first, end.first);
        size_t re = std::max(start.first, end.first);

        size_t cs = std::min(start.second, end.second);
        size_t ce = std::max(start.second, end.second);

        
        for (size_t row = rs; row < re; ++row) {
            ++result;
            if (empty_rows[row]) result += (expansion_factor-1);
        }

        for (size_t col = cs; col < ce; ++col) {
            ++result;
            if (empty_cols[col]) result += (expansion_factor-1);
        }
    }

    return result;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;

    }

    std::ifstream inputFile(argv[1]);
    bool part2 = std::stoi(argv[2]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the input file!" << std::endl;
        return 1;

    }
    
    std::vector<std::string> input;
    std::string line;
    while (getline(inputFile, line)) {
        input.push_back(line);
    }

    inputFile.close();

    size_t expansion_factor = part2 ? 1000000 : 2;
    
    uint64_t result = solve(input, expansion_factor);
    std::cout << "Solution: " << result << std::endl;

    return 0;

}

