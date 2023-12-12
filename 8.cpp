#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

int solve2(const std::vector<std::string>& input) {
    uint32_t result{}; 

    for (const auto& str : input) {

    }

    return result;

}

int solve(const std::vector<std::string>& input, std::string LR) {

    uint32_t result{}; 
    std::map<std::string, std::pair<std::string, std::string>> dir_map;

    for (const auto& str : input) {
        std::string key = str.substr(0, 3);
        std::string left = str.substr(7, 3);
        std::string right = str.substr(12, 3);
        dir_map[key] = std::make_pair(left, right);
    }
    
    std::string curr = "AAA";
    std::string goal = "ZZZ";
    size_t i = 0;
    while (curr != goal) {
        switch(LR[i]) {
            case 'R':
                curr = dir_map[curr].second;
                break;
            case 'L':
                curr = dir_map[curr].first;
                break;
        }
        ++result;
        ++i;
        if(i == LR.size()) i = 0;
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
    std::string line, LR;

    for (int i = 0; i < 2; ++i) {
        getline(inputFile, line);
        if (i == 0) LR = line;
    }

    while (getline(inputFile, line)) {
        input.push_back(line);
    }

    inputFile.close();

    int result = solve(input, LR);
    int result2 = solve2(input);

    std::cout << "Solution: " << result << std::endl;
    std::cout << "Solution 2: " << result2 << std::endl;

    return 0;

}

