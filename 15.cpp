#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

size_t hash(const std::string& str) {
    size_t current_value = 0;
    for(char c : str) {
        current_value += c;
        current_value *= 17;
        current_value = current_value % 256;
    }
    return current_value; 
}

using hashmap_t = std::vector<std::vector<std::pair<std::string, int>>>;
using box_t = std::vector<std::pair<std::string, int>>;

size_t focusing_power(hashmap_t& hashmap) {
    size_t fp = 0;
    size_t box_n = 0;
    for (const auto& box : hashmap) {
        size_t slot = 1;
        for (const auto& lens : box) {
            fp += (1+box_n) * lens.second * slot;
            ++slot;
        }
        ++box_n;
    }
    return fp;
}

box_t::iterator find_key(box_t& box, const std::string& key) {
    return std::find_if(box.begin(), box.end(),
        [key](const std::pair<std::string, int>& e) {
            return e.first == key;
        });
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> " << "<?part2>" << std::endl;
        return 1;

    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the input file!" << std::endl;
        return 1;

    }

    bool part2 = std::stoi(argv[2]);

    std::string line;
    std::string input; 
    while (getline(inputFile, line)) input = line;
    
    inputFile.close();

    size_t result{};
    std::stringstream ss(input);
    std::string token;

    hashmap_t hashmap(256);

    while(getline(ss, token, ',')) {
        if(!part2) result += hash(token);

        else {
            size_t minus = token.find('-');
            size_t equals = token.find('=');

            if (minus != std::string::npos) {
                std::string key = token.substr(0, minus);
                size_t hash_val = hash(key);
                box_t& box = hashmap[hash_val];
                auto it = find_key(box, key);
                if (it != box.end()) {
                    box.erase(it);
                }
            }
            if (equals != std::string::npos) {
                std::string key = token.substr(0, equals);
                size_t hash_val = hash(key);
                int val = std::stoi(token.substr(equals+1));
                box_t& box = hashmap[hash_val];
                auto it = find_key(box, key);
                if (it != box.end()) {
                    it -> second = val;
                } else {
                    box.emplace_back(key, val);
                }
            }
        }
    }
    
    if(part2) result = focusing_power(hashmap);


    std::cout << "Solution: " << result << std::endl;

    return 0;
}

