#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <sstream>

uint64_t solve(const std::vector<std::string>& input, size_t expansion_factor) {
    uint64_t result{}; 
    
    size_t key = 1; 
    std::map<size_t, std::pair<int, int>> coords;
    for (size_t y = 0; y < input.size(); ++y) {
        std::vector<size_t> xs;
        size_t hashtag = input[y].find('#');
        while (hashtag != std::string::npos) {
            xs.push_back(hashtag);
            hashtag = input[y].find('#', hashtag + 1);
        }
        if (!xs.empty()) {
            for (auto x : xs) {
                coords[key] = std::make_pair(y, x); 
                ++key;
            }
        } else {
            y += (expansion_factor - 1);
        }
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
        std::pair<int, int> start = coords[keys.first]; 
        std::pair<int, int> end   = coords[keys.second]; 
        int steps = std::abs(end.second - start.second) + std::abs(end.first - start.first);
        result += steps;
    }
    return result;
}

void expand_galaxies(std::vector<std::string>& input, size_t expansion_factor) {
    
    size_t size = input.size();

    for (size_t r = 0; r < input.size(); ++r) {
        if (input[r].find("#") != std::string::npos) continue;  
        input.insert(input.begin() + (r+1), expansion_factor-1, std::string(size, '.'));
        r += (expansion_factor-1);
    }
    size = input.size();

    for (size_t c = 0; c < input[0].size(); ++c) {
        bool expand = true;
        for(size_t r = 0; r < size; ++r) {
            if(input[r][c] != '.') {
                expand = false;
                break;
            }
        }
        if (expand) {
            std::string expansion((expansion_factor-1), '.');
            for (size_t i = 0; i < input.size(); ++i) {
                input[i].insert(c, expansion);  
            }
            c += (expansion_factor-1);
        }
    }
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

    expand_galaxies(input, expansion_factor);
    
    
    uint64_t result = solve(input, expansion_factor);
    std::cout << "Solution: " << result << std::endl;

    return 0;

}

