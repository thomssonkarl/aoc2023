#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

bool has_hashtag(const std::string& str) {
    return str.find("#") != std::string::npos;
}

using cachekey_t = std::pair<std::string, std::vector<uint16_t>>;

std::map<cachekey_t, size_t> cache;

uint64_t arrangements(const std::string& str, const std::vector<uint16_t>& groups) {

    uint64_t result = 0;    
    cachekey_t cache_key = std::make_pair(str, groups);
    auto cached = cache.find(cache_key);
    if(cached != cache.end()) return cached->second;

    if (groups.empty()) {
        return has_hashtag(str) ? 0 : 1;
    }

    if (str.empty()) {
        return groups.empty() ? 1 : 0;
    }

    if (str[0] == '.' || str[0] == '?') {
        result += arrangements(str.substr(1), groups);
    }

    if (str[0] == '#' || str[0] == '?') {
        if (groups[0] < str.length()) {
            std::string sub = str.substr(0, groups[0]);
            if (sub.find('.') == std::string::npos &&
                (groups[0] == str.length() || str[groups[0]] != '#')) {
                std::vector<uint16_t> new_groups(groups.begin() + 1, groups.end());
                result += arrangements(str.substr(groups[0] + 1), new_groups);
            }
        }
    }
    cache[cache_key] = result;
    return result;
}

std::string transform_string(const std::string& input) {
    std::istringstream iss(input);
    std::string conditions;
    std::string groups;

    iss >> conditions >> groups;

    std::string transformed_conditions;
    for (int i = 0; i < 5; ++i) {
        if (!transformed_conditions.empty()) {
            transformed_conditions += '?';
        }
        transformed_conditions += conditions;
    }

    std::istringstream groups_stream(groups);
    std::vector<std::string> groups_list;
    std::copy(std::istream_iterator<std::string>(groups_stream),
              std::istream_iterator<std::string>(),
              std::back_inserter(groups_list));

    std::string transformed_groups;
    for (int i = 0; i < 5; ++i) {
        if (!transformed_groups.empty()) {
            transformed_groups += ',';
        }
        for (const auto& group : groups_list) {
            transformed_groups += group;
            transformed_groups += ',';
        }
        transformed_groups.pop_back();
    }

    std::string transformed_string = transformed_conditions + " " + transformed_groups;

    return transformed_string;
}


uint64_t solve(const std::vector<std::string>& input) {
    uint64_t result{}; 

    for (const auto& str : input) {
        size_t space = str.find_first_of(' ');
        std::stringstream ss(str.substr(space+1));
        std::string num;
        std::vector<uint16_t> groups;
        while(getline(ss, num, ',')) {
           groups.push_back(std::stoi(num)); 
        }
        result += arrangements(str.substr(0, space+1), groups);
    }

    return result;

}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << " <?part2>" << std::endl;
        return 1;

    }
    bool part2 = std::stoi(argv[2]);
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the input file!" << std::endl;
        return 1;

    }

    std::vector<std::string> input;
    std::string line;
    while (getline(inputFile, line)) {
        input.push_back(part2 ? transform_string(line) : line);
    }

    inputFile.close();

    uint64_t result = solve(input);

    std::cout << "Solution: " << result << std::endl;

    return 0;

}

