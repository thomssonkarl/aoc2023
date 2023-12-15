#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <sstream>

int solve(const std::vector<std::string>& input) {
    uint32_t result{}; 
    
    size_t key = 1; 
    std::map<size_t, std::pair<int, int>> coords;
    size_t y = 0;
    for (auto& str : input) {
        std::vector<size_t> xs;
        size_t hashtag = str.find('#');
        while (hashtag != std::string::npos) {
            xs.push_back(hashtag);
            hashtag = str.find('#', hashtag + 1);
        }

        if (!xs.empty()) {
            for (auto x : xs) {
                coords[key] = std::make_pair(y, x); 
                ++key;
            }
        }
       ++y; 
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

void expand_galaxies(std::vector<std::string>& input) {
    
    std::vector<size_t> to_expand;
    size_t size = input.size();

    for (size_t r = 0; r < size; ++r) {
        bool expand = true;
        for (size_t c = 0; c < size; ++c) {
            if (input[r][c] != '.') {
                expand = false;
                break;  
            }
        }
        if(expand) {
            to_expand.push_back(r); 
        }
    }

    size_t offset = 0;
    for (size_t row : to_expand) {
        input.insert(input.begin() + (row+1+offset), std::string(size, '.'));
        ++offset;
    }

    to_expand.clear();
    size = input.size();

    for (size_t c = 0; c < size; ++c) {
        bool expand = true;
        for(size_t r = 0; r < size; ++r) {
            if(input[r][c] != '.') {
                expand = false;
                break;
            }
        }
        if (expand) {
            to_expand.insert(to_expand.begin(), c);
        }
            
    }

    for (size_t col : to_expand) {
        for(size_t i = 0; i < input.size(); ++i) {
            if (i==0) input[i].insert(input[i].begin() + col, '.'); 
            else input[i].insert(input[i].begin() + col + 1, '.'); 
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;

    }

    std::ifstream inputFile(argv[1]);
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

    expand_galaxies(input);

    int result = solve(input);

    std::cout << "Solution: " << result << std::endl;

    return 0;

}

