#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

bool has_hashtag(const std::string& str) {
    return str.find("#") != std::string::npos;
}

size_t arrangements(const std::string& str, const std::vector<uint16_t>& groups) {

    size_t result = 0;    

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
    return result;
}


int solve(const std::vector<std::string>& input) {
    uint32_t result{}; 

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

    int result = solve(input);

    std::cout << "Solution: " << result << std::endl;

    return 0;

}

